#ifndef HTTP_H
#define HTTP_H

#include "HTML.h"
#include "Parsable.h"

class HTTP: public Parsable {

public:
	HTTP(std::string data):
	  Parsable(data){
		  this->data = data;
	  }
private:
	std::vector<std::string> parse(std::string stringToParse);
	HTML* html;
	std::string method;
};

#endif

