#ifndef PARSABLE_H
#define PARSABLE_H

#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <string>
#include <vector>

class Parsable {

public:
	std::vector<std::string> parse(std::string);
	std::string stringToParse;

private:
	

};

#endif