//
// Created by Ivan Kishchenko on 10.12.2021.
//

#pragma once

#include "network/Handler.h"
#include "network/Buffer.h"
#include <memory>
#include <variant>

#include "MQTT.h"
#include "MQTTDecoder.h"
#include "MQTTEncoder.h"

namespace network::mqtt {

    class MQTTCodec : public InboundOutboundMessageHandler<Buffer, PublishMessage, PubAckMessage, SubscribeMessage, SubAckMessage, UnSubscribeMessage, UnSubAckMessage> {
        ArrayBuffer<2048> _incBuf;
        MQTTDecoder::Ptr _decoder;
        MQTTEncoder::Ptr _encoder;

    public:
        MQTTCodec();

        void handleActive(const Context &ctx) override;

        void handleRead(const Context &ctx, const Buffer &msg) override;

        void handleWrite(const Context &ctx, const PublishMessage &msg) override;

        void handleWrite(const Context &ctx, const PubAckMessage &msg) override;

        void handleWrite(const Context &ctx, const SubscribeMessage &msg) override;

        void handleWrite(const Context &ctx, const SubAckMessage &msg) override;

        void handleWrite(const Context &ctx, const UnSubscribeMessage &msg) override;

        void handleWrite(const Context &ctx, const UnSubAckMessage &msg) override;

        void handleUserMessage(const Context &ctx, const UserMessage &msg) override;
    };

}


