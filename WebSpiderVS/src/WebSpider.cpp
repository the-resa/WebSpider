#include "WebSpider.h"

WebSpider::WebSpider(string protocol, string host) {

	this->protocol = protocol;
	this->host = host;
	domain = host.substr(host.find_first_not_of("www."));
}

void WebSpider::crawl(string path, string link) {
	// start new thread for crawling
//	boost::thread crawlThread(boost::bind(&WebSpider::crawl, this, path));
//	boost::mutex mutex;
//	mutex.initialize();

	try {		

		bool hasBeenCrawledYet = false;
//		mutex.lock();
		// TODO: check if this loop is necessary
		for (unsigned int i = 0; i < crawledLinks.size(); i++) {
			if (path + link == crawledLinks.at(i))
				hasBeenCrawledYet = true;
		}
//		mutex.unlock();

		if (false == hasBeenCrawledYet) {
//			mutex.lock();
			crawledLinks.push_back(path + link);
//			mutex.unlock();


			cout << "crawling link: " << path << link << endl;
#ifdef DEBUG
			cout << "\tdomain: " << domain << endl;
#endif
			boost::asio::io_service io_service;

			// Get a list of endpoints corresponding to the host name.
			tcp::resolver resolver(io_service);
			tcp::resolver::query query(host, protocol);
			tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			tcp::resolver::iterator end;

			// Try each endpoint until we successfully establish a connection.
			tcp::socket socket(io_service);
			boost::system::error_code error = boost::asio::error::host_not_found;
			while (error && endpoint_iterator != end)
			{
				socket.close();
				socket.connect(*endpoint_iterator++, error);
			}
			if (error)
				throw boost::system::system_error(error);

			// Form the request. We specify the "Connection: close" header so that the
			// host will close the socket after transmitting the response. This will
			// allow us to treat all data up until the EOF as the content.
			boost::asio::streambuf request;
			ostream request_stream(&request);

			request_stream << "GET " << path << link << " HTTP/1.0\r\n";
			request_stream << "Host: " << host << "\r\n";
			request_stream << "Accept: */*\r\n";
			request_stream << "Connection: close\r\n\r\n";

			// Send the request.
			boost::asio::write(socket, request);

			// Read the response status line.
			boost::asio::streambuf response;
			boost::asio::read_until(socket, response, "\r\n");

			// Check that response is OK.
			istream response_stream(&response);
			string http_version;
			response_stream >> http_version;
			unsigned int status_code;
			response_stream >> status_code;
			string status_message;
			getline(response_stream, status_message);
			if (!response_stream || http_version.substr(0, 5) != "HTTP/")
			{
				cout << "Invalid response\n";
			}
			if (status_code == 200)
			{
				// Read the response headers, which are terminated by a blank line.
				boost::asio::read_until(socket, response, "\r\n\r\n");

				ostringstream ss;

				// Read until EOF, writing data to output as we go.
				while (boost::asio::read(socket, response,
					boost::asio::transfer_at_least(1), error)) {
						//  cout << &response;
						ss << &response;
				}
				if (error != boost::asio::error::eof)
					throw boost::system::system_error(error);		

				vector<string> links;

				// TODO: href= can also start with ' instead of " ; nice-to-have: regex filter last path
				boost::regex e("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",
					boost::regbase::normal | boost::regbase::icase);
				boost::regex_split(std::back_inserter(links), ss.str(), e);

				boost::regex n("<\\s*A\\s+[^>]*href\\s*=\\s*\'([^\']*)\'",		// TODO: href= can also start with ' instead of " ; nice-to-have: regex filter last path
					boost::regbase::normal | boost::regbase::icase);
				boost::regex_split(std::back_inserter(links), ss.str(), n);


//				mutex.lock();
				for (unsigned int i = 0; i < links.size(); i++) {
					string newPath, newLink;
					// check relative link
					if (links.at(i).find(protocol) == string::npos) {
						// ignore links with "..", "#" or "javascript:"
						if (links.at(i).find("..") == string::npos && links.at(i).find("#") == string::npos && links.at(i).find("javascript:") == string::npos) {
							// check new dirs
							if (links.at(i).find("/") != string::npos) {
								newPath = path + links.at(i).substr(0, links.at(i).find_last_of("/") + 1);
								newLink = links.at(i).substr(links.at(i).find_last_of("/") + 1);
							}
							// relative link in same dir
							else {
								newPath = path;
								newLink = links.at(i);
							}
//							crawlThread.join();
							// crawl new link
							crawl(newPath, newLink);
						}
					}
				}
//				mutex.unlock();
			}
			else {
//				mutex.lock();
				brokenLinks.push_back(path + link);
//				mutex.unlock();
				cout << "Added broken link: " << path << link << endl;
			}
		}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << "\n";
	}

}