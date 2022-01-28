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

const string maxString = ::makeMaxString();
constexpr char testMessage[] = "Test message";
} // namespace

class IntergationTests : public ::testing::Test
{
protected:
    IntergationTests() = default;
    ~IntergationTests() override = default;

    LinkFactory m_linkFactory;

    void SetUp() override
    {
        // A placeholder for a future usage
    }

    void TearDown() override
    {
        // A placeholder for a future usage
    }
};

TEST_F(IntergationTests, SenderConstructorTest)
{
    unique_ptr<ILink> linkSender(
        m_linkFactory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);
    EXPECT_EQ(linkSender->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(m_linkFactory.errorCode(), boost::system::errc::errc_t::success);
}

TEST_F(IntergationTests, ReceiveConstructorUdpTest)
{
    unique_ptr<ILink> linkListen(m_linkFactory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);
    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(m_linkFactory.errorCode(), boost::system::errc::errc_t::success);
}

TEST_F(IntergationTests, ReceiveConstructorUnknownTest)
{
    unique_ptr<ILink> linkListen(m_linkFactory.create(static_cast<LinkType>(23), 5000));
    ASSERT_EQ(linkListen, nullptr);
}

TEST_F(IntergationTests, ReceiveConstructorBusyPortTest)
{
    unique_ptr<ILink> linkListen(m_linkFactory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);
    EXPECT_EQ(m_linkFactory.errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);

    unique_ptr<ILink> linkListenSamePort(m_linkFactory.create(LinkType::udp, 5000));
    ASSERT_EQ(linkListenSamePort, nullptr);
#ifdef _WIN32
    EXPECT_EQ(m_linkFactory.errorCode(), WSAEADDRINUSE);
#else
    EXPECT_EQ(m_linkFactory.errorCode(), boost::system::errc::errc_t::address_in_use);
#endif
}

TEST_F(IntergationTests, SyncExchangeTest)
{
    unique_ptr<ILink> linkSender(
        m_linkFactory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<ILink> linkListen(m_linkFactory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    string dataToSend = maxString;

    std::size_t sentDataSize = linkSender->send(dataToSend);

    EXPECT_EQ(linkSender->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(sentDataSize, LOODSMAN_MAX_PACKET_LENGTH);

    string receivedData(linkListen->receive());

    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(receivedData.size(), LOODSMAN_MAX_PACKET_LENGTH);
    EXPECT_EQ(receivedData, dataToSend);

    dataToSend = testMessage;
    sentDataSize = linkListen->send(dataToSend);

    EXPECT_EQ(linkListen->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(sentDataSize, dataToSend.size());

    receivedData = string(linkSender->receive());

    EXPECT_EQ(linkSender->errorCode(), boost::system::errc::errc_t::success);
    EXPECT_EQ(receivedData.size(), dataToSend.size());
    EXPECT_EQ(receivedData, dataToSend);
}

TEST_F(IntergationTests, AsyncExchangeTest)
{
    unique_ptr<LinkAsync> linkSender(
        m_linkFactory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<LinkAsync> linkListen(m_linkFactory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    string dataToSend = maxString;

    auto counterPtr = std::make_shared<int>(0);

    linkSender->asyncSend(dataToSend,
                          [dataToSend, counterPtr](std::size_t bytesTransferred) mutable {
                              EXPECT_EQ(bytesTransferred, dataToSend.size());
                              (*counterPtr)++;
                          });
    linkListen->asyncReceive([dataToSend, counterPtr](std::string_view dataReceived) mutable {
        EXPECT_EQ(dataToSend, dataReceived);
        (*counterPtr)++;
    });

    linkListen->checkHandlers();
    linkSender->checkHandlers();

    dataToSend = testMessage;

    linkSender->asyncSend(dataToSend,
                          [dataToSend, counterPtr](std::size_t bytesTransferred) mutable {
                              EXPECT_EQ(bytesTransferred, dataToSend.size());
                              (*counterPtr)++;
                          });
    linkListen->asyncReceive([dataToSend, counterPtr](std::string_view dataReceived) mutable {
        EXPECT_EQ(dataToSend, dataReceived);
        (*counterPtr)++;
    });

    linkListen->checkHandlers();
    linkSender->checkHandlers();

    EXPECT_EQ(*counterPtr, 4);
}

TEST_F(IntergationTests, AsyncExchangeRunTest)
{
    unique_ptr<LinkAsync> linkSender(
        m_linkFactory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<LinkAsync> linkListen(m_linkFactory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    string dataToSend = maxString;

    auto counterPtr = std::make_shared<int>(0);

    linkSender->asyncSend(dataToSend,
                          [dataToSend, counterPtr](std::size_t bytesTransferred) mutable {
                              EXPECT_EQ(bytesTransferred, dataToSend.size());
                              (*counterPtr)++;
                          });
    linkListen->asyncReceive([dataToSend, counterPtr](std::string_view dataReceived) mutable {
        EXPECT_EQ(dataToSend, dataReceived);
        (*counterPtr)++;
    });

    linkListen->runHandlers();
    linkSender->runHandlers();

    EXPECT_EQ(*counterPtr, 2);
}

TEST_F(IntergationTests, AsyncExchangeCloseOpenTest)
{
    unique_ptr<LinkAsync> linkSender(
        m_linkFactory.create(LinkType::udp, 5001, "0.0.0.0", 5000, "127.0.0.1"));
    ASSERT_NE(linkSender, nullptr);

    unique_ptr<LinkAsync> linkListen(m_linkFactory.create(LinkType::udp, 5000));
    ASSERT_NE(linkListen, nullptr);

    EXPECT_EQ(linkListen->close(), 0);

    string dataToSend = maxString;

    auto counterPtr = std::make_shared<int>(0);

    linkSender->asyncSend(dataToSend,
                          [dataToSend, counterPtr](std::size_t bytesTransferred) mutable {
                              EXPECT_EQ(bytesTransferred, dataToSend.size());
                              (*counterPtr)++;
                          });

    linkListen->asyncReceive([dataToSend, counterPtr](std::string_view dataReceived) mutable {
        EXPECT_EQ("", dataReceived);
        (*counterPtr)++;
    });

    linkListen->checkHandlers();
    linkSender->checkHandlers();

    EXPECT_EQ(linkListen->open(), 0);

    linkSender->asyncSend(dataToSend,
                          [dataToSend, counterPtr](std::size_t bytesTransferred) mutable {
                              EXPECT_EQ(bytesTransferred, dataToSend.size());
                              (*counterPtr)++;
                          });

    linkListen->asyncReceive([dataToSend, counterPtr](std::string_view dataReceived) mutable {
        EXPECT_EQ(dataToSend, dataReceived);
        (*counterPtr)++;
    });

    linkListen->checkHandlers();
    linkSender->checkHandlers();

    EXPECT_EQ(*counterPtr, 4);
}
