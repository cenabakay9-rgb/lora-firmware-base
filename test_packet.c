#include <stdio.h>
#include "packet.h"

int main(void) {
    Packet p;

    p.packet_id   = 1001;
    p.source_node = 2;
    p.event_id    = 55;
    p.t_gen       = 125.3;
    p.priority    = 3;
    p.payload     = 45.0;
    p.ttl         = 300.0;
    p.checksum    = 8842;
    p.score       = 0.0;

    printf("Test: birkaç taninlanmis degeri ile ornek bir paket olusturuldu\n");
    printf("  packet_id   = %u\n", p.packet_id);
    printf("  source_node = %u\n", p.source_node);
    printf("  priority    = %u\n", p.priority);
    printf("  payload     = %.1f\n", p.payload);

    if (p.packet_id == 1001 && p.source_node == 2 && p.priority == 3) {
        printf("SONUC: PASS\n");
    } else {
        printf("SONUC: FAIL\n");
    }

    return 0;
}
