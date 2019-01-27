#include "Core.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Group.hpp"
#include "../server/server.hpp"
using namespace std;

void replace_all(string before, string now, string& str) {
    for ( int character = str.find(before); character >= 0; character = str.find(before) )
        str.replace(character, before.size(), now);
}

string Core::dashboardBody() {
  int n=-1;
  string body = readFile("static/dashboard.html");
  replace_all("$(User_icon)", userIconBody(on_time_user->get_access_level()), body);
  replace_all("$(Users_setting_icon)", userSettingIconBody(on_time_user->get_access_level()), body);
  replace_all("$(User_name)", get_working_username(), body);  
  replace_all("$(Root_folder)", folderBody(Root,n), body);  
  return body;
}

string Core::userSettingIconBody(User::AccessLevel access) {
  string body;
  if(on_time_user->get_access_level() >= User::ADMIN)
    body = readFile("static/usersettingicon.html");
  return body;
}

string Core::userIconBody(User::AccessLevel access) {
  string body = (access > User::ADMIN) ?
      readFile("static/superusericon.html") : (access == User::ADMIN) ?
      readFile("static/adminusericon.html") :
      readFile("static/simpleusericon.html");
  return body;
}

string Core::folderBody(Document* main_doc, int &n) {
  string body = readFile("static/folder.html");
  replace_all("$(N)", to_string(++n), body);
  replace_all("$(Main_doc_name)", main_doc->get_name(), body);
  replace_all("$(Trash&Inf_icon)", trashInfoIconBody(main_doc, ++n), body);
  replace_all("$(New_document)", newDocumentBody(main_doc, ++n), body);
  replace_all("$(Contents)", contentsBody(main_doc, ++n), body);
  return body;
}

string Core::trashInfoIconBody(Document* main_doc, int &n) {
  string body;
  if((main_doc != Root)) {
    body += trashIconBody(main_doc);
    body += infoIconBody(main_doc, ++n);
  }
  return body;
}

string Core::trashIconBody(Document* main_doc) {
  string body = (check_hole_rw_access_http(main_doc, Document::WRITE)) ?
      readFile("static/trashicon.html") :
      readFile("static/unabletrashicon.html");
  replace_all("$(Path)", main_doc->path(), body);
  return body;
}

string Core::infoIconBody(Document* main_doc, int &n) {
  string body = (check_rw_access_http(main_doc, Document::WRITE)) ?
      readFile("static/infoicon.html") :
      readFile("static/unableinfoicon.html");
  replace_all("$(N)", to_string(++n), body);
  replace_all("$(Main_doc_info)", main_doc->info_http(), body);
  return body;
}

string Core::newDocumentBody(Document* main_doc, int &n) {
  if(main_doc == Root)
    return "";
  else
    return newIconBody(main_doc, ++n);
}

string Core::contentsBody(Document* main_doc, int &n) {
  vector<Document*> contents = main_doc->get_contents();
  string body;
  for(int i=0; i<contents.size(); i++) {
    if( contents[i]->is_folder() )
      body += (check_rw_access_http(contents[i], Document::READ)) ?
          folderBody(contents[i], ++n) :
          unableFolderBody(contents[i], ++n) ;
    else
      body += fileBody(contents[i], ++n);
  }
  return body;
}

string Core::unableFolderBody(Document* main_doc, int &n) {
  string body = readFile("static/unablefolder.html");
  replace_all("$(Main_doc_name)", main_doc->get_name(), body);
  replace_all("$(Trash&Inf_icon)", trashInfoIconBody(main_doc, ++n), body);
  return body;
}

string Core::fileBody(Document* main_doc, int &n) {
  string body = readFile("static/file.html");
  replace_all("$(N)", to_string(++n), body);
  replace_all("$(Main_doc_name)", main_doc->get_name(), body);
  replace_all("$(Trash&Inf_icon)", trashInfoIconBody(main_doc, ++n), body);
  replace_all("$(Actions)", fileIconsBody(main_doc, ++n), body);
  return body;
}

string Core::fileIconsBody(Document* main_doc, int &n) {
  string body;
  body += readIconBody(main_doc);
  body += copyIconBody(main_doc);
  body += cutIconBody(main_doc);
  body += downloadIconBody(main_doc, ++n);
  return body;
}

string Core::readIconBody(Document* main_doc) {
  string body = (check_rw_access_http(main_doc, Document::WRITE)) ?
      readFile("static/readicon.html") :
      readFile("static/unablereadicon.html");
  replace_all("$(Path)", main_doc->path(), body);
  return body;
}

string Core::copyIconBody(Document* main_doc) {
  string body = (check_rw_access_http(main_doc, Document::WRITE)) ?
      readFile("static/copyicon.html") :
      readFile("static/unablecopyicon.html");
  replace_all("$(Path)", main_doc->path(), body);
  return body;
}

