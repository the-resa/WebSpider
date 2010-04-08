#ifndef HTTP_GETTER_H
#define HTTP_GETTER_H

#include "HTTP.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>



using boost::asio::ip::tcp;
using namespace std;

class HTTPGetter {


public:
	//HTTPGetter();
	//HTTP http;
	int get_http(string server, string path);
	ostream HTML;
	string server;
	string path;

};

#endif

