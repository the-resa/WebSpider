#ifndef WORK_H
#define WORK_H

#include "Runnable.h"
#include <iostream>

class Work : public Runnable {

public:
	Work(int d = 1);

	void run();

private:
	int data;
};

#endif