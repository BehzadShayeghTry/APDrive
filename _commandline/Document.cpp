#include "Document.hpp"
#include "User.hpp"
#include "Group.hpp"

Document::Document() {
    station = NULL;
    name = "";
    owner_user = NULL;
    owner_group = NULL;
    owner_access = NONE;
    group_access = NONE;
}

Document::Document(User* owner, std::string doc_name, Document* state, Group* group) {
	station = state;
	name = doc_name;
	owner_user = owner;
	owner_group = group;
	state->push(this);
	owner_access = READ_WRITE;
	group_access = NONE;
}

bool Document::is_same_document(std::string other_name) {
	return this->name == other_name;
}

Document* Document::get_station() {
	if (station == NULL)
		throw new Station_null("");
	return station;
}

std::string Document::path() {
	std::vector<std::string> dirs;
	Document* dir = this;
	while(dir->station != NULL) {
		dirs.push_back(dir->name);
		dir = dir->station;
	}
	std::string path;
	for(int i=dirs.size()-1; i>=0; i--)
		path += "/" + dirs[i];
	return path;
}

std::string Document::get_name() {
	return name;
}
std::string Document::get_pure_name() {
	return name;
}

bool Document::is_owner_user(User* other_user) {
	return (this->owner_user == other_user);
}

Document::Access Document::get_access(User* user) {
	Document::Access access = NONE;
	if(is_owner_user(user))
		access = owner_access;
	
	if(owner_group->has_same_member(user)) {
		access = (access == READ_WRITE) ? READ_WRITE :
				 (group_access == READ_WRITE) ? READ_WRITE :
				 (access == READ && group_access == WRITE) ? READ_WRITE :
				 (access == WRITE && group_access == READ) ? READ_WRITE :
				 (access == group_access) ? access :
				 (group_access == NONE) ? access :
				 (access == NONE) ? group_access :
				 NONE;
	}
	return access;
}

void Document::add_group_access(Document::Access mode) {
	if(group_access == READ_WRITE) return;
	else if(group_access == mode) return;
	else if(group_access == NONE) group_access = mode;
	else group_access = READ_WRITE;
}

void Document::sub_group_access(Document::Access mode) {
	if(group_access == NONE) return;
	else if(group_access == mode) group_access = NONE;
	else if(group_access = READ_WRITE) {
		if(mode == READ) group_access = WRITE;
		if(mode == WRITE) group_access = READ;
	}
	else return;
}

void Document::add_user_access(Document::Access mode) {
	if(owner_access == READ_WRITE) return;
	else if(owner_access == mode) return;
	else if(owner_access == NONE) owner_access = mode;
	else owner_access = READ_WRITE;
}

void Document::sub_user_access(Document::Access mode) {
	if(owner_access == NONE) return;
	else if(owner_access == mode) owner_access = NONE;
	else if(owner_access = READ_WRITE) {
		if(mode == READ) owner_access = WRITE;
		if(mode == WRITE) owner_access = READ;
	}
	else return;
}

void Document::change_owner(User* new_owner) {
	owner_user = new_owner;
}

void Document::change_group(Group* new_group) {
	owner_group = new_group;
}

bool Document::hole_access(User* user, Document::Access mode) {
	return (get_access(user)==READ_WRITE || mode==NONE || get_access(user)==mode);
}


void Document::push(Document* doc) {
	throw new Use_file_as_folder("enternal document");
}
bool Document::is_same_folder(std::string other_name) {
	return false;
}
bool Document::is_same_file(std::string other_name) {
	return false;
}
Document* Document::subset_folder(std::string subset_name) {
	throw new Use_file_as_folder("subset");
}
Document* Document::select_file(std::string file_name) {
	throw new Use_file_as_folder("select_file");
}
bool Document::check_name_exist(std::string) {
	throw new Use_file_as_folder("enternal document");
}
void Document::list_contents() {
	throw new Use_file_as_folder("enternal document");
}
std::vector<unsigned char> Document::get_buffer() {
	throw new Use_folder_as_file("file buffer");
}
void Document::remove(std::string doc_name) {
	throw new Use_folder_as_file("enternal document");
}
bool Document::is_folder(std::string doc_name) {
	throw new Use_folder_as_file("enternal document");
}
void Document::show_folder_info() {
	throw new Use_folder_as_file("enternal document");
}


std::string Document::access_writer(Document::Access acc) {
    if( acc == Document::NONE ) return "-,-";
    if( acc == Document::READ ) return "read,-";
    if( acc == Document::WRITE ) return "-,write";
    if( acc == Document::READ_WRITE) return "read,write";
    else return "-,-";
}