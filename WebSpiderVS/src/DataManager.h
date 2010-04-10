#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "WebSpider/URL.h"

class DataManager {
private:
	DataManager();

public:
	~DataManager();
	static DataManager& getInstance();

	std::vector<URL> crawledURLs;
	std::vector<URL> brokenURLs;
};

#endif
