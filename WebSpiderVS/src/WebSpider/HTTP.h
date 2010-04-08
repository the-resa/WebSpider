#ifndef HTTP_H
#define HTTP_H

#include "Parsable.h"
#include "HTML.h"

class HTTP: public Parsable {
	
public:
	std::string method;
	HTML html;
};

#endif