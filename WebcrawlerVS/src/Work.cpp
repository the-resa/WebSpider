#include "Work.h"

Work::Work(int d):
data(d) 
{

}

void Work::run() {
	std::cout << "Work " << data << " being processed.\n";
}