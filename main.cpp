#include <iostream>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/NetException.h>

int main(int argc,char** argv)
{
	try {
		using namespace Poco::Net;
		HTTPClientSession session("www.seznam.cz",80);
		std::cout << "is connected? " << session.connected() << "\n"; //not yet

		HTTPRequest request(HTTPRequest::HTTP_GET, "/");
		session.sendRequest(request);
		//std::ostream &postDataGoesHere = session.sendRequest(request);
		std::cout << "is connected? " << session.connected() << "\n"; //already is

		HTTPResponse response;
		session.receiveResponse( response );

		std::cout << "got back: status = " << response.getStatus() << "\n";
		std::cout << "content starts:\n";
		response.write( std::cout );
		std::cout << "content ends:\n";
	}
	catch (Poco::Net::NetException& e) {
		std::cout << "Got exception: " << e.what() << "\n";
	}
	return 0;
}