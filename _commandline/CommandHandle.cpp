#include "CommandHandle.hpp"
#include "Interface.hpp"
using namespace std;

const std::string green("\033[1;32m");
const std::string reset("\033[0m");

CommandHandle::CommandHandle() {
    interface = new Interface();
}

void CommandHandle::run() {
    read_home_directory();
    string line_command;  

    cout << green << "(?): " << " » " << reset;
	while ( getline(cin,line_command) ) {
        if(line_command == "exit") return;
        istringstream words(line_command);

        try{
            handle(words);
        }
        catch(MyExeptions* Ex) {
            Ex->error();
            delete Ex;
        }
    
    cout << green << interface->get_working_username() << ": "
        << interface->get_working_path() << " » " << reset;
	}
}

void CommandHandle::handle(istringstream& words) {
    string command;
    words >> command;

        if(command == "login" || command == "li")
        login(words);
    else if(command == "logout" || command == "lo")
        logout();
    else if(command == "add_user" || command == "au")
        add_user(words);
    else if(command == "change_directory" || command == "cd")
        change_directory(words);
    else if(command == "make_directory" || command == "md")
        make_directory(words);
    else if(command == "print_directory" || command == "pd")
        print_directory();
    else if(command == "promote")
        promote(words);
    else if(command == "demote")
        demote(words);
    else if(command == "userlist")
        userlist();
    else if(command == "add_group" || command == "ag")
        add_group(words);
    else if(command == "add_to_group" || command == "jg")
        add_to_group(words);
    else if(command == "upload" || command == "up")
        upload(words);
    else if(command == "download" || command == "dw")
        download(words);
    else if(command == "list_documents" || command == "ls")
        list_documents();
    else if(command == "copy" || command == "cp")
        copy(words);
    else if(command == "move" || command == "mv")
        move(words);
    else if(command == "remove" || command == "rm")
        remove(words);
    else if(command == "file_size" || command == "fs")
        file_size(words);
    else if(command == "storage")
        storage();
    else if(command == "elem_info" || command == "ei")
        elem_info(words);
    else if(command == "change_mode" || command == "cm")
        change_mode(words);
    else if(command == "change_owner" || command == "co")
        change_owner(words);
    else if(command == "change_group" || command == "cg")
        change_group(words);
    else if(command == "--help")
        print_commands();
    else throw new Unknown_command(command);

    if(words >> command) throw new Extra_arguments_in_command(command);
}

void CommandHandle::print_commands() {
    cout << "--------------" << endl
        << "+ login(li)\t" << "<username> <password>" << endl
        << "+ logout(lo)" << endl
        << "+ add_user(au)\t" << "<username> <password>" << endl
        << "+ change_directory(cd)\t" << "<address>" << endl
        << "+ make_directory(md)\t" << "<foldername>" << endl
        << "+ print_directory(pd)" << endl
        << "+ promote\t" << "<username> <newmote>" << endl
        << "+ demote\t" << "<username> <newmote>" << endl
        << "+ userlist" << endl
        << "+ add_group(ag)\t" << "<groupname>" << endl
        << "+ add_to_group(jg)\t" << "<groupname> <username>" << endl
        << "+ upload(up)\t" << "<realfilename> <uploadpath>" << endl
        << "+ download(dw)\t" << "<realfilename> <drivepath>" << endl
        << "+ list_documents(ls)" << endl
        << "+ copy(cp)\t" << "<sorce> <destination>" << endl
        << "+ move(mv)\t" << "<sorce> <destination>" << endl
        << "+ remove(rm)\t" << "<path>" << endl
        << "+ file_size(fs)\t" << "<path>" << endl
        << "+ storage" << endl
        << "+ elem_info(ei)\t" << "(path)" << endl
        << "+ change_mode(cm)\t" << "<group|user> <+|-> <read|write|rw> <path>" << endl
        << "+ change_owner(co)\t" << "<username> <path>" << endl
        << "+ change_group(cg)\t" << "<groupname> <path>" << endl
        << "+ exit" << endl
        << "+ --help" << endl
        << "--------------" << endl;
}

void CommandHandle::login(istringstream& words) {
    string user_name, password;
    if(words >> user_name >> password)
        interface->login(user_name,password);
    else throw new Not_enough_arguments("username-password");
}

void CommandHandle::logout() {
    interface->logout();
}

void CommandHandle::add_user(istringstream& words) {
    string user_name, password;
    if(words >> user_name >> password)
        interface->add_user(user_name,password);
    else throw new Not_enough_arguments("username-password");
}

void CommandHandle::change_directory(istringstream& words) {
    string path;
    if(words >> path){
        if(path[path.size()-1]=='/') path.pop_back();

        interface->change_directory(path);
    }
    else throw new Not_enough_arguments("path");
}

