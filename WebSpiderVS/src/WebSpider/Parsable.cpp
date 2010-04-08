# include "Parsable.h"


std::vector<std::string> Parsable::parse(std::string stringToParse) {
	std::vector<std::string> parseResult;
	boost::algorithm::split_regex(parseResult, stringToParse, boost::regex(  "" /* hier regex rein */ ) ) ;
	return parseResult;
}
