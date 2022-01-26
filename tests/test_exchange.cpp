#include <gtest/gtest.h>
#include <string>

#include "link_factory.h"

using std::string;
using namespace loodsman;

TEST(intergationTests, SenderConstructorTest)
{
    LinkFactory factory;
    LinkAsync* linkSender = factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    delete linkSender;
}

TEST(intergationTests, ReceiveConstructorTest)
{
    LinkFactory factory;
    ILink* linkListen = factory.create(LinkType::udp, 5000);

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkListen, nullptr);

    delete linkListen;
}

TEST(intergationTests, SyncExchangeTest)
{
    LinkFactory factory;
    LinkAsync* linkSender = factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    LinkFactory factoryListen;
    ILink* linkListen = factoryListen.create(LinkType::udp, 5000);

    result = factoryListen.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkListen, nullptr);

    // ------------------------------------

    string dataToSend{};

    for (int i = 0; i < (LOODSMAN_MAX_PACKET_LENGTH); i++)
    {
        dataToSend.append("K");
    }

    // ------------------------------------

    std::size_t sent_data_size = linkSender->send(dataToSend);

    EXPECT_EQ(linkSender->errorCode(), 0);
    EXPECT_EQ(sent_data_size, LOODSMAN_MAX_PACKET_LENGTH);

    string received_data(linkListen->receive());

    EXPECT_EQ(linkListen->errorCode(), 0);
    EXPECT_EQ(received_data.size(), LOODSMAN_MAX_PACKET_LENGTH);

    dataToSend = "Test message";
    sent_data_size = linkListen->send(dataToSend);

    EXPECT_EQ(linkListen->errorCode(), 0);
    EXPECT_EQ(sent_data_size, dataToSend.size());

    received_data = string(linkSender->receive());

    EXPECT_EQ(linkSender->errorCode(), 0);
    EXPECT_EQ(received_data.size(), dataToSend.size());

    delete linkListen;
    delete linkSender;
}

void sendHandler(std::size_t bytesTransferred)
{
    EXPECT_NE(bytesTransferred, 0);
}

void receiveHandler(const std::string& data)
{
    EXPECT_NE(data.size(), 0);
}

TEST(intergationTests, AsyncExchangeTest)
{
    LinkFactory factory;
    LinkAsync* linkSender = factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    int result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkSender, nullptr);

    LinkAsync* linkListen = factory.create(LinkType::udp, 5000);

    result = factory.errorCode();

    EXPECT_EQ(result, 0);
    ASSERT_NE(linkListen, nullptr);

    // ------------------------------------

    string dataToSend{};

    for (int i = 0; i < (LOODSMAN_MAX_PACKET_LENGTH); i++)
    {
        dataToSend.append("K");
    }

    // ------------------------------------

    linkSender->asyncSend(dataToSend, sendHandler);

    linkListen->asyncReceive(receiveHandler);

    linkListen->checkHandlers();
    linkSender->checkHandlers();

    dataToSend = "Test message";

    linkListen->asyncSend(dataToSend, sendHandler);

    linkSender->asyncReceive(receiveHandler);

    linkListen->checkHandlers();
    linkSender->checkHandlers();
}
