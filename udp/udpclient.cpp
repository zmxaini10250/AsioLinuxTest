#include <boost/asio.hpp>
#include <iostream>

#include "udpclient.h"

void ClientSend()
{
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket(io_service);
	boost::asio::ip::udp::endpoint end_point(boost::asio::ip::address::from_string("127.0.0.1"), 7474);
	socket.open(end_point.protocol());
	while (true)
	{
		std::string input_data;
		std::cin >> input_data;
		try
		{
			socket.send_to(boost::asio::buffer(input_data.c_str(), input_data.size()), end_point);
		}
		catch (boost::system::system_error &e)
		{
			std::cout << "process failed:" << e.what() << std::endl;
		}
	}
}