void CommandHandle::make_directory(istringstream& words) {
    string name;
    if(words >> name)
        interface->make_directory(name);
    else throw new Not_enough_arguments("folder name");
}

void CommandHandle::print_directory() {
    interface->print_directory();
}

void CommandHandle::promote(istringstream& words) {
    string username, mote;
    User::AccessLevel Mote;
    if(words >> username >> mote) {
        Mote = mote_reader(mote);
        interface->promote(username,Mote);
    }
    else throw new Not_enough_arguments("username-mote");
}

void CommandHandle::demote(istringstream& words) {
    string username, mote;
    User::AccessLevel Mote;
    if(words >> username >> mote){
        Mote = mote_reader(mote);
        interface->demote(username,Mote);
    }
    else throw new Not_enough_arguments("username-mote");
}

void CommandHandle::userlist() {
    interface->userlist();
}

void CommandHandle::add_group(istringstream& words) {
    string group_name;
    if(words >> group_name)
        interface->add_group(group_name);
    else throw new Not_enough_arguments("group name");
}

void CommandHandle::add_to_group(istringstream& words) {
    string group_name, user_name;
    if(words >> group_name >> user_name)
        interface->add_to_group(group_name,user_name);
    else throw new Not_enough_arguments("groupname-username");
}

void CommandHandle::upload(istringstream& words) {
    string real_file, upload_path;
    if(words >> real_file >> upload_path)
        interface->upload(real_file,upload_path);
    else throw new Not_enough_arguments("filename-upload path");
}

void CommandHandle::download(istringstream& words) {
    string real_file, drive_path;
    if(words >> real_file >> drive_path)
        interface->download(real_file,drive_path);
    else throw new Not_enough_arguments("real-filename-drive path");
}

void CommandHandle::list_documents() {
    interface->list_documents();
}

void CommandHandle::copy(istringstream& words) {
    string sorce_path, destination_path;
    if(words >> sorce_path >> destination_path)
        interface->copy(sorce_path,destination_path);
    else throw new Not_enough_arguments("sorce path-destination path");
}

void CommandHandle::move(istringstream& words) {
    string sorce_path, destination_path;
    if(words >> sorce_path >> destination_path)
        interface->move(sorce_path,destination_path);
    else throw new Not_enough_arguments("sorce path-destination path");
}

void CommandHandle::remove(istringstream& words) {
    string path;
    if(words >> path)
        interface->remove(path);
    else throw new Not_enough_arguments("path");
}

void CommandHandle::file_size(istringstream& words) {
    string path;
    if(words >> path)
        interface->file_size(path);
    else throw new Not_enough_arguments("path");
}

void CommandHandle::storage() {
    interface->storage();
}

void CommandHandle::elem_info(istringstream& words) {
    string path;
    if(words >> path)
        interface->elem_info(path);
    else
        interface->elem_info();
}

void CommandHandle::change_mode(istringstream& words) {
    string grp_user, mode, path; char add_sub;
    if(words >> grp_user >> add_sub >> mode >> path) {
        Document::Access Mode = mode_reader(mode);
        if(grp_user == "group") {
            if(add_sub == '+')
                interface->plus_group_mode(Mode,path);
            else if(add_sub == '-')
                interface->sub_group_mode(Mode,path);
            else throw new something_else("+ or -");
        }
        else if(grp_user == "user") {
            if(add_sub == '+')
                interface->plus_user_mode(Mode,path);
            else if(add_sub == '-')
                interface->sub_user_mode(Mode,path);
            else throw new something_else("+ or -");
        }
        else throw new something_else("group or user");
    }
    else throw new Not_enough_arguments("group or user-(+or-)-mode-path");
}

void CommandHandle::change_owner(istringstream& words) {
    string username, path;
    if(words >> username >> path)
        interface->change_owner(username, path);
    else throw new Not_enough_arguments("username-path");
}

void CommandHandle::change_group(istringstream& words) {
    string groupname, path;
    if(words >> groupname >> path)
        interface->change_group(groupname, path);
    else throw new Not_enough_arguments("groupname-path");
}

User::AccessLevel CommandHandle::mote_reader(string mote) {
    if(mote == "superuser")
        return User::SUPERUSER;
    if(mote == "admin")
        return User::ADMIN;
    if(mote == "user")
        return User::USER;
    if(mote == "root")
        return User::ROOT;
    else throw new Unknown_access_level(mote);
}

Document::Access CommandHandle::mode_reader(string mode) {
    if(mode == "read")
        return Document::READ;
    if(mode == "write")
        return Document::WRITE;
    if(mode == "rw")
        return Document::READ_WRITE;
    else throw new Unknown_access_level(mode);
}

void CommandHandle::read_home_directory() {
    string home_directory;
    cout << green << "Enter home directory:" << reset << endl;
    getline(cin,home_directory);
    interface->set_home_directory(home_directory);
}