#include "WebSpider.h"

WebSpider::WebSpider(string protocol, string host)
{
	this->protocol = protocol;
	this->host = host;

	// set domain
	if (host.find("www.") != string::npos) {
		domain = host.substr(4);
	}
	else domain = host;

	crawledLinks.mutex = &mutex;
	brokenLinks.mutex = &mutex;

	elapsedTime = 0.0;
}

void WebSpider::crawl(string path, string file) {

	crawlTimer.restart();

#ifdef MULTITHREADING
	cout << "Threads running: " << threadGroup.size() << endl;
#endif

	try {		

		bool hasBeenCrawledYet = false;
		mutex.lock();
		for (unsigned int i = 0; i < crawledLinks.size(); i++) {
			if (path + file == crawledLinks.at(i))
				hasBeenCrawledYet = true;
		}
		mutex.unlock();

		if (false == hasBeenCrawledYet) {

			crawledLinks.push_back(path + file);

			cout << "crawling link: " << path << file << endl;
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

			request_stream << "GET " << path << file << " HTTP/1.0\r\n";
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

				mutex.lock();
				for (unsigned int i = 0; i < links.size(); i++) {
					string link = links.at(i);
					string newPath, newFile;
					// check relative link
					if (link.find("://") == string::npos) {
						// ignore links with "#" or "javascript:" or ".."
						if (link.find("#") == string::npos && link.find("javascript:") == string::npos && link.find("..") == string::npos) {
							// check new dirs
							if (link.find("/") != string::npos) {
								newPath = path + link.substr(0, link.find_last_of("/") + 1);
								newFile = link.substr(link.find_last_of("/") + 1);
							}
							// relative file in same dir
							else {
								newPath = path;
								newFile = link;
							}

							#ifdef MULTITHREADING
							mutex.lock();
							boost::thread thread(boost::bind(&WebSpider::crawl, this, path, file));
							threadGroup.add_thread(&thread);
							mutex.unlock();
							#endif
							// crawl new file recursive
							crawl(newPath, newFile);
						}
					}
					// absolute link
					else {
						// if link is in same domain
						if (link.find(domain) != string::npos) {
							newPath = link.substr(link.find(host));
							// if no "/" is found it's the root dir
							if (newPath.find("/") == string::npos) {
								newPath = "/";
								newFile = "";
							}
							else {
								newFile = link.substr(link.find_last_of("/") + 1);
								newPath = newPath.substr(newPath.find(host) + host.size());
								newPath = newPath.erase(newPath.find(newFile), newFile.size());
							}

							#ifdef MULTITHREADING
							mutex.lock();
							boost::thread thread(boost::bind(&WebSpider::crawl, this, path, file));
							threadGroup.add_thread(&thread);
							mutex.unlock();
							#endif
							// crawl file recursive
							crawl(newPath, newFile);

						}
					}
				}
				mutex.unlock();
			}
			else {
				brokenLinks.push_back(path + file);
				cout << "Added broken link: " << path << file << endl;
			}
#ifdef MUTLITHREADING
			mutex.lock();
#endif
			elapsedTime += crawlTimer.elapsed(); 
#ifdef MULTITHREADING
			mutex.unlock();
#endif
		}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << "\n";
	}

}