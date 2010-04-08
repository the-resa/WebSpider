#ifndef HTTP_H
#define HTTP_H

#include "HTML.h"
#include "Parsable.h"
#include <iostream>

class HTTP: public Parsable {

public:
	HTTP(std::string data):
	  Parsable(data){
		  this->data = data;
	  }
	  std::vector<std::string> parse(std::string stringToParse);
private:
	
	HTML* html;
	std::string method;
};

#endif

