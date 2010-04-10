#include "HTML.h"

HTML::HTML(string data) {
	vector<string> parseResult;
	
	boost::regex e("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",
               boost::regbase::normal | boost::regbase::icase);
	boost::regex_split(std::back_inserter(parseResult), data, e);

	//boost::algorithm::split_regex(parseResult, stringToParse, boost::regex("(http|ftp|https):\\/\\/[\\w\\-_]+(\\.[\\w\\-_]+)+([\\w\\-\\.,@?^=%&amp;:/~\\+#]*[\\w\\-\\@?^=%&amp;/~\\+#])?",  boost::regex::normal | boost::regbase::icase));
	//boost::algorithm::split_regex(parseResult, stringToParse, boost::regex("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",  boost::regex::normal | boost::regbase::icase));

	for(unsigned int i = 0; i < parseResult.size();i++) {
		Link link(parseResult[i]);
		links.push_back(link);
		cout << "URL found: " << link.data << endl;
	}
}