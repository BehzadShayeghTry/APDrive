#ifndef MYEXEPTIOS_HPP
#define MYEXEPTIOS_HPP

#include <iostream>

class MyExeptions
{
public:
    MyExeptions(std::string);
    ~MyExeptions();
    virtual void error() = 0;
protected:
	std::string Error;
};

class Unknown_command : public MyExeptions {
public:
	Unknown_command(std::string);
	void error();
};

class No_user_joined : public MyExeptions {
public:
	No_user_joined(std::string);
	void error();
};

class Need_logout : public MyExeptions {
public:
	Need_logout(std::string);
	void error();
};

class Extra_arguments_in_command : public MyExeptions {
public:
	Extra_arguments_in_command(std::string);
	void error();
};

class Not_enough_arguments : public MyExeptions {
public:
	Not_enough_arguments(std::string);
	void error();
};

class Not_found_user : public MyExeptions {
public:
	Not_found_user(std::string);
	void error();
};

class Not_found_group : public MyExeptions {
public:
	Not_found_group(std::string);
	void error();
};

class Not_in_group : public MyExeptions {
public:
	Not_in_group(std::string);
	void error();
};

class Already_in_group : public MyExeptions {
public:
	Already_in_group(std::string);
	void error();
};

class Wrong_password : public MyExeptions {
public:
	Wrong_password(std::string);
	void error();
};

class Repetitive_user : public MyExeptions {
public:
	Repetitive_user(std::string);
	void error();
};

class Repetitive_document : public MyExeptions {
public:
	Repetitive_document(std::string);
	void error();
};

class Low_access : public MyExeptions {
public:
	Low_access(std::string);
	void error();
};

class No_such_directory : public MyExeptions {
public:
	No_such_directory(std::string);
	void error();
};

class No_such_file : public MyExeptions {
public:
	No_such_file(std::string);
	void error();
};

class Station_null : public MyExeptions {
public:
	Station_null(std::string);
	void error();
};

class Unknown_access_level : public MyExeptions {
public:
	Unknown_access_level(std::string);
	void error();
};

class pro_de_mote_possiblity : public MyExeptions {
public:
	pro_de_mote_possiblity(std::string);
	void error();
};

class Static_root : public MyExeptions {
public:
	Static_root(std::string);
	void error();
};

class Repetitive_group : public MyExeptions {
public:
	Repetitive_group(std::string);
	void error();
};

class Not_found_real_file : public MyExeptions {
public:
	Not_found_real_file(std::string);
	void error();
};

class Need_file_name : public MyExeptions {
public:
	Need_file_name(std::string);
	void error();
};

class Use_file_as_folder : public MyExeptions {
public:
	Use_file_as_folder(std::string);
	void error();
};

class Use_folder_as_file : public MyExeptions {
public:
	Use_folder_as_file(std::string);
	void error();
};

class user_without_group : public MyExeptions {
public:
	user_without_group(std::string);
	void error();
};

class access_denied : public MyExeptions {
public:
	access_denied(std::string);
	void error();
};

class something_else : public MyExeptions {
public:
	something_else(std::string);
	void error();
};

#endif