#ifndef THREAD_SAFE_VECTOR_H
#define THREAD_SAFE_VECTOR_H

#include <vector>
#include <boost/thread.hpp>

template <class T>
class ThreadSafeVector {

public:
	ThreadSafeVector() {};

	void push_back(const T &type) {
		mutex->lock();
		vector.push_back(type);
		mutex->unlock();
	}

	T at(unsigned int index) {
		mutex->lock();
		T type = vector.at(index);
		mutex->unlock();
		return type;
	}

	unsigned int size() {
		mutex->lock();
		unsigned int n = vector.size();
		mutex->unlock();
		return n;
	}

	boost::mutex* mutex;

private:
	std::vector<T> vector;
};

#endif