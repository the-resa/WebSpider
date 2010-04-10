#ifndef HTML_H
#define HTML_H

#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <iostream>

#include "Link.h"

using namespace std;

class HTML {
public:
	HTML(string data);
	vector<Link> links;
};

#endif