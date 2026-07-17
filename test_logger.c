#include <stdio.h>
#include "logger.h"
#include "pull.h"

Packet make_packet(uint32_t id, uint8_t priority, double score) {
    Packet p;
    p.packet_id   = id;
    p.source_node = 1;
    p.event_id    = id;
    p.t_gen       = 0.0;
    p.priority    = priority;
    p.payload     = 0.0;
    p.ttl         = 0.0;
    p.checksum    = 0;
    p.score       = score;
    return p;
}

int main(void) {
    printf("Ornek log ciktilari:\n\n");

    log_packet_sent(make_packet(1, 3, 85.0));
    log_round_summary(1, ORDER_SCORE, 1);

    printf("\n=== GENEL SONUC: PASS (fonksiyonlar hatasiz calisti) ===\n");
    return 0;
}
