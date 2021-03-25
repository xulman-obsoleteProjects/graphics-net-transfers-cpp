#include <iostream>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/NetException.h>

int main(int argc,char** argv)
{
	try {
		std::string msg("v1 points 2 dim 3 10 7.7 8.8 9.9 5 2 11 17.7 8.8 9.9 5 3");
		std::string msG("v1 points 2 dim 3 110 7.7 8.8 19.9 5 2 111 17.7 8.8 19.9 5 3");

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
