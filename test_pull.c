#include <stdio.h>
#include "pull.h"

Packet make_packet(uint32_t id, uint8_t priority, double t_gen) {
    Packet p;
    p.packet_id   = id;
    p.source_node = 1;
    p.event_id    = id;
    p.t_gen       = t_gen;
    p.priority    = priority;
    p.payload     = 0.0;
    p.ttl         = 0.0;
    p.checksum    = 0;
    p.score       = 0.0;
    return p;
}

int main(void) {
    int all_pass = 1;

    int b3  = pull_budget(3.0);
    int b15 = pull_budget(15.0);
    int b30 = pull_budget(30.0);
    printf("Test 1: butceler = %d, %d, %d (beklenen: 1, 7, 15)\n", b3, b15, b30);
    if (b3 == 1 && b15 == 7 && b30 == 15) {
        printf("Test 1 PASS\n");
    } else {
        printf("Test 1 FAIL\n");
        all_pass = 0;
    }

    PacketBuffer buf;
    buffer_init(&buf);
    buffer_add(&buf, make_packet(1, 1, 100.0));
    buffer_add(&buf, make_packet(2, 3, 0.0));
    buffer_add(&buf, make_packet(3, 1, 110.0));

    Packet out[20];
    int sent = pull_respond(&buf, 120.0, ORDER_SCORE, out, 1);

    printf("Test 2: gonderilen ilk paket id = %u (beklenen: 2, alarm)\n", out[0].packet_id);
    if (sent == 1 && out[0].packet_id == 2 && buf.count == 2) {
        printf("Test 2 PASS: skor modu alarmi secti buffer 2'ye dustu\n");
    } else {
        printf("Test 2FAIL\n");
        all_pass = 0;
    }

    PacketBuffer buf2;
    buffer_init(&buf2);
    buffer_add(&buf2, make_packet(1, 1, 100.0));
    buffer_add(&buf2, make_packet(2, 3, 0.0));
    buffer_add(&buf2, make_packet(3, 1, 50.0));

    Packet out2[20];
    pull_respond(&buf2, 120.0, ORDER_FIFO, out2, 2);

    printf("Test 3: FIFO sirasina gore = %u, %u (beklenen: 2, 3)\n",
           out2[0].packet_id, out2[1].packet_id);
    if (out2[0].packet_id == 2 && out2[1].packet_id == 3) {
        printf("Test 3 PASS: FIFO en eskiden en yeniye dogru gonderdi\n");
    } else {
        printf("Test 3 FAIL\n");
        all_pass = 0;
    }

    PacketBuffer buf3;
    buffer_init(&buf3);
    buffer_add(&buf3, make_packet(1, 1, 0.0));
    buffer_add(&buf3, make_packet(2, 2, 10.0));

    Packet out3[20];
    int sent3 = pull_respond(&buf3, 100.0, ORDER_SCORE, out3, 15);

    printf("Test 4:gonderilen = %d (beklenen: 2), kalan buffer = %d (beklenen: 0)\n",
           sent3, buf3.count);
    if (sent3 == 2 && buf3.count == 0) {
        printf("Test 4 PASS\n");
    } else {
        printf("Test 4 FAIL\n");
        all_pass = 0;
    }

    printf("\n=== GENEL SONUC: %s ===\n", all_pass ? "PASS" : "FAIL");
    return 0;
}
