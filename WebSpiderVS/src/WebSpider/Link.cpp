#include "Link.h"


Link::Link(string data) {
	init(data);
}

void Link::init(std::string data) {

	this->data = data;
	relative = false;

	// filter "http://" (may be done in regex!!)
	if (data.substr(0, 7) == "http://") {
		data = data.substr(7);

		// split data into server and path
		int indexOfFirstSlash = data.find("/");
		if (indexOfFirstSlash != string::npos) { // may not be safe (int == npos (?) )
			server = data.substr(0, indexOfFirstSlash);
			path = data.substr(indexOfFirstSlash);
			// append "/" to path if neccesary
			if (path.at(path.size() - 1) != '/')
				path.append("/");
		}
		else {
			 server = data;
			 path = "/";
		}

		// overwrite data to correct data
		data = server + path;

		// filter domain (may be done with regex!!!)
		if ("www." == server.substr(0,4)) 
			domain = server.substr(4);
		else
			domain = server;
	}
	else
		relative = true;
}