#include <stdio.h>
#include "collector.h"
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

    Node nodes[2];
    node_init(&nodes[0]);
    node_init(&nodes[1]);

    buffer_add(&nodes[0].buffer, make_packet(1, 1, 90.0));
    buffer_add(&nodes[1].buffer, make_packet(2, 3, 0.0));

    Packet out[20];
    int sent = collector_run_round(nodes, 2, 100.0, ORDER_SCORE, 1, 2.0, out, 1);

    printf("Test 1: forward edilen id = %u (beklenen: 2, alarm)\n", out[0].packet_id);
    if (sent == 1 && out[0].packet_id == 2) {
        printf("Test 1 PASS: iki node'dan toplanan havuzdan alarm secildi\n");
    } else {
        printf("Test 1 FAIL\n");
        all_pass = 0;
    }

    if (nodes[0].state == STATE_SLEEP && nodes[1].state == STATE_SLEEP) {
        printf("Test 2 PASS: tur sonunda tum node'lar SLEEP moda dondu\n");
    } else {
        printf("Test 2 FAIL\n");
        all_pass = 0;
    }

    Node nodes2[2];
    node_init(&nodes2[0]);
    node_init(&nodes2[1]);
    buffer_add(&nodes2[0].buffer, make_packet(10, 1, 0.0));
    buffer_add(&nodes2[1].buffer, make_packet(20, 2, 0.0));

    Packet out2[20];
    int sent2 = collector_run_round(nodes2, 2, 50.0, ORDER_SCORE, 5, 2.0, out2, 10);

    if (sent2 == 2) {
        printf("Test 3 PASS: havuzda 2 paket vardi ikisi de forward edildi\n");
    } else {
        printf("Test 3 FAIL: sent2 = %d\n", sent2);
        all_pass = 0;
    }

    // Test 4: iletim gecikmesi 0 kabul edilirse gecikme hic yokmus gibi calismali
    Node nodes3[1];
    node_init(&nodes3[0]);
    buffer_add(&nodes3[0].buffer, make_packet(100, 1, 0.0));

    Packet out3[20];
    int sent3 = collector_run_round(nodes3, 1, 100.0, ORDER_SCORE, 1, 0.0, out3, 1);

    if (sent3 == 1 && out3[0].packet_id == 100) {
        printf("Test 4 PASS: gecikme=0 ile de dogru calisti\n");
    } else {
        printf("Test 4 FAIL\n");
        all_pass = 0;
    }

    printf("\n=== GENEL SONUC: %s ===\n", all_pass ? "PASS" : "FAIL");
    return 0;
}
