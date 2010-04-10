#ifndef URL_H
#define URL_H

#include <string>
#include <iostream>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

#define DEBUG

class URL {

public:
	URL(std::string data);

	string	data;	// the whole data
	string	server;
	string	path;
	string	domain;
	string	protocol;
};

#endif