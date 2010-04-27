#ifndef RUNNABLE_H
#define RUNNABLE_H

class Runnable {
public:
	virtual void run() = 0;
	virtual ~Runnable() {}
};

#endif