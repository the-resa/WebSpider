#ifndef PARSABLE_H
#define PARSABLE_H

#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <string>
#include <vector>

class Parsable {

public:
	Parsable(std::string data);
	std::string getData() const;

protected:
	virtual std::vector<std::string> parse(std::string stringToParse) = 0;
	std::string data;

private:
	

};

#endif