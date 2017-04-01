#include  <boost/asio.hpp>
#include <iostream>

#include "tcpclient.h"

void ClientSend()
{

	try
	{
		boost::asio::io_service ios;
		boost::system::error_code error;

		// 1. �ý������ķ���, ��������������, ��  
		// query("www.163.com","80"), Ҳ���� query("www.163.com","telnet")  
		// echo          7/tcp  
		// ftp           21/tcp                 # File Transfer Protocol (Control)  
		// telnet        23/tcp                 # Virtual Terminal Protocol  
		// smtp          25/tcp                 # Simple Mail Transfer Protocol  
		// time          37/tcp  timeserver     # Time  
		//      TCP::resolver resolver(ios);  
		//      TCP::resolver::query query("127.0.0.1", "10000");  
		//      TCP::resolver::iterator endpoint_iterator = resolver.resolve(query);  
		//      TCP::resolver::iterator end;  
		//      TCP::socket socket(ios);  
		//      socket.connect(*endpoint_iterator, error);  

		// 2. �ü��ķ���  
		boost::asio::ip::tcp::socket socket(ios);
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 10000);
		socket.connect(endpoint, error);

		// ����Ҫ�ж�һ��, ����û�����ϻ�ͨ��.  
		if (error)
			throw boost::system::system_error(error);

		while (true)
		{
			// boost::array<char, 128> buf;  
			std::vector<char> buf(128);
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			// ����ҲҪ�ж�һ��, �����������жϿ�, ����������ѭ��.  
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.  
			else if (error)
				throw boost::system::system_error(error); // Some other error.  

														  // bufҪע����ƴ�С��  
			socket.write_some(boost::asio::buffer(buf, len), error);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}