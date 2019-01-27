#include "File.hpp"
#include "User.hpp"
#include "Group.hpp"


std::string File::info_http() {
    std::string info;
    info += name + " | ";
    info += "file | ";
    info += owner_user->get_user_name() + " | ";
    info += Document::access_writer(owner_access) + " | ";
    info += owner_group->get_name() + " | ";
    info += Document::access_writer(group_access) + " | ";
    info += std::to_string(size()) + " bytes";
    return info;
}

// ------------------------------------------------------------------------------------

File::File(User* user, std::string name, Document* station, Group* group, std::vector<unsigned char> _buffer)
	: Document(user, name, station, group) , buffer(_buffer) {}

File::File(User* user, std::string name, Document* station, Group* group, Document* sorce)
	: Document(user, name, station, group) , buffer(sorce->get_buffer()) {}

File::~File() {}

std::vector<unsigned char> File::get_buffer() { return buffer; }

bool File::is_same_file(std::string other_name) { 
	return (this->name == other_name);
}

unsigned long File::size() {
	return buffer.size();
}

void File::show_info() {
    std::cout << "file ";
    std::cout << Document::access_writer(owner_access) << " ";
    std::cout << Document::access_writer(group_access) << " ";
    std::cout << owner_user->get_user_name() << " ";
    std::cout << owner_group->get_name() << " ";
    std::cout << name << std::endl;
}