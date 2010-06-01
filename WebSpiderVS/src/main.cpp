#include "WebSpider.h"
#include <boost/timer.hpp>
#include <ctime>

#ifdef WIN32
#include "wingetopt.h"
#endif

int main(int argc, char* argv[]) 
{

	string protocol = "http";
	string server = "www.wrel.de";
	string link = "/frick/Demosite/";
	string file = "";

	int opt=0;

	while((opt = getopt(argc, argv, "p:s:l:f"))!= -1)  
	{  
		switch(opt)  {  
			case 'p':   
				protocol = optarg;
			break;
			
			case 's':  
				server = optarg;  
				break;  
			
			case 'l':  
				link = optarg;  
				break;  

			case 'f':   
				file = optarg;
				break;  

			default:    
				cout << "Unknown option. Standard-parameter will be used.\n"; 
				break; 
		}  
	} 

	cout << "The crawling will start from the following site:\n" <<
		"\t" << protocol + "://" + server + link + file << endl;

	time_t start, end;
	WebSpider spider(protocol, server);

	cout << "Enter any key to start crawling\n";
	int key;
	cin >> key;

	time(&start);
	spider.crawl(link, file);

	while (true) {
		if (0 == spider.getThreadNum()) {
#ifdef WIN32
			Sleep(1000); // sleep one second to wait if there are still threads running
#else
			sleep(1);
#endif
			if (0 == spider.getThreadNum()) {
				break;
			}
		}
	}

	time(&end);

	std::cout << "Links crawled: " << spider.crawledLinks.size() << std::endl;
	std::cout << "Broken links found: " << spider.brokenLinks.size() << std::endl;
	std::cout << "Broken links in percent: " << (float)spider.brokenLinks.size() / (float)spider.crawledLinks.size() * 100 << std::endl;
	std::cout << "Elapsed time: " << difftime(end, start) << std::endl;
#ifdef WIN32
	system("PAUSE");
#endif
	return 0;
}
