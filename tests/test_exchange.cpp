#include <gtest/gtest.h>
#include <memory>
#include <string_view>

#include "link_factory.h"

using std::string;
using std::unique_ptr;
using namespace loodsman;

class intergationTests : public ::testing::Test
{
protected:
    LinkFactory factory;

    intergationTests() = default;

    ~intergationTests() override = default;

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(intergationTests, SenderConstructorTest)
{
    unique_ptr<ILink> linkSender(factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);
    EXPECT_EQ(linkSender->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(factory.errorCode(), boost::system::errc::errc_t::success);
}

TEST_F(intergationTests, ReceiveConstructorUdpTest)
{
    unique_ptr<ILink> linkListen(factory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);
    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(factory.errorCode(), boost::system::errc::errc_t::success);
}

TEST_F(intergationTests, ReceiveConstructorUnknownTest)
{
    unique_ptr<ILink> linkListen(factory.create(static_cast<LinkType>(23), 5000));
    ASSERT_EQ(linkListen, nullptr);
}

TEST_F(intergationTests, ReceiveConstructorBusyPortTest)
{
    unique_ptr<ILink> linkListen(factory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);
    EXPECT_EQ(factory.errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);

    unique_ptr<ILink> linkListenSamePort(factory.create(LinkType::udp, 5000));
    ASSERT_EQ(linkListenSamePort, nullptr);
    EXPECT_EQ(factory.errorCode(), boost::system::errc::errc_t::address_in_use);
}

TEST_F(intergationTests, SyncExchangeTest)
{
    unique_ptr<ILink> linkSender(factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<ILink> linkListen(factory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    // ------------------------------------

    string dataToSend{};

    for (int i = 0; i < LOODSMAN_MAX_PACKET_LENGTH; i++)
    {
        dataToSend.append("K");
    }

    // ------------------------------------

    std::size_t sent_data_size = linkSender->send(dataToSend);

    EXPECT_EQ(linkSender->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(sent_data_size, LOODSMAN_MAX_PACKET_LENGTH);

    string received_data(linkListen->receive());

    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(received_data.size(), LOODSMAN_MAX_PACKET_LENGTH);

    dataToSend = "Test message";
    sent_data_size = linkListen->send(dataToSend);

    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(sent_data_size, dataToSend.size());

    received_data = string(linkSender->receive());

    EXPECT_EQ(linkSender->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(received_data.size(), dataToSend.size());
}

TEST_F(intergationTests, AsyncExchangeTest)
{
    unique_ptr<LinkAsync> linkSender(
        factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<LinkAsync> linkListen(factory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    // ------------------------------------

    string dataToSend{};

    for (int i = 0; i < LOODSMAN_MAX_PACKET_LENGTH; i++)
    {
        dataToSend.append("K");
    }

    // ------------------------------------

    auto counter_ptr = std::make_shared<int>(0);

    linkSender->asyncSend(dataToSend,
                          [dataToSend, counter_ptr](std::size_t bytesTransferred) mutable {
                              EXPECT_EQ(bytesTransferred, dataToSend.size());
                              (*counter_ptr)++;
                          });
    linkListen->asyncReceive([dataToSend, counter_ptr](std::string_view dataReceived) mutable {
        EXPECT_EQ(dataToSend, dataReceived);
        (*counter_ptr)++;
    });

    linkListen->checkHandlers();
    linkSender->checkHandlers();

    dataToSend = "Test message";

    linkSender->asyncSend(dataToSend,
                          [dataToSend, counter_ptr](std::size_t bytesTransferred) mutable {
                              EXPECT_EQ(bytesTransferred, dataToSend.size());
                              (*counter_ptr)++;
                          });
    linkListen->asyncReceive([dataToSend, counter_ptr](std::string_view dataReceived) mutable {
        EXPECT_EQ(dataToSend, dataReceived);
        (*counter_ptr)++;
    });

    linkListen->checkHandlers();
    linkSender->checkHandlers();

    EXPECT_EQ(*counter_ptr, 4);
}

TEST_F(intergationTests, AsyncExchangeRunTest)
{
    unique_ptr<LinkAsync> linkSender(
        factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<LinkAsync> linkListen(factory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    // ------------------------------------

    string dataToSend{};

    for (int i = 0; i < LOODSMAN_MAX_PACKET_LENGTH; i++)
    {
        dataToSend.append("Z");
    }

    // ------------------------------------

    auto counter_ptr = std::make_shared<int>(0);

    linkSender->asyncSend(dataToSend,
                          [dataToSend, counter_ptr](std::size_t bytesTransferred) mutable {
                              EXPECT_EQ(bytesTransferred, dataToSend.size());
                              (*counter_ptr)++;
                          });
    linkListen->asyncReceive([dataToSend, counter_ptr](std::string_view dataReceived) mutable {
        EXPECT_EQ(dataToSend, dataReceived);
        (*counter_ptr)++;
    });

    linkListen->runHandlers();
    linkSender->runHandlers();

    EXPECT_EQ(*counter_ptr, 2);
}
