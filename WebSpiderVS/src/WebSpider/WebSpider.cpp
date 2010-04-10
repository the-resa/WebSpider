#include "WebSpider.h"


void WebSpider::crawl(Link link) {

	crawledLinks.push_back(link);

	cout << "crawling URL: " << link.data << "\n\t(server: \"" + link.server << "\", path: \"" << link.path << "\", domain: \"" << link.domain << "\")\n";

	try
	{
		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(link.server, "http");
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

		request_stream << "GET " << link.path << " HTTP/1.0\r\n";
		request_stream << "Host: " << link.server << "\r\n";
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
			return;
		}
		if (status_code != 200)
		{
			cout << "Response returned with status code " << status_code << "\n";
			brokenLinks.push_back(link);
			cout << "Added broken link: " << link.data << endl;
			return;
		}
		
		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		string header;
		/*
		while (getline(response_stream, header) && header != "\r")
			cout << header << "\n";
		cout << "\n";
		

		// Write whatever content we already have to output.
		if (response.size() > 0)
			cout << &response;

		*/

		ostringstream ss;

		// Read until EOF, writing data to output as we go.
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error)) {
				//  cout << &response;
				ss << &response;
		}
		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);

		HTML html(ss.str());
		// binary search may be better
		for (int i = 0; i < crawledLinks.size(); i++) {
			for (int j = 0; j < html.links.size(); j ++) {
				if (crawledLinks.at(i).data != html.links.at(j).data) {

					// check relative link 
					if (html.links.at(j).relative == true) {
						html.links.at(j).init(link.server + html.links.at(j).path);
					}

#ifdef CRAWL_DOMAIN_ONLY
					if (html.links.at(j).domain == link.domain) 
#endif
						// call method recursive
						crawl(html.links.at(j));
				}
			}
		}
		
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << "\n";
	}
}