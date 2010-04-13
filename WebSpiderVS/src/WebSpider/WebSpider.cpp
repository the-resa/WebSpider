#include "WebSpider.h"


void WebSpider::crawlURL(string server) {

	crawledURLs.push_back(server);
	cout << "New URL crawled: " << server << endl;

	try
	{
		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(server, "http");
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
		std::ostream request_stream(&request);

		string path;
		if (server[server.size() - 1] == '/') 
			path = "";
		else
			path = "/";

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
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			std::cout << "Invalid response\n";
			return;
		}
		if (status_code != 200)
		{
			std::cout << "Response returned with status code " << status_code << "\n";
			brokenURLs.push_back(server);
			cout << "Added broken link: " << server << endl;
			return;
		}
		
		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		/*
		while (std::getline(response_stream, header) && header != "\r")
			std::cout << header << "\n";
		std::cout << "\n";
		*/

		// Write whatever content we already have to output.
		if (response.size() > 0)
			std::cout << &response;

		std::ostringstream ss;

		// Read until EOF, writing data to output as we go.
		while (boost::asio::read(socket, response,
			boost::asio::transfer_at_least(1), error)) {
				//  std::cout << &response;
				ss << &response;
		}
		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error);

		vector<string> urls = htmlParser.getURLs(ss.str());
		for (int i = 0; i < crawledURLs.size(); i++) {
			for (int j = 0; j < urls.size(); j ++) {
				if (crawledURLs.at(i) != urls.at(j))
					crawlURL(urls.at(j));
			}
		}
		
	}
	catch (std::exception& e)
	{
		server;
		std::cout << "Exception: " << e.what() << "\n";
	}
}