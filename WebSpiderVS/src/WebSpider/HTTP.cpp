#include "HTTP.h"

std::vector<std::string> HTTP::parse(std::string stringToParse) {
	std::vector<std::string> parseResult;
	
	boost::regex e("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",
               boost::regbase::normal | boost::regbase::icase);
	boost::regex_split(std::back_inserter(parseResult), stringToParse, e);

	//boost::algorithm::split_regex(parseResult, stringToParse, boost::regex("(http|ftp|https):\\/\\/[\\w\\-_]+(\\.[\\w\\-_]+)+([\\w\\-\\.,@?^=%&amp;:/~\\+#]*[\\w\\-\\@?^=%&amp;/~\\+#])?",  boost::regex::normal | boost::regbase::icase));
	//boost::algorithm::split_regex(parseResult, stringToParse, boost::regex("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",  boost::regex::normal | boost::regbase::icase));
	std::cout << parseResult.size() << " Links\n";
	for(unsigned int i = 0; i < parseResult.size();i++) {
		std::cout << i << parseResult[i] << "\n";
	}
	
	return parseResult;
}