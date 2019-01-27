#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include "User.hpp"
#include "Document.hpp"

class Core;

class Interface
{
public:
    Interface();
    std::string get_working_username();
    std::string get_working_path();
    void set_home_directory(std::string);
    void login(std::string, std::string);
    void logout();
    void add_user(std::string, std::string);
    void change_directory(std::string);
    void make_directory(std::string);
    void print_directory();
    void promote(std::string, User::AccessLevel);
    void demote(std::string, User::AccessLevel);
    void userlist();
    void add_group(std::string);
    void add_to_group(std::string,std::string);
    void upload(std::string, std::string);
    void download(std::string, std::string);
    void list_documents();
    void copy(std::string, std::string);
    void move(std::string, std::string);
    void remove(std::string);
    void file_size(std::string);
    void storage();
    void elem_info(std::string);
    void elem_info();
    void plus_group_mode(Document::Access, std::string);
    void sub_group_mode(Document::Access, std::string);
    void plus_user_mode(Document::Access, std::string);
    void sub_user_mode(Document::Access, std::string);
    void change_owner(std::string, std::string);
    void change_group(std::string, std::string);

private:
    Core* core;
};

#endif