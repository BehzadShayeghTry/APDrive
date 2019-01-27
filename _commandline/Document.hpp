#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <iostream>
#include <vector>
#include "MyExeptions.hpp"

class User;
class Group;
class Folder;

class Document
{
public:
	enum Access {
		NONE,
		READ,
		WRITE,
		READ_WRITE
	};
public:
	Document();
	Document(User*,std::string,Document*,Group*);
	bool is_same_document(std::string);
	Document* get_station();
	std::string get_pure_name();
	bool is_owner_user(User*);
	Access get_access(User*);
	virtual std::string path();
	virtual std::string get_name();
	virtual void add_group_access(Access);
	virtual void sub_group_access(Access);
	virtual void add_user_access(Access);
	virtual void sub_user_access(Access);
	virtual void change_owner(User*);
	virtual void change_group(Group*);
	virtual bool hole_access(User*, Access);
	
	virtual void push(Document*);
	virtual Document* subset_folder(std::string);
	virtual Document* select_file(std::string);
	virtual bool is_same_folder(std::string);
	virtual bool is_same_file(std::string);
	virtual bool check_name_exist(std::string);
	virtual void list_contents();
	virtual std::vector<unsigned char> get_buffer();
	virtual void remove(std::string);
	virtual bool is_folder(std::string);
	virtual void show_folder_info();

	virtual unsigned long size() = 0;
	virtual void show_info() = 0;

protected:
	std::string access_writer(Access);

	Document* station;
	std::string name;
	User* owner_user;
	Group* owner_group;
	Access owner_access;
	Access group_access;
};

#endif