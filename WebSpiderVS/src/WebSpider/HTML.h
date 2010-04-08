#ifndef HTML_H
#define HTML_H

#include "Parsable.h"
#include "URL.h"

class HTML: public Parsable {

public:
	std::vector<URL> urls;

};

#endif