string Core::cutIconBody(Document* main_doc) {
  string body = (check_rw_access_http(main_doc, Document::WRITE)) ?
      readFile("static/cuticon.html") :
      readFile("static/unablecuticon.html");
  replace_all("$(Path)", main_doc->path(), body);
  return body;
}

string Core::downloadIconBody(Document* main_doc, int &n) {
  string body = (check_rw_access_http(main_doc, Document::READ)) ?
      readFile("static/downloadicon.html") :
      readFile("static/unabledownloadicon.html");
  replace_all("$(N)", to_string(++n), body);
  replace_all("$(Path)", main_doc->path(), body);
  return body;
}

string Core::newIconBody(Document* main_doc, int &n) {
  string body = ( check_rw_access_http(main_doc, Document::WRITE) ) ?
      readFile("static/newicon.html") :
      readFile("static/unablenewicon.html");
  replace_all("$(N)", to_string(++n), body);
  replace_all("$(New_folder)", newFolderIconBody(main_doc, ++n), body);
  replace_all("$(New_file)", newFileIconBody(main_doc, ++n), body);
  return body;
}

string Core::newFolderIconBody(Document* main_doc, int &n) {
  string body = readFile("static/newfoldericon.html");
  replace_all("$(N)", to_string(++n), body);
  replace_all("$(Path)", main_doc->path(), body);
  return body;
}

string Core::newFileIconBody(Document* main_doc, int &n) {
  string body = readFile("static/newfileicon.html");
  replace_all("$(N)", to_string(++n), body);
  replace_all("$(Path)", main_doc->path(), body);
  return body;
}

string Core::userListBody() {
  string body = readFile("static/userlist.html");
  replace_all("$(Add_user_door)", addUserdoorIconBody(on_time_user->get_access_level()), body);
  for(int i=1; i<users.size(); i++) {
    string users_html = readFile("static/userinf.html");
    replace_all("$(Username)", users[i]->get_user_name(), users_html);
    replace_all("$(Access_level)", access_level_reader(users[i]->get_access_level()), users_html);
    users_html += "$(Other_user)";
    replace_all("$(Users)", users_html, body);
    replace_all("$(Other_user)", "$(Users)", body);
  }
  replace_all("$(Users)", "", body);
  return body;
}

string Core::addUserdoorIconBody(User::AccessLevel access) {
  string body;
  if(access > User::ADMIN)
    body = readFile("static/adduserdooricon.html");
  return body;
}

string Core::pastePageBody(string sorce_dir, string order) {
  int n=-1;
  string body = readFile("static/pastepage.html");
  replace_all("$(Root_folder)", pasteFolderPageBody(Root,n,sorce_dir,order), body);
  return body;
}

string Core::pasteFolderPageBody(Document* main_doc, int &n, string sorce_dir, string order) {
  string body = readFile("static/pastefolderpage.html");
  replace_all("$(N)", to_string(++n), body);
  replace_all("$(Main_doc_name)", main_doc->get_name(), body);
  replace_all("$(Paste_icon)", pasteIconBody(main_doc,sorce_dir,order), body);
  replace_all("$(Contents)", pasteContentsBody(main_doc,sorce_dir,order,++n), body);
  return body;
}

string Core::pasteIconBody(Document* main_doc, string sorce_dir, string order) {
  string body;
  if((main_doc != Root)) {

    body = (check_hole_rw_access_http(main_doc, Document::WRITE)) ?
        readFile("static/pasteicon.html") :
        readFile("static/unablepasteicon.html");
    replace_all("$(Path)", main_doc->path(), body);
    replace_all("$(Sorce)", sorce_dir, body);
    replace_all("$(Order)", order, body);
  }
  return body;
}

string Core::pasteContentsBody(Document* main_doc, string sorce_dir, string order, int& n) {
  vector<Document*> contents = main_doc->get_contents();
  string body;
  for(int i=0; i<contents.size(); i++) {
    if( contents[i]->is_folder() ) {
      body += ( check_rw_access_http(contents[i], Document::READ) ) ?
          pasteFolderPageBody(contents[i], ++n, sorce_dir, order) :
          unablePasteFolderPageBody(contents[i], sorce_dir, order);
    }
  }
  return body;
}

string Core::unablePasteFolderPageBody(Document* main_doc, string sorce_dir, string order) {
  string body = readFile("static/unablepastefolder.html");
  replace_all("$(Main_doc_name)", main_doc->get_name(), body);
  replace_all("$(Paste_icon)", pasteIconBody(main_doc,sorce_dir,order), body);
  return body;
}

// ---------------------------------------------------------------------------------------

