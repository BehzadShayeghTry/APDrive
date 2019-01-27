#include "Interface.hpp"
#include "Core.hpp"

Interface::Interface() {
    core = new Core();
}

std::string Interface::get_working_username() {
    return core->get_working_username();
}

std::string Interface::get_working_path() {
	return core->get_working_path();
}

void Interface::set_home_directory(std::string home_directory) {
	core->set_home_directory(home_directory);
}

void Interface::login(std::string user_name, std::string password) {
    core->login(user_name, password);
}

void Interface::logout() {
    core->logout();
}

void Interface::add_user(std::string user_name, std::string password) {
    core->add_user(user_name,password);
}

void Interface::change_directory(std::string path) {
	core->change_directory(path);
}

void Interface::make_directory(std::string name) {
	core->make_directory(name);
}

void Interface::print_directory() {
	core->print_directory();
}

void Interface::promote(std::string username, User::AccessLevel Mote) {
	core->promote(username,Mote);
}

void Interface::demote(std::string username, User::AccessLevel Mote) {
	core->demote(username,Mote);
}

void Interface::userlist() {
	core->userlist();
}

void Interface::add_group(std::string group_name) {
	core->add_group(group_name);
}

void Interface::add_to_group(std::string group_name, std::string user_name) {
	core->add_to_group(group_name, user_name);
}

void Interface::upload(std::string real_file, std::string upload_path) {
	core->upload(real_file, upload_path);
}

void Interface::download(std::string real_file, std::string drive_path) {
	core->download(real_file, drive_path);
}

void Interface::list_documents() {
	core->list_documents();
}

void Interface::copy(std::string sorce_path, std::string destination_path) {
	core->copy(sorce_path, destination_path);
}

void Interface::move(std::string sorce_path, std::string destination_path) {
	core->move(sorce_path, destination_path);
}

void Interface::remove(std::string path) {
	core->remove(path);
}

void Interface::file_size(std::string path) {
	core->file_size(path);
}

void Interface::storage() {
	core->storage();
}

void Interface::elem_info(std::string path) {
	core->elem_info(path);
}

void Interface::elem_info() {
	core->elem_info();
}

void Interface::plus_group_mode(Document::Access mode, std::string path) {
	core->plus_group_mode(mode, path);
}

void Interface::sub_group_mode(Document::Access mode, std::string path) {
	core->sub_group_mode(mode, path);
}

void Interface::plus_user_mode(Document::Access mode, std::string path) {
	core->plus_user_mode(mode, path);
}

void Interface::sub_user_mode(Document::Access mode, std::string path) {
	core->sub_user_mode(mode, path);
}

void Interface::change_owner(std::string username, std::string path) {
	core->change_owner(username,path);
}

void Interface::change_group(std::string groupname, std::string path) {
	core->change_group(groupname,path);
}