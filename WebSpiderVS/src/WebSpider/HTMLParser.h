#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <iostream>

using namespace std;

class HTMLParser {
public:
	vector<string> getURLs(string htmlToParse);
};

#endif