void Core::upload_http(string real_file, string upload_path) {
    check_on_time_user();

    vector<string> dirs = read_path(upload_path);
    if(upload_path[upload_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = upload_path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);

    check_rw_access(target_dir, Document::WRITE);

    if(target_dir->check_name_exist(file_name))
        remove(upload_path);

    if(real_file.size()==0){
        logout();
        throw Server::Exception("no file has choosen!");
    }
    
    vector<unsigned char> buffer;
    for(int i=0; i<real_file.size(); i++)
        buffer.push_back(real_file[i]);
    new File(on_time_user,file_name,target_dir, on_time_user->get_own_group() ,buffer);
}

User::AccessLevel Core::get_working_user_accesslevel() {
    return on_time_user->get_access_level();
}

bool Core::check_rw_access_http(Document* doc, Document::Access acc) {
    if( on_time_user == users[0] ) return true;
    if( doc == Root ) return false;

    Document::Access user_access = doc->get_access(on_time_user);

    if( (acc == Document::READ) &&
        (user_access == Document::WRITE || user_access == Document::NONE) )
        return false;

    if( (acc == Document::WRITE) &&
        (user_access == Document::READ || user_access == Document::NONE) )
        return false;

    if( (acc == Document::READ_WRITE) &&
        (user_access != Document::READ_WRITE))
        return false;

    return true;
}

bool Core::check_hole_rw_access_http(Document* doc, Document::Access acc) {
    if( on_time_user == users[0] ) return true;
    return doc->hole_access(on_time_user,acc);
}

string Core::read_name_of_path(string path) {
    vector<string> all = read_path(path);
    return all[all.size()-1];
}

string Core::show_media(string target) {
    check_on_time_user();

    vector<string> dirs = read_path(target);
    if(target[target.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = target[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);
    Document* downloading_file = target_dir->select_file(file_name);

    check_rw_access(downloading_file, Document::READ);

    vector<unsigned char> buffer = downloading_file->get_buffer();
    string output;
    for(int i=0; i<buffer.size(); i++)
        output.push_back(buffer[i]);

    return output;
}

// --------------------------------------------------------------------------------------------

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
    if( on_time_user != NULL ){
        logout();
        throw Server::Exception("should log out at first");
    }

    int user_index = index_user(user_name);

    if(user_index < 0){
        logout();
        throw Server::Exception("not found user "+user_name);
    }
    if(!users[user_index]->check_password(password)){
        logout();
        throw Server::Exception("wrong password"+password);
    }

    on_time_user = users[user_index];
    on_time_directory = on_time_user->get_home();
}

void Core::logout() {
    on_time_user = NULL;
    on_time_directory = Root;
}

void Core::add_user(string user_name, string password) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN ){
        logout();
        throw Server::Exception("low access, need admin at least");
    }

    if( index_user(user_name) > 0 ){
        logout();
        throw Server::Exception("already exist "+user_name);
    }
    if( index_group(user_name) > 0 ){
        logout();
        throw Server::Exception("already exist "+user_name+" as a group");
    }

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
    if(check_name_exist(name)){
        logout();
        throw Server::Exception("already exist "+name);
    }

    check_rw_access(on_time_directory, Document::WRITE);

    new Folder(on_time_user,name,on_time_directory, on_time_user->get_own_group());
}

void Core::print_directory() {
    check_on_time_user();
    cout << "you are in : \"" << get_working_path() << "\"" << endl;
}

void Core::promote(string username, User::AccessLevel Mote) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN){
        logout();
        throw Server::Exception("low access, need superuser at least");
    }

    int index = index_user(username);
    if(index < 0){
        logout();
        throw Server::Exception("not found user: "+username);
    }
    if(Mote == User::ROOT || users[index]->get_access_level() == User::ROOT){
        logout();
        throw Server::Exception("cannt use this command on root");
    }
    if(users[index]->get_access_level() >= Mote){
        logout();
        throw Server::Exception("you cant use this command for demote");
    }
    else users[index]->change_access_level(Mote);
}

void Core::demote(string username, User::AccessLevel Mote) {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN){
        logout();
        throw Server::Exception("low access, need superuser at least");
    }

    int index = index_user(username);
    if(index < 0){
        logout();
        throw Server::Exception("not found user: "+username);
    }
    if(Mote == User::ROOT || users[index]->get_access_level() == User::ROOT){
        logout();
        throw Server::Exception("cannt use this command on root");
    }
    if(users[index]->get_access_level() <= Mote){
        logout();
        throw Server::Exception("you cant use this command for demote");
    }
    else users[index]->change_access_level(Mote);
}

void Core::userlist() {
    check_on_time_user();
    if( on_time_user->get_access_level() < User::ADMIN){
        logout();
        throw Server::Exception("low access, need admin at least");
    }

    print_users_list();
}

