#include "Core.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Group.hpp"
using namespace std;

Core::Core() {
    Root = new Folder();
    users.push_back(new User(Root));
    groups.push_back(users[0]->get_own_group());
    on_time_directory = Root;
}

string Core::get_working_username() {
    if(on_time_user == NULL) return "(?)";
    return on_time_user->get_user_name();
}

string Core::get_working_path() {
    return on_time_directory->path();
}

void Core::set_home_directory(string _home_directory) {
    if(_home_directory[home_directory.size()-1]!='/')
        _home_directory.push_back('/');
        
    home_directory = _home_directory;
}

void Core::login(string user_name, string password) {
    if( on_time_user != NULL )
        throw new Need_logout("");

    int user_index = index_user(user_name);

    if(user_index < 0)
        throw new Not_found_user(user_name);
    if(!users[user_index]->check_password(password))
        throw new Wrong_password(password);

    on_time_user = users[user_index];
    on_time_directory = on_time_user->get_home();
}

void Core::logout() {
    on_time_user = NULL;
    on_time_directory = Root;
}

void Core::add_user(string user_name, string password) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN )
        throw new Low_access("admin");

    if( index_user(user_name) > 0 )
        throw new Repetitive_user(user_name);
    if( index_group(user_name) > 0 )
        throw new Repetitive_group(user_name);

    users.push_back(new User(user_name,password,Root));
    groups.push_back(users[users.size()-1]->get_own_group());
}

void Core::change_directory(string path) {
    check_on_time_user();
    vector<string> dirs = read_path(path);

    Document* target_directory = path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);

    check_rw_access(target_directory, Document::READ);
    on_time_directory = target_directory;
}

void Core::make_directory(string name) {
    check_on_time_user();
    if(check_name_exist(name))
        throw new Repetitive_document(name);

    check_rw_access(on_time_directory, Document::WRITE);

    new Folder(on_time_user,name,on_time_directory, on_time_user->get_own_group());
}

void Core::print_directory() {
    check_on_time_user();
    cout << "you are in : \"" << get_working_path() << "\"" << endl;
}

void Core::promote(string username, User::AccessLevel Mote) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::SUPERUSER)
        throw new Low_access("superuser");

    int index = index_user(username);
    if(index < 0)
        throw new Not_found_user(username);
    if(Mote == User::ROOT || users[index]->get_access_level() == User::ROOT)
        throw new Static_root("");
    if(users[index]->get_access_level() >= Mote)
        throw new pro_de_mote_possiblity("promote");
    else users[index]->change_access_level(Mote);
}

void Core::demote(string username, User::AccessLevel Mote) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::SUPERUSER)
        throw new Low_access("superuser");

    int index = index_user(username);
    if(index < 0)
        throw new Not_found_user(username);
    if(Mote == User::ROOT || users[index]->get_access_level() == User::ROOT)
        throw new Static_root("");
    if(users[index]->get_access_level() <= Mote)
        throw new pro_de_mote_possiblity("demote");
    else users[index]->change_access_level(Mote);
}

void Core::userlist() {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN)
        throw new Low_access("admin");

    print_users_list();
}

void Core::add_group(string group_name) {
    check_on_time_user();

    if( index_group(group_name) > 0 )
        throw new Repetitive_group(group_name);

    groups.push_back( new Group(group_name, on_time_user));
}

void Core::add_to_group(string group_name, string user_name) {
    check_on_time_user();

    int group_index = index_group(group_name);
    if( group_index < 0 )
        throw new Not_found_group(group_name);
    if( !groups[group_index]->has_same_member(on_time_user))
        throw new Not_in_group(group_name);

    int user_index = index_user(user_name);
    if( user_index < 0 )
        throw new Not_found_user(user_name);
    if( groups[group_index]->has_same_member(users[user_index]))
        throw new Already_in_group(user_name);

    groups[group_index]->add_member(users[user_index]);
}

