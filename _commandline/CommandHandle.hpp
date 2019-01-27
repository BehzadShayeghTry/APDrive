#ifndef COMMANDHANDLE_HPP
#define COMMANDHANDLE_HPP

#include <iostream>
#include "MyExeptions.hpp"
#include <bits/stdc++.h>
#include "User.hpp"
#include "Document.hpp"

class Interface;

class CommandHandle
{
public:
    CommandHandle();
    void run();
    

private:
    void read_home_directory();
    void handle(std::istringstream&);
    void login(std::istringstream&);
    void logout();
    void add_user(std::istringstream&);
    void change_directory(std::istringstream&);
    void make_directory(std::istringstream&);
    void print_directory();
    void promote(std::istringstream&);
    void demote(std::istringstream&);
    void userlist();
    void add_group(std::istringstream&);
    void add_to_group(std::istringstream&);
    void upload(std::istringstream&);
    void download(std::istringstream&);
    void list_documents();
    void copy(std::istringstream&);
    void move(std::istringstream&);
    void remove(std::istringstream&);
    void file_size(std::istringstream&);
    void storage();
    void elem_info(std::istringstream&);
    void change_mode(std::istringstream&);
    void change_owner(std::istringstream&);
    void change_group(std::istringstream&);
    void print_commands();
    User::AccessLevel mote_reader(std::string);
    Document::Access mode_reader(std::string);

    Interface* interface;
};

#endif 