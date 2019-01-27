#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include "MyExeptions.hpp"
#include "Document.hpp"

class File : public Document
{
public:
	File(User*,std::string,Document*,Group*, std::vector<unsigned char>);
	File(User*,std::string,Document*,Group*, Document*);
	~File();
	std::vector<unsigned char> get_buffer();
	bool is_same_file(std::string);
	unsigned long size();
	void show_info();

private:
	std::vector<unsigned char> buffer;
};

#endif