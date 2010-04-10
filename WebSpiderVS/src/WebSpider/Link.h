#ifndef LINK_H
#define LINK_H

#include <string>
#include <iostream>
using namespace std;

class Link {

public:
	Link(std::string data);
	void init(std::string data);

	string	data;	// the whole data
	string	server;
	string	path;
	string	domain;
	bool	relative;

};

#endif