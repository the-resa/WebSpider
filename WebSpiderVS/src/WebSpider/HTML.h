#ifndef HTML_H
#define HTML_H

#include "Parsable.h"

class HTML: public Parsable {

public:
	HTML(std::string data): 
	  Parsable(data) {
	  }

	std::vector<std::string> urls;

};

#endif