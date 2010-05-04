CXXFLAGS = -Wall
CXX = g++ -g

all: webcrawler

webcrawler: src/main.o src/WebSpider.o
	$(CXX) -o $@ src/main.o src/WebSpider.o -lboost_thread-mt -lboost_regex-mt -lboost_system-mt

