#include <gtest/gtest.h>
#include <memory>
#include <string_view>

#include "link_factory.h"

using std::string;
using std::unique_ptr;
using namespace loodsman;

namespace
{
string makeMaxString()
{
    string data{};
    while (data.size() < LOODSMAN_MAX_PACKET_LENGTH)
    {
        data.append("K");
    }
    return data;
}

constexpr char test_message[] = "Test message";

} // namespace

class intergationTests : public ::testing::Test
{
protected:
    LinkFactory factory;
    string maxString;

    intergationTests() : maxString(::makeMaxString())
    {
    }

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
#ifdef _WIN32
    EXPECT_EQ(factory.errorCode(), WSAEADDRINUSE);
#else
    EXPECT_EQ(factory.errorCode(), boost::system::errc::errc_t::address_in_use);
#endif
}

TEST_F(intergationTests, SyncExchangeTest)
{
    unique_ptr<ILink> linkSender(factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<ILink> linkListen(factory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    string dataToSend = maxString;

    std::size_t sent_data_size = linkSender->send(dataToSend);

    EXPECT_EQ(linkSender->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(sent_data_size, LOODSMAN_MAX_PACKET_LENGTH);

    string received_data(linkListen->receive());

    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(received_data.size(), LOODSMAN_MAX_PACKET_LENGTH);
    EXPECT_EQ(received_data, dataToSend);

    dataToSend = "Test message";
    sent_data_size = linkListen->send(dataToSend);

    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(sent_data_size, dataToSend.size());

    received_data = string(linkSender->receive());

    EXPECT_EQ(linkSender->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(received_data.size(), dataToSend.size());
    EXPECT_EQ(received_data, dataToSend);
}

TEST_F(intergationTests, AsyncExchangeTest)
{
    unique_ptr<LinkAsync> linkSender(
        factory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<LinkAsync> linkListen(factory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    string dataToSend = maxString;

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

    string dataToSend = maxString;

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
