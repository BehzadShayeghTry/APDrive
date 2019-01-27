#include "User.hpp"
#include "Folder.hpp"
#include "Group.hpp"

User::User(Folder* Root) {
    user_name = "root";
    password = "root";
    access_level = ROOT;
    own_group = new Group(this);
    home = new Folder(this,"root", Root, own_group);
}

User::User(std::string _user_name, std::string _password, Folder* Root) {
    user_name = _user_name;
    password = _password;
    access_level = USER;
    own_group = new Group(this);
    home = new Folder(this,user_name, Root, own_group);
}

User::~User() {}

bool User::is_same_user(std::string other_user_name) {
    return this->user_name == other_user_name;
}

bool User::check_password(std::string other_password) {
    return this->password == other_password;
}

std::string User::get_user_name() {
    return user_name;
}

User::AccessLevel User::get_access_level() {
    return this->access_level;
}

Folder* User::get_home() {
    return this->home;
}

void User::change_access_level(AccessLevel newMote) {
    this->access_level = newMote;
}

Group* User::get_own_group() {
    return own_group;
}