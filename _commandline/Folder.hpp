#ifndef FOLDER_H
#define FOLDER_H

#include <iostream>
#include <vector>
#include "MyExeptions.hpp"
#include "Document.hpp"

class Folder : public Document
{
public:
	Folder();
	Folder(User*,std::string,Document*,Group*);
	~Folder();
	Document* subset_folder(std::string);
	Document* select_file(std::string);
	bool is_same_folder(std::string);
	bool check_name_exist(std::string);
	void push(Document*);
	std::string get_name();
	void list_contents();
	void remove(std::string);
	unsigned long size();
	void show_info();
	bool is_folder(std::string);
	void show_folder_info();
	void add_group_access(Access);
	void sub_group_access(Access);
	void add_user_access(Access);
	void sub_user_access(Access);
	void change_owner(User*);
	void change_group(Group*);
	bool hole_access(User*,Access);

private:
	std::vector<Document*> contents;
};

#endif