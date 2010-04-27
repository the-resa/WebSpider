#ifndef WORK_H
#define WORK_H

class Work : public Runnable {
	
	public:
		Work(int d = 1) : data(d) {}

		void run() {
			printf("work %d being processed\n",
				data);
		}

	private:
		int data;
};

#endif