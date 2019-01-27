#ifndef USER_HPP
#define USER_HPP

#include <iostream>

class Folder;
class Group;

class User
{
public:
    enum AccessLevel {
        USER,
        ADMIN,
        SUPERUSER,
        ROOT
    };

public:
    User(Folder*);
    User(std::string, std::string, Folder*);
    ~User();
    bool is_same_user(std::string);
    bool check_password(std::string);
    std::string get_user_name();
    AccessLevel get_access_level();
    Folder* get_home();
    void change_access_level(AccessLevel);
    Group* get_own_group();

private:
    std::string user_name;
    std::string password;
    AccessLevel access_level;
    Folder* home;
    Group* own_group;
};




#endif