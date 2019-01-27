#ifndef CORE_HPP
#define CORE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "MyExeptions.hpp"
#include "User.hpp"
#include "Document.hpp"

class Document;
class Folder;
class Group;

class Core
{
public:
    Core();
    std::string get_working_username();
    std::string get_working_path();
    void set_home_directory(std::string);
    void login(std::string, std::string);
    void logout();
    void add_user(std::string, std::string);
    void change_directory(std::string);
    void make_directory(std::string);
    void print_directory();
    void promote(std::string, User::AccessLevel Mote);
    void demote(std::string, User::AccessLevel Mote);
    void userlist();
    void add_group(std::string);
    void add_to_group(std::string, std::string);
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
    int index_user(std::string);
    int index_group(std::string);
    Document* find_diraction(Document*, std::vector<std::string>);
    std::vector<std::string> read_path(std::string);
    bool check_name_exist(std::string);
    void print_users_list();
    std::string access_level_reader(User::AccessLevel);
    Document* find_file_or_folder(std::string);
    void check_on_time_user();
    void check_rw_access(Document*, Document::Access);
    void check_hole_rw_access(Document*, Document::Access);

    std::string home_directory;
    Folder* Root;
    User* on_time_user;
    Document* on_time_directory;
    std::vector<User*> users;
    std::vector<Group*> groups;
};

#endif