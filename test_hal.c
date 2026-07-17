#include <stdio.h>
#include "hal.h"

Packet make_packet(uint32_t id) {
    Packet p;
    p.packet_id   = id;
    p.source_node = 1;
    p.event_id    = id;
    p.t_gen       = 0.0;
    p.priority    = 1;
    p.payload     = 0.0;
    p.ttl         = 0.0;
    p.checksum    = 0;
    p.score       = 0.0;
    return p;
}

int main(void) {
    int all_pass = 1;

    if (hal_get_sent_count() == 0) {
        printf("Test 1 PASS: baslangicta sayac 0\n");
    } else {
        printf("Test 1 FAIL\n");
        all_pass = 0;
    }

    hal_send(make_packet(1));
    hal_send(make_packet(2));
    hal_send(make_packet(3));

    if (hal_get_sent_count() == 3) {
        printf("Test 2 PASS: 3 paket gonderildi/ sayac 3\n");
    } else {
        printf("Test 2 FAIL\n");
        all_pass = 0;
    }

    hal_reset();
    if (hal_get_sent_count() == 0) {
        printf("Test 3 PASS: reset sonrasi sayac 0\n");
    } else {
        printf("Test 3 FAIL\n");
        all_pass = 0;
    }

    printf("\n=== GENEL SONUC: %s ===\n", all_pass ? "PASS" : "FAIL");
    return 0;
}
