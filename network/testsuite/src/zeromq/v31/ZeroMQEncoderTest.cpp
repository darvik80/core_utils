//
// Created by Ivan Kishchenko on 05.02.2022.
//

#include "ZeroMQEncoderTest.h"
#include "ZeroMQTestData.h"
#include "network/zeromq/v31/ZeroMQEncoder.h"

namespace network::zeromq::v31 {

    BOOST_FIXTURE_TEST_SUITE(ZeroMQEncoderV31Test, ZeroMQEncoderV31Fixture)

        BOOST_AUTO_TEST_CASE(testCmdReadyEncode) {
            ZeroMQEncoder encoder;

            ZeroMQCommand cmd(ZERO_MQ_CMD_READY);
            cmd.props.emplace(ZERO_MQ_PROP_SOCKET_TYPE, ZERO_MQ_SOCKET_TYPE_PUB);

            network::ArrayBuffer<128> buf;
            std::error_code success;
            BOOST_REQUIRE_EQUAL(success, encoder.write(buf, cmd));
            BOOST_REQUIRE_EQUAL(27, buf.size());

            BOOST_REQUIRE_EQUAL_COLLECTIONS(&rawCmdReady[0], &rawCmdReady[26], &buf.data()[0], &buf.data()[26]);
        }

        BOOST_AUTO_TEST_CASE(testCmdSubEncode) {
            ZeroMQEncoder encoder;

            ZeroMQCommand cmd(ZERO_MQ_CMD_SUBSCRIBE);
            cmd.props.emplace(ZERO_MQ_PROP_SUBSCRIPTION, "test");

            network::ArrayBuffer<128> buf;
            std::error_code success;
            BOOST_REQUIRE_EQUAL(success, encoder.write(buf, cmd));
            BOOST_REQUIRE_EQUAL(16, buf.size());

            BOOST_REQUIRE_EQUAL_COLLECTIONS(&rawCmdSub[0], &rawCmdSub[15], &buf.data()[0], &buf.data()[15]);
        }

        BOOST_AUTO_TEST_CASE(testMsgEncode) {
            ZeroMQEncoder encoder;

            ZeroMQMessage msg;
            msg << "Hello";
            msg << "World";

            network::ArrayBuffer<128> buf;
            std::error_code success;
            BOOST_REQUIRE_EQUAL(success, encoder.write(buf, msg));
            BOOST_REQUIRE_EQUAL(14, buf.size());
        }

    BOOST_AUTO_TEST_SUITE_END()

}