void Core::upload(string real_file, string upload_path) {
    check_on_time_user();

    vector<string> dirs = read_path(upload_path);
    if(upload_path[upload_path.size()-1]=='/')
        throw new Need_file_name("");
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = upload_path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);

    check_rw_access(target_dir, Document::WRITE);

    if(target_dir->check_name_exist(file_name))
        remove(upload_path);

    ifstream file(home_directory+real_file, ifstream::binary);
    if (!file)
        throw new Not_found_real_file(real_file);
    
    vector<unsigned char> buffer(istreambuf_iterator<char>(file), {});
    new File(on_time_user,file_name,target_dir, on_time_user->get_own_group() ,buffer);
}

void Core::download(string output_name, string file_path) {
    check_on_time_user();

    vector<string> dirs = read_path(file_path);
    if(file_path[file_path.size()-1]=='/')
        throw new Need_file_name("");
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = file_path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);
    Document* downloading_file = target_dir->select_file(file_name);

    check_rw_access(downloading_file, Document::READ);

    ofstream new_file(home_directory+output_name, ofstream::binary);

    vector<unsigned char> buffer = downloading_file->get_buffer();
    new_file.write ((char*)&buffer[0] , buffer.size());
}

void Core::list_documents() {
    check_on_time_user();
    on_time_directory->list_contents();
}

void Core::copy(string sorce_path, string destination_path) {
    check_on_time_user();

    vector<string> sorce_dirs = read_path(sorce_path);
    if(sorce_path[sorce_path.size()-1]=='/')
        throw new Need_file_name("");
    string sorce_name = sorce_dirs[sorce_dirs.size()-1];
    sorce_dirs.pop_back();
    Document* sorce_dir = sorce_path[0]=='/' ? find_diraction(Root,sorce_dirs) :
                            find_diraction(on_time_directory,sorce_dirs);
    Document* sorce = sorce_dir->select_file(sorce_name);

    check_rw_access(sorce, Document::READ);

    vector<string> destination_dirs = read_path(destination_path);
    if(destination_path[destination_path.size()-1]=='/')
        throw new Need_file_name("");
    string file_name = destination_dirs[destination_dirs.size()-1];
    destination_dirs.pop_back();
    Document* destination_dir = destination_path[0]=='/' ? find_diraction(Root,destination_dirs) :
                            find_diraction(on_time_directory,destination_dirs);

    check_rw_access(destination_dir, Document::WRITE);

    new File(on_time_user, file_name, destination_dir, on_time_user->get_own_group() , sorce);
}

void Core::move(string sorce_path, string destination_path) {
    copy(sorce_path,destination_path);
    remove(sorce_path);
}

void Core::remove(string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);

    check_hole_rw_access(target, Document::WRITE);

    (target->get_station())->remove(target->get_pure_name());
}

void Core::file_size(string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);

    check_rw_access(target, Document::READ);

    unsigned long size = target->size();
    cout << size << " bytes = ";
    if(size%1000 < 500)
        cout << size/1000;
    else
        cout << size/1000 + 1;
    cout << " Kb" << endl;
}

void Core::storage() {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN)
        throw new Low_access("admin");

    file_size("/");
}

void Core::elem_info(string path) {
    check_on_time_user();
    Document* target = find_file_or_folder(path);

    target->show_info();
}

void Core::elem_info() {
    check_on_time_user();

    on_time_directory->show_folder_info();
}

void Core::plus_group_mode(Document::Access mode, std::string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user))
        throw new access_denied("owner");

    target->add_group_access(mode);
}

void Core::sub_group_mode(Document::Access mode, std::string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user))
        throw new access_denied("owner");

    target->sub_group_access(mode);
}

void Core::plus_user_mode(Document::Access mode, std::string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user))
        throw new access_denied("owner");

    target->add_user_access(mode);
}

void Core::sub_user_mode(Document::Access mode, std::string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user))
        throw new access_denied("owner");

    target->sub_user_access(mode);
}

