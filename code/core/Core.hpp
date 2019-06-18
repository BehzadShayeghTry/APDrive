#ifndef CORE_HPP
#define CORE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "User.hpp"
#include "Document.hpp"

class Folder;
class Group;

class Core
{
public:
    std::string dashboardBody();
    std::string userListBody();
    std::string pastePageBody(std::string, std::string);
    
    void upload_http(std::string, std::string);
    User::AccessLevel get_working_user_accesslevel();
    bool check_rw_access_http(Document*, Document::Access);
    bool check_hole_rw_access_http(Document*, Document::Access);
    std::string read_name_of_path(std::string);
    std::string show_media(std::string);

private:
    std::string userSettingIconBody(User::AccessLevel);
    std::string userIconBody(User::AccessLevel);
    std::string folderBody(Document*, int&);
    std::string trashInfoIconBody(Document*, int&);
    std::string trashIconBody(Document*);
    std::string infoIconBody(Document*, int&);
    std::string newDocumentBody(Document*, int&);
    std::string contentsBody(Document*, int&);
    std::string unableFolderBody(Document*, int&);
    std::string fileBody(Document*, int&);
    std::string fileIconsBody(Document*, int&);
    std::string readIconBody(Document*);
    std::string copyIconBody(Document*);
    std::string cutIconBody(Document*);
    std::string downloadIconBody(Document*, int&);
    std::string newIconBody(Document*, int&);
    std::string newFolderIconBody(Document*, int&);
    std::string newFileIconBody(Document*, int&);
    std::string addUserdoorIconBody(User::AccessLevel);
    std::string pasteFolderPageBody(Document*, int&, std::string, std::string);
    std::string pasteIconBody(Document*, std::string, std::string);
    std::string pasteContentsBody(Document*, std::string, std::string, int&);
    std::string unablePasteFolderPageBody(Document*, std::string, std::string);

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
    void promote(std::string, User::AccessLevel);
    void demote(std::string, User::AccessLevel);
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