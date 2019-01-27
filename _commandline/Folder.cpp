#include "Folder.hpp"
#include "User.hpp"
#include "Group.hpp"

Folder::Folder() : Document() {}

Folder::Folder(User* user, std::string name, Document* station, Group* group)
	: Document(user, name, station, group) {}

Document* Folder::subset_folder(std::string subset_name) {
	if(subset_name == ".")
		return this;
	else if(subset_name == "..")
		return station;
	else
	for(int i=0; i<contents.size(); i++)
		if(contents[i]->is_same_folder(subset_name))
			return contents[i];
	throw new No_such_directory(subset_name);
}

Document* Folder::select_file(std::string file_name) {
	for(int i=0; i<contents.size(); i++)
		if(contents[i]->is_same_file(file_name))
			return contents[i];
	throw new No_such_file(file_name);
}

Folder::~Folder() {
	for(int i=0; i<contents.size(); i++)
		delete contents[i];
}

bool Folder::is_same_folder(std::string other_name) {
	return this->name == other_name;
}

bool Folder::check_name_exist(std::string name) {
	for(int i=0; i<contents.size(); i++)
		if(contents[i]->is_same_document(name))
			return true;
	return false;
}

void Folder::push(Document* doc) {
	contents.push_back(doc);
}

std::string Folder::get_name() {
	return (name + '/');
}

void Folder::list_contents() {
	for(int i=0; i<contents.size(); i++)
		std::cout << contents[i]->get_name() << std::endl;
}

void Folder::remove(std::string doc_name) {
	for(int i=0; i<contents.size(); i++)
		if(contents[i]->is_same_document(doc_name)) {
			delete contents[i];
			contents.erase(contents.begin()+i);
			return;
		}

	throw new No_such_file(doc_name);
}

unsigned long Folder::size() {
	unsigned long total_size = 0;
	for(int i=0; i<contents.size(); i++)
		total_size += contents[i]->size();
	return total_size;
}

void Folder::show_info() {
    std::cout << "dir ";
    std::cout << Document::access_writer(owner_access) << " ";
    std::cout << Document::access_writer(group_access) << " ";
    std::cout << owner_user->get_user_name() << " ";
    std::cout << owner_group->get_name() << " ";
    std::cout << name << std::endl;
}

bool Folder::is_folder(std::string doc_name) {
	if(doc_name == "." || doc_name == "..")
		return true;
	for(int i=0; i<contents.size(); i++)
		if(contents[i]->is_same_folder(doc_name))
			return true;
	return false;
}

void Folder::show_folder_info() {
	for(int i=0; i<contents.size(); i++)
		contents[i]->show_info();
}

void Folder::add_group_access(Document::Access mode) {
	for(int i=0; i<contents.size(); i++)
		contents[i]->add_group_access(mode);

	Document::add_group_access(mode);
}

void Folder::sub_group_access(Document::Access mode) {
	for(int i=0; i<contents.size(); i++)
		contents[i]->sub_group_access(mode);

	Document::sub_group_access(mode);
}

void Folder::add_user_access(Document::Access mode) {
	for(int i=0; i<contents.size(); i++)
		contents[i]->add_user_access(mode);

	Document::add_user_access(mode);
}

void Folder::sub_user_access(Document::Access mode) {
	for(int i=0; i<contents.size(); i++)
		contents[i]->sub_user_access(mode);

	Document::sub_user_access(mode);
}

void Folder::change_owner(User* new_owner) {
	for(int i=0; i<contents.size(); i++)
		contents[i]->change_owner(new_owner);

	Document::change_owner(new_owner);
}

void Folder::change_group(Group* new_group) {
	for(int i=0; i<contents.size(); i++)
		contents[i]->change_group(new_group);

	Document::change_group(new_group);
}

bool Folder::hole_access(User* user, Document::Access mode) {
	if(!Document::hole_access(user,mode)) return false;
	else
	for(int i=0; i<contents.size(); i++)
		if(!(contents[i]->hole_access(user,mode)))
			return false;
	return true;
}