void Core::add_group(string group_name) {
    check_on_time_user();

    if( index_group(group_name) > 0 ){
        logout();
        throw Server::Exception("already exist "+group_name);
    }

    groups.push_back( new Group(group_name, on_time_user));
}

void Core::add_to_group(string group_name, string user_name) {
    check_on_time_user();

    int group_index = index_group(group_name);
    if( group_index < 0 ){
        logout();
        throw Server::Exception("already not fount "+group_name);
    }
    if( !groups[group_index]->has_same_member(on_time_user)){
        logout();
        throw Server::Exception("user is not in group "+group_name);
    }

    int user_index = index_user(user_name);
    if( user_index < 0 ){
        logout();
        throw Server::Exception("already not fount "+user_name);
    }
    if( groups[group_index]->has_same_member(users[user_index])){
        logout();
        throw Server::Exception(user_name+"is already in group "+group_name);
    }

    groups[group_index]->add_member(users[user_index]);
}

void Core::upload(string real_file, string upload_path) {
    check_on_time_user();

    vector<string> dirs = read_path(upload_path);
    if(upload_path[upload_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string file_name = dirs[dirs.size()-1];
    dirs.pop_back();
    Document* target_dir = upload_path[0]=='/' ? find_diraction(Root,dirs) :
                            find_diraction(on_time_directory,dirs);

    check_rw_access(target_dir, Document::WRITE);

    if(target_dir->check_name_exist(file_name))
        remove(upload_path);

    ifstream file(home_directory+real_file, ifstream::binary);
    if (!file){
        logout();
        throw Server::Exception("not found "+real_file);
    }
    
    vector<unsigned char> buffer(istreambuf_iterator<char>(file), {});
    new File(on_time_user,file_name,target_dir, on_time_user->get_own_group() ,buffer);
}

void Core::download(string output_name, string file_path) {
    check_on_time_user();

    vector<string> dirs = read_path(file_path);
    if(file_path[file_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
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
    if(sorce_path[sorce_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
    string sorce_name = sorce_dirs[sorce_dirs.size()-1];
    sorce_dirs.pop_back();
    Document* sorce_dir = sorce_path[0]=='/' ? find_diraction(Root,sorce_dirs) :
                            find_diraction(on_time_directory,sorce_dirs);
    Document* sorce = sorce_dir->select_file(sorce_name);

    check_rw_access(sorce, Document::READ);

    vector<string> destination_dirs = read_path(destination_path);
    if(destination_path[destination_path.size()-1]=='/'){
        logout();
        throw Server::Exception("need file name");
    }
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
        Server::Exception("low access, need admin at least");

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

void Core::plus_group_mode(Document::Access mode, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    target->add_group_access(mode);
}

void Core::sub_group_mode(Document::Access mode, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    target->sub_group_access(mode);
}

void Core::plus_user_mode(Document::Access mode, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    target->add_user_access(mode);
}

void Core::sub_user_mode(Document::Access mode, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    target->sub_user_access(mode);
}

void Core::change_owner(string username, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    int user_index = index_user(username);
    if(user_index < 0){
        logout();
        throw Server::Exception("not found user: "+username);
    }

    target->change_owner(users[user_index]);
}

void Core::change_group(string groupname, string path) {
    check_on_time_user();

    Document* target = find_file_or_folder(path);
    if(!target->is_owner_user(on_time_user)){
        logout();
        throw Server::Exception("access denied, need owner");
    }

    int group_index = index_group(groupname);
    if( index_group(groupname) < 0 ){
        logout();
        throw Server::Exception("not found group: "+groupname);
    }

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
    else{
        logout();
        throw Server::Exception("unknown access level");
    }
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
    if( on_time_user == NULL ){
        logout();
        throw Server::Exception("no user is working");
    }
}

void Core::check_rw_access(Document* doc, Document::Access acc) {
    if( on_time_user == users[0] ) return;
    if( doc == Root ){
        logout();
        throw Server::Exception("access denied, need Root access");
    }

    Document::Access user_access = doc->get_access(on_time_user);

    if( (acc == Document::READ) &&
        (user_access == Document::WRITE || user_access == Document::NONE) ){
        logout();
    throw Server::Exception("access denied, need Read access");
    }

    if( (acc == Document::WRITE) &&
        (user_access == Document::READ || user_access == Document::NONE) ){
        logout();
    throw Server::Exception("access denied, need Write access");
    }

    if( (acc == Document::READ_WRITE) &&
        (user_access != Document::READ_WRITE)){
        logout();
    throw Server::Exception("access denied, need Read-Write access");
    }
}

void Core::check_hole_rw_access(Document* doc, Document::Access acc) {
    if( on_time_user != users[0])
        if( !(doc->hole_access(on_time_user,acc)) ){
            logout();
            throw Server::Exception("access denied, need Hole-Write access");
        }
}