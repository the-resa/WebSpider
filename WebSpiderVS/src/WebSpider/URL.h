#ifndef URL_H
#define URL_H

include "Parsable.h"

class URL: public Parsable {

public:
	std::vector<std::string> subdomains;

};

#endif