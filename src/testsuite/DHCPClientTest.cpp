#include "DHCPClientTest.h"
#include <Poco/CppUnit/TestCaller.h>
#include <Poco/CppUnit/TestSuite.h>
#include <Poco/Net/NetWorkInterface.h>

using Poco::Net::IPAddress;

DHCPClientTest::DHCPClientTest(const std::string& rName) :
CppUnit::TestCase(rName)
{
}


DHCPClientTest::~DHCPClientTest()
{
}


void DHCPClientTest::testTimeSync()
{
	assert(_dhcpClient.Request(std::string("local")));
}


CppUnit::Test* DHCPClientTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DHCPClientTest");

	CppUnit_addTest(pSuite, DHCPClientTest, testTimeSync);

	return pSuite;
}