void Core::change_owner(string username, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user))
        throw new access_denied("owner");

    int user_index = index_user(username);
    if(user_index < 0)
        throw new Not_found_user(username);

    target->change_owner(users[user_index]);
}

void Core::change_group(string groupname, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user))
        throw new access_denied("owner");

    int group_index = index_group(groupname);
    if( index_group(groupname) < 0 )
        throw new Not_found_group(groupname);

    target->change_group(groups[group_index]);
}

int Core::index_user(string user_name) {
    for(int i=0; i<users.size(); i++) {
        if(users[i]->is_same_user(user_name)) return i;
    }
    return -1;
}

int Core::index_group(string group_name) {
    for(int i=0; i<groups.size(); i++) {
        if(groups[i]->is_same_group(group_name)) return i;
    }
    return -1;
}

Document* Core::find_diraction(Document* start, vector<string> dirs) {
    Document* response = start;
    if(dirs.size()==0) return start;

    if(dirs[0]=="")
        dirs.erase(dirs.begin()+0);

    for(int i=0; i<dirs.size(); i++){
        if(dirs[i]==".") continue;
        if(dirs[i]=="..") {
            response = response->get_station();
            continue;
        }
        response = response->subset_folder(dirs[i]);
    }
    return response;
}

vector<string> Core::read_path(string path) {
    vector<string> dirs;
    int slash_index = path.find('/');
    while(slash_index < path.size()-1) {
        dirs.push_back( path.substr(0,slash_index) );
        path.erase(0,slash_index+1);
        slash_index = path.find('/');
    }
    if(path[path.size()-1]=='/')
        path.pop_back();
    dirs.push_back(path);
    return dirs;
}

bool Core::check_name_exist(string name) {
    return on_time_directory->check_name_exist(name);
}

void Core::print_users_list() {
    cout << "Username\t\tAccessLevel" << endl;
    cout << "--------\t\t-----------" << endl;
    for(int i=0; i<users.size(); i++) {
        cout << "--- " << users[i]->get_user_name()
         << "\t\t" << access_level_reader(users[i]->get_access_level()) << endl;
    }
    cout << "------------------" << endl;
}

string Core::access_level_reader(User::AccessLevel access_level) {
    if( access_level == User::USER ) return "user";
    if( access_level == User::ADMIN ) return "admin";
    if( access_level == User::SUPERUSER ) return "superuser";
    if( access_level == User::ROOT ) return "root";
    else throw new Unknown_access_level("");
}

Document* Core::find_file_or_folder(string path) {
    if(path == "/") return Root;
    vector<string> dirs = read_path(path);
    
    string name;
    bool poped = false;
    if(path[path.size()-1] != '/'){
        name = dirs[dirs.size()-1];
        dirs.pop_back();
        poped = true;
    }

    Document* dir = path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory, dirs);

    if(!poped) return dir;

    return (dir->is_folder(name)) ? dir->subset_folder(name)
                                : dir->select_file(name);
}

void Core::check_on_time_user() {
    if( on_time_user == NULL )
        throw new No_user_joined("");
}

void Core::check_rw_access(Document* doc, Document::Access acc) {
    if( on_time_user == users[0] ) return;
    if( doc == Root ) throw new access_denied("Root");

    Document::Access user_access = doc->get_access(on_time_user);

    if( (acc == Document::READ) &&
        (user_access == Document::WRITE || user_access == Document::NONE) )
        throw new access_denied("Read");

    if( (acc == Document::WRITE) &&
        (user_access == Document::READ || user_access == Document::NONE) )
        throw new access_denied("Write");

    if( (acc == Document::READ_WRITE) &&
        (user_access != Document::READ_WRITE))
        throw new access_denied("Read-Write");
}

void Core::check_hole_rw_access(Document* doc, Document::Access acc) {
    if( !(doc->hole_access(on_time_user,acc)) )
        throw new access_denied("Hole-Write");
}