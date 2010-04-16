#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

class DataManager {

private:
	DataManager();
	DataManager(const DataManager& cc);

public:
	~DataManager();
	static DataManager& getInstance();
};

DataManager& DataManager::getInstance() {
	static DataManager instance;
	return instance;
};

#endif