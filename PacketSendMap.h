#ifndef PACKET_SEND_MAP_H
#define PACKET_SEND_MAP_H

#include "Const.h"
#include "Packet.h"
#include "SceneGame.h"

class PacketSendMap : public Packet
{
public:
    PacketSendMap();
    void prepare(SceneGame* scene);
    void process(SceneGame* scene);
};

#endif
