#include "MyExeptions.hpp"
using namespace std;

const std::string red("\033[0;31m");
const std::string reset("\033[0m");

MyExeptions::MyExeptions(string er) : Error(er) {}
MyExeptions::~MyExeptions() {}

Unknown_command::Unknown_command(string er) : MyExeptions(er) {}
void Unknown_command::error() {
	cout << red << "Unknown command : " << Error << reset << endl;
}

No_user_joined::No_user_joined(string er) : MyExeptions(er) {}
void No_user_joined::error() {
	cout << red << "Please login at first." << reset << endl;
	cout << red << "if you don't know, you can login by command:" << reset << endl;
	cout << red << "\"login(li) <username> <password>\"" << reset << endl;
}

Need_logout::Need_logout(string er) : MyExeptions(er) {}
void Need_logout::error() {
	cout << red << "you should logout first." << reset << endl;
	cout << red << "if you don't know, you can logout by command:" << reset << endl;
	cout << red << "\"logout(lo)\"" << reset << endl;
}

Extra_arguments_in_command::Extra_arguments_in_command(string er) : MyExeptions(er) {}
void Extra_arguments_in_command::error() {
	cout << red << "you entered some extra arguments than this command need." << reset << endl;
	cout << red << "such \"" << Error << "\" that we ignored them!" << reset << endl;
}

Not_enough_arguments::Not_enough_arguments(string er) : MyExeptions(er) {}
void Not_enough_arguments::error() {
	cout << red << "this command need more arguments than you entered." << reset << endl;
	cout << red << "you should enter: " << Error << " after command key." << reset << endl;
}


Not_found_user::Not_found_user(string er) : MyExeptions(er) {}
void Not_found_user::error() {
	cout << red << "user \"" << Error << "\" not found!" << reset << endl;
}

Not_found_group::Not_found_group(string er) : MyExeptions(er) {}
void Not_found_group::error() {
	cout << red << "group \"" << Error << "\" not found!" << reset << endl;
}

Not_in_group::Not_in_group(string er) : MyExeptions(er) {}
void Not_in_group::error() {
	cout << red << "you are not a member of this group : " << Error << reset << endl;
}

Already_in_group::Already_in_group(string er) : MyExeptions(er) {}
void Already_in_group::error() {
	cout << red << "this user \"" << Error << "\" is already in this group." << reset << endl;
}

Wrong_password::Wrong_password(string er) : MyExeptions(er) {}
void Wrong_password::error() {
	cout << red << "password \"" << Error << "\" is not true." << reset << endl;
	cout << red << "Please try again..." << reset << endl;
}

Repetitive_user::Repetitive_user(string er) : MyExeptions(er) {}
void Repetitive_user::error() {
	cout << red << "user \"" << Error << "\" is already added." << reset << endl;
}

Repetitive_document::Repetitive_document(string er) : MyExeptions(er) {}
void Repetitive_document::error() {
	cout << red << "document \"" << Error << "\" is already exsisted." << reset << endl;
}

Low_access::Low_access(string er) : MyExeptions(er) {}
void Low_access::error() {
	cout << red << "this command need " << Error << " access level low limit." << reset << endl;
	cout << red << "your access level is too low!" << reset << endl;
}

No_such_directory::No_such_directory(string er) : MyExeptions(er) {}
void No_such_directory::error() {
	cout << red << "there is no directory: \"" << Error << "\". Please check it out once." << reset << endl;
}

No_such_file::No_such_file(string er) : MyExeptions(er) {}
void No_such_file::error() {
	cout << red << "there is no file: \"" << Error << "\". Please check it out once." << reset << endl;
}

Station_null::Station_null(string er) : MyExeptions(er) {}
void Station_null::error() {
	cout << red << "you are in home now" << reset << endl;
}

Unknown_access_level::Unknown_access_level(string er) : MyExeptions(er) {}
void Unknown_access_level::error() {
	cout << red << "Unknown access level: \"" << Error << "\"" << reset << endl;
}

pro_de_mote_possiblity::pro_de_mote_possiblity(string er) : MyExeptions(er) {}
void pro_de_mote_possiblity::error() {
	cout << red << "entered mote cann't be used for " << Error << " order." << reset << endl;
}

Static_root::Static_root(string er) : MyExeptions(er) {}
void Static_root::error() {
	cout << red << "can not change root access level!" << reset << endl;
}

Repetitive_group::Repetitive_group(string er) : MyExeptions(er) {}
void Repetitive_group::error() {
	cout << red << "there is already exsist a group with this name : " << Error << reset << endl;
}

Not_found_real_file::Not_found_real_file(string er) : MyExeptions(er) {}
void Not_found_real_file::error() {
	cout << red << "there is no such file \"" << Error << "\" in home directory!" << reset << endl;
}

Need_file_name::Need_file_name(string er) : MyExeptions(er) {}
void Need_file_name::error() {
	cout << red << "Please choose a file name." << reset << endl;
}

Use_file_as_folder::Use_file_as_folder(string er) : MyExeptions(er) {}
void Use_file_as_folder::error() {
	cout << red << "order \"" << Error << "\" can be used just for folders." << reset << endl;
}

Use_folder_as_file::Use_folder_as_file(string er) : MyExeptions(er) {}
void Use_folder_as_file::error() {
	cout << red << "order \"" << Error << "\" can be used just for files." << reset << endl;	
}

user_without_group::user_without_group(string er) : MyExeptions(er) {}
void user_without_group::error() {
	cout << red << "you used an user who have not a group on his name. check it out!" << reset << endl;	
}

access_denied::access_denied(string er) : MyExeptions(er) {}
void access_denied::error() {
	cout << red << "this command need " << Error << " access to that document." << reset << endl;
	cout << red << "your access is not enough!" << endl;
}

something_else::something_else(string er) : MyExeptions(er) {}
void something_else::error() {
	cout << red << "you should enter one element between " << Error << " ." << reset << endl;
}