#include <stdio.h>
#include "node_fsm.h"
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

    // Test 1: node_init sonrasi SLEEP durumunda olmali
    Node node;
    node_init(&node);
    if (node.state == STATE_SLEEP && node.buffer.count == 0) {
        printf("Test 1 PASS: node SLEEP durumunda basladi buffer bos\n");
    } else {
        printf("Test 1 FAIL\n");
        all_pass = 0;
    }

    // Test 2: istek gelmeden cevap verilmeye calisilirsa 0 paket gonderilmeli
    Packet out[20];
    int sent0 = node_respond_and_sleep(&node, 100.0, ORDER_SCORE, out, 5);
    if (sent0 == 0 && node.state == STATE_SLEEP) {
        printf("Test 2 PASS:istek gelmeden cevap verilemedi\n");
    } else {
        printf("Test 2 FAIL\n");
        all_pass = 0;
    }

    // Test 3: PULL_REQUEST gelince SLEEP modeundan RESPONDING moduna gecisi olmali
    node_on_pull_request(&node);
    if (node.state == STATE_RESPONDING) {
        printf("Test 3 PASS: SLEEP'ten RESPONDING'e gecti\n");
    } else {
        printf("Test 3 FAIL\n");
        all_pass = 0;
    }

    // Test 4: buffer'a paket koyup responding durumundayken cevap verdirelim
    buffer_add(&node.buffer, make_packet(1, 3, 0.0));
    buffer_add(&node.buffer, make_packet(2, 1, 90.0));

    int sent = node_respond_and_sleep(&node, 100.0, ORDER_SCORE, out, 1);

    if (sent == 1 && out[0].packet_id == 1 && node.state == STATE_SLEEP) {
        printf("Test 4 PASS: alarm gonderildi node tekrar SLEEP'e dondu\n");
    } else {
        printf("Test 4 FAIL\n");
        all_pass = 0;
    }

    printf("\n=== GENEL SONUC: %s ===\n", all_pass ? "PASS" : "FAIL");
    return 0;
}
