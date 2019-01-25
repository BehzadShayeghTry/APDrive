#ifndef GROUP_HPP
#define GROUP_HPP

#include <iostream>
#include <vector>
class User;

class Group {
public:
	Group(User*);
	Group(std::string, User*);
	~Group();
	void add_member(User*);
	bool is_same_group(std::string);
	bool has_same_member(User*);
	std::string get_name();

private:
	std::string name;
	std::vector<User*> members;
};

#endif