#include "link_factory.h"
#include <gtest/gtest.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using namespace loodsman;

TEST(intergationTests, SenderConstructorTest)
{
    LinkFactory factory;
    ILinkAsync* linkSender = factory.createIp(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    delete linkSender;
}

TEST(intergationTests, ReceiveConstructorTest)
{
    LinkFactory factory;
    ILink* linkListen = factory.createIp(LinkType::udp, 5000);

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkListen, nullptr);

    delete linkListen;
}

TEST(intergationTests, SyncExchangeTest)
{
    LinkFactory factory;
    ILinkAsync* linkSender = factory.createIp(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    LinkFactory factoryListen;
    ILink* linkListen = factoryListen.createIp(LinkType::udp, 5000);

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
    cout << "Send handler:Sent bytes: " << bytesTransferred << endl;
    EXPECT_NE(bytesTransferred, 0);
}

void receiveHandler(const std::string& data)
{
    cout << "Receive handler:Received data: " << data << endl;
    EXPECT_NE(data.size(), 0);
}

TEST(intergationTests, AsyncExchangeTest)
{
    LinkFactory factory;
    ILinkAsync* linkSender = factory.createIp(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    ILinkAsync* linkListen = factory.createIp(LinkType::udp, 5000);

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

    cout << "This message should be displayed before " << endl;


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
