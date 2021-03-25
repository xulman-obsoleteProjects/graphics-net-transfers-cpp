#include <sstream>
#include <iostream>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/NetException.h>

int main(int argc,char** argv)
{
	int base = atoi(argv[1]);
	std::cout << "base for IDs is " << base << "\n";
	try {
		std::ostringstream a,b;
		a << "v1 points 2 dim 3 " << base << " 7.7 8.8 9.9 5 2 " << base+1 << " 17.7 8.8 9.9 5 3";
		b << "v1 points 2 dim 3 " << base+100 << " 7.7 8.8 19.9 5 2 " << base+101 << " 17.7 8.8 19.9 5 3";
		std::string msg(a.str());
		std::string msG(b.str());
		std::cout << "going to send: " << msg << "\n";
		std::cout << "going to send: " << msG << "\n";

		using namespace Poco::Net;
		HTTPClientSession session("localhost",8765);
		HTTPRequest request(HTTPRequest::HTTP_POST, "/simViewer");

		{
		request.setContentLength(msg.size());
		std::ostream &requestBody = session.sendRequest(request);
		requestBody << msg;
		}

		{
		request.setContentLength(msG.size());
		std::ostream &requestBody = session.sendRequest(request);
		requestBody << msG;
		}

		/*
		//hear back some acknowledgement:
		HTTPResponse response;
		std::istream &responseBody = session.receiveResponse(response);

		if (response.getStatus() != HTTPResponse::HTTP_OK)
			std::cerr << "couldn't transfer the message!\n";
		else
			std::cout << "message transferred!\n";

		/*
		//verbose report of what the receiving party has to say:
		std::cout << "got back: status = " << response.getStatus() << "\n";
		std::cout << "content starts:\n";
		response.write( std::cout );
		std::cout << "content middle:\n";
		std::string resMsg;
		while (responseBody >> resMsg) std::cout << resMsg << "\n";
		std::cout << "content ends:\n";
		*/
	}
	catch (Poco::Net::NetException& e) {
		std::cout << "Got exception: " << e.what() << "\n";
	}
	return 0;
}
