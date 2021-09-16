#include "udp_link_factory.h"
#include <gtest/gtest.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using namespace loodsman;

TEST(intergationTests, SenderConstructorTest)
{
    UdpLinkFactory factory(5001, "0.0.0.0", 5000, "127.0.0.1");
    ILink* linkSender = factory.create();

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    delete linkSender;
}

TEST(intergationTests, ReceiveConstructorTest)
{
    UdpLinkFactory factory(5000);
    ILink* linkListen = factory.create();

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkListen, nullptr);

    delete linkListen;
}

TEST(intergationTests, SyncExchangeTest)
{
    UdpLinkFactory factorySender(5001, "0.0.0.0", 5000, "127.0.0.1");
    ILink* linkSender = factorySender.create();

    int result = factorySender.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    UdpLinkFactory factoryListen(5000);
    ILink* linkListen = factoryListen.create();

    result = factoryListen.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkListen, nullptr);

    // ------------------------------------

    string dataToSend{};

    for (int i = 0; i < (MAX_PACKET_LENGTH); i++)
    {
        dataToSend.append("K");
    }

    // ------------------------------------

    cout << "Sending... " << endl;
    std::size_t sent_data_size = linkSender->send(dataToSend);
    cout << "Sent bytes: " << sent_data_size << endl;
    cout << "Error messages: " << linkSender->errorMessage() << endl;

    EXPECT_EQ(linkSender->errorCode(), 0);
    EXPECT_EQ(sent_data_size, MAX_PACKET_LENGTH);

    cout << "Listening..." << endl;
    ;
    string received_data(linkListen->receive());
    cout << "Error messages: " << linkListen->errorMessage() << endl;

    EXPECT_EQ(linkListen->errorCode(), 0);
    EXPECT_EQ(received_data.size(), MAX_PACKET_LENGTH);

    dataToSend = "Test message";
    cout << "Sending..." << endl;
    sent_data_size = linkListen->send(dataToSend);
    cout << "Sent bytes: " << sent_data_size << endl;
    cout << "Error messages: " << linkListen->errorMessage() << endl;

    EXPECT_EQ(linkListen->errorCode(), 0);
    EXPECT_EQ(sent_data_size, dataToSend.size());

    cout << "Listening" << endl;
    ;
    received_data = string(linkSender->receive());

    EXPECT_EQ(linkSender->errorCode(), 0);
    EXPECT_EQ(received_data.size(), dataToSend.size());

    delete linkListen;
    delete linkSender;
}

void sendHandler(std::size_t bytesTransferred)
{
    cout << "sendhandler:Sent bytes: " << bytesTransferred << endl;
    EXPECT_NE(bytesTransferred, 0);
}

void receiveHandler(const std::string& data)
{
    cout << "Receive handler:Received data: " << data << endl;
    EXPECT_NE(data.size(), 0);
}

TEST(intergationTests, AsyncExchangeTest)
{
    UdpLinkFactory factory(0);
    ILinkAsync* linkSender = factory.create(5001, "0.0.0.0", 5000, "127.0.0.1");

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    ILinkAsync* linkListen = factory.create(5000);

    result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkListen, nullptr);

    // ------------------------------------

    string dataToSend{};

    for (int i = 0; i < (MAX_PACKET_LENGTH); i++)
    {
        dataToSend.append("K");
    }

    // ------------------------------------

    cout << "Sending... " << endl;
    linkSender->asyncSend(dataToSend, sendHandler);

    //    cout << "Error messages: " << linkSender->errorMessage() << endl;

    //    EXPECT_EQ(linkSender->errorCode(), 0);

    cout << "Listening..." << endl;
    ;
    linkListen->asyncReceive(receiveHandler);

    factory.checkHandlers();

    //    cout << "Error messages: " << linkListen->errorMessage() << endl;
    //    EXPECT_EQ(linkListen->errorCode(), 0);

    dataToSend = "Test message";
    cout << "Sending..." << endl;

    linkListen->asyncSend(dataToSend, sendHandler);

    //    cout << "Error messages: " << linkListen->errorMessage() << endl;
    //
    //    EXPECT_EQ(linkListen->errorCode(), 0);

    //
    cout << "Listening" << endl;

    linkSender->asyncReceive(receiveHandler);

    factory.checkHandlers();

    //    delete linkListen;
    //    delete linkSender;
}
