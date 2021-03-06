#ifndef __NET__
#define __NET__ 1


#include "ether.h"


struct net {
    void *nic;
    uint8_t addr[ETHER_ADDR_LEN];
    uint32_t (*send)(struct net *inet, void *p_packet, uint32_t packet_size);
    uint32_t ipv4_addr;
};


#endif
