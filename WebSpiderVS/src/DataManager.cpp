#include "DataManager.h"

DataManager::DataManager() {

}

DataManager::~DataManager() {
	crawledURLs.clear();
	brokenURLs.clear();
}

DataManager& DataManager::getInstance()  {
	static DataManager instance;
	return instance;
}