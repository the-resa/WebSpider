#include "URL.h"
#include "../DataManager.h"

URL::URL(std::string data) {

	this->data = data;

	try {
		// filter protocol (may be done in regex!!)
		if (data.find(":") != string::npos) {
			protocol = data.substr(0, data.find(":"));

			string restURL = data.substr(data.find(":") + 3);	// url without protocol, +3 because of "://" after "http"

			// split restURL into server and path
			if (restURL.find("/") != string::npos) { // may not be safe (int == npos (?) )
				server = restURL.substr(0, restURL.find_first_of("/"));
				path = restURL.substr(restURL.find_first_of("/"));
				// append "/" to path if neccesary
				if (path.at(path.size() - 1) != '/')
					path.append("/");
			}
			else {
				server = restURL;
				path = "/";
			}
		}

		// overwrite data to correct data
		data = protocol + "://" + server + path;

		// filter domain (may be done with regex!!!)
		if ("www." == server.substr(0,4)) 
			domain = server.substr(4);
		else
			domain = server;

		cout << "crawling URL: " << protocol << "://" << server << path << " (domain: \"" << domain << "\")\n";

		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(server, protocol);
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
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		ostream request_stream(&request);

		request_stream << "GET " << path << " HTTP/1.0\r\n";
		request_stream << "Host: " << server << "\r\n";
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
			/*
			HTML html(ss.str());
			// binary search may be better
			for (int i = 0; i < urls.size(); i++) {
			for (int j = 0; j < crawledURLs.size(); j ++) {
			if (html.urls.at(i).data != crawledURLs.at(j).data) {

			// check relative url 
			if (html.urls.at(i).protocol == "") {
			html.urls.at(i).init(url.protocol + "://" + url.server + html.urls.at(i).data); // data is path in this case
			}

			#ifdef CRAWL_DOMAIN_ONLY
			if (html.urls.at(i).domain == url.domain) 
			#endif
			// call method recursive
			crawl(html.urls.at(i));
			}
			}
			}
			*/		

			vector<string> parseResult;

			boost::regex e("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",
				boost::regbase::normal | boost::regbase::icase);
			boost::regex_split(std::back_inserter(parseResult), ss.str(), e);

			//boost::algorithm::split_regex(parseResult, stringToParse, boost::regex("(http|ftp|https):\\/\\/[\\w\\-_]+(\\.[\\w\\-_]+)+([\\w\\-\\.,@?^=%&amp;:/~\\+#]*[\\w\\-\\@?^=%&amp;/~\\+#])?",  boost::regex::normal | boost::regbase::icase));
			//boost::algorithm::split_regex(parseResult, stringToParse, boost::regex("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",  boost::regex::normal | boost::regbase::icase));


			for(unsigned int i = 0; i < parseResult.size(); i++) {
				for (unsigned int j = 0; j < DataManager::getInstance().crawledURLs.size(); j++) {
					if (parseResult.at(i) != DataManager::getInstance().crawledURLs.at(j).data) {
#ifdef DEBUG
						cout << "New URL found: \"" << parseResult.at(i) << "\"\n";
#endif
//						URL url(parseResult[i]);
//						DataManager::getInstance().crawledURLs.push_back(url);

					}
				}
			}
		}
		else {
			cout << "Response returned with status code " << status_code << "\n";
			URL brokenURL(this->data);
			DataManager::getInstance().brokenURLs.push_back(brokenURL);
			cout << "Added broken url: " << data << endl;
		}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << "\n";
	}

}
