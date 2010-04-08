#include "HTMLParser.h"

vector<string> HTMLParser::getURLs(string htmlToParse) {
	std::vector<std::string> parseResult;
	boost::algorithm::split_regex(parseResult, htmlToParse, boost::regex("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",  boost::regex::normal | boost::regbase::icase));
	
	return parseResult;
}