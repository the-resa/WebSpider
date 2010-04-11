#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "WebSpider/URL.h"

class DataManager {
private:
	DataManager();

public:
	~DataManager();
	static DataManager& getInstance();

	std::vector<string>	crawledURLs;
	std::vector<string>	brokenURLs;
	std::string			protocol;
	std::string			server;
};

#endif
