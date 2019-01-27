#include "Group.hpp"
#include "User.hpp"

Group::Group(User* owner) {
	name = owner->get_user_name();
	members.push_back(owner);
}

Group::Group(std::string _name, User* creator) : name(_name) {
	members.push_back(creator);
}

Group::~Group() {}

void Group::add_member(User* member) {
	members.push_back(member);
}

bool Group::is_same_group(std::string other_group_name) {
    return this->name == other_group_name;
}

bool Group::has_same_member(User* other_member) {
	for(int i=0; i<members.size(); i++)
		if( members[i] == other_member ) return true;
	return false;
}

std::string Group::get_name() {
	return name;
}