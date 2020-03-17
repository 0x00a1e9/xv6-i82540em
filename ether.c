#include "types.h"
#include "defs.h"
#include "ether.h"
#include "net.h"
#include "i82540em.h"


size_t gen_frame(struct ether_hdr *ehdr, void *p_packet, size_t packet_size)
{
    if (packet_size > ETHER_DATA_MAX_LEN || !p_packet)
        return 0;

    uint8_t frame[ETHER_FRAME_MAX_LEN];
    memset(frame, 0, sizeof(frame));
    struct ether_hdr *hdr = (struct ether_hdr *)frame;
    void *data = hdr + 1;

    memmove((void *)&hdr->dst, (void *)&ehdr->dst, ETHER_ADDR_LEN);
    memmove((void *)&hdr->src, (void *)&ehdr->src, ETHER_ADDR_LEN);
    memmove((void *)&hdr->type, (void *)&ehdr->type, ETHER_TYPE_LEN);
    memmove((void *)data, (void *)p_packet, packet_size);

    if (packet_size < ETHER_DATA_MIN_LEN) {
        memset(data+packet_size, 0, ETHER_DATA_MIN_LEN-packet_size); // needs padding!
        return (size_t)ETHER_FRAME_MIN_LEN;
    }
    else {
        return (size_t)(ETHER_HDR_LEN + packet_size);
    }
}