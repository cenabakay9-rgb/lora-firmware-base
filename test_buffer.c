#include <stdio.h>
#include "buffer.h"

// hizlica bir Packet olusturmak icin kullaniyoruz
Packet make_packet(uint32_t id, double score) {
    Packet p;
    p.packet_id   = id;
    p.source_node = 1;
    p.event_id    = id;
    p.t_gen       = 0.0;
    p.priority    = 1;
    p.payload     = 0.0;
    p.ttl         = 0.0;
    p.checksum    = 0;
    p.score       = score;
    return p;
}

int main(void) {
    PacketBuffer buf;
    buffer_init(&buf);

    int all_pass = 1;

    // Test 1: Bos buffer'a paket ekleme
    Packet p1 = make_packet(1, 10.0);
    int result1 = buffer_add(&buf, p1);
    if (result1 == 1 && buf.count == 1) {
        printf("Test 1 PASS: bos buffer'a ekleme calisti\n");
    } else {
        printf("Test 1 FAIL\n");
        all_pass = 0;
    }

    // Test 2: Buffer'i 20 pakete kadar dolduralim skorlar 10,20,30...200 diye gitsin
    for (int i = 2; i <= 20; i++) {
        Packet p = make_packet(i, i * 10.0);
        buffer_add(&buf, p);
    }
    if (buf.count == 20) {
        printf("Test 2 PASS: buffer 20 pakete doldu\n");
    } else {
        printf("Test 2 FAIL: buf.count = %d\n", buf.count);
        all_pass = 0;
    }

    // Test 3: Buffer doluyken dusuk skorlu yeni paket eklemeye calisalim
    Packet low = make_packet(999, 5.0);
    int result3 = buffer_add(&buf, low);
    if (result3 == 0) {
        printf("Test 3 PASS: dusuk skorlu paket reddedildi\n");
    } else {
        printf("Test 3 FAIL: dusuk skorlu paket kabul edildi\n");
        all_pass = 0;
    }

    // Test 4: Buffer doluyken, YUKSEK skorlu yeni paket eklemeye calisalim
    Packet high = make_packet(1000, 999.0);
    int result4 = buffer_add(&buf, high);
    int found_new = 0;
    for (int i = 0; i < buf.count; i++) {
        if (buf.items[i].packet_id == 1000) {
            found_new = 1;
        }
    }
    if (result4 == 1 && found_new == 1 && buf.count == 20) {
        printf("Test 4 PASS: yuksek skorlu paket en dusugun yerine gecti\n");
    } else {
        printf("Test 4 FAIL\n");
        all_pass = 0;
    }

    printf("\n=== GENEL SONUC: %s ===\n", all_pass ? "PASS" : "FAIL");

    return 0;
}
