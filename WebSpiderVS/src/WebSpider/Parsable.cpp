# include "Parsable.h"


std::vector<std::string> Parsable::parse(std::string stringToParse) {
	vector<std::string> parseResult;
	boost::algorithm::split_regex(parseResult, stringToParse, regex( "" /* hier regex rein */ ) ) ;
	return parseResult;
}
