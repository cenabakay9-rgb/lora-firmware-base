#include <stdio.h>
#include "scoring.h"
#include "buffer.h"
#include "pull.h"
#include "node_fsm.h"
#include "collector.h"

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
    printf("=== LIMITATION CASES ===\n\n");

    // cok yasli bir paket adina freshness 0'da mi kaliyor testi
    double f1 = scoring_freshness(A_MAX * 10.0, 0.0);
    printf("Test 1: freshness = %.2f\n", f1);
    printf("%s\n\n", f1 == 0.0 ? "PASS" : "FAIL");

    // t_now < t_gen durumunda gelecekten paket casei, ust sinir kontrolunun olmadigi yer
    double f2 = scoring_freshness(0.0, 100.0);
    printf("Test 2: freshness = %.2f\n", f2);
    printf("%s\n\n", f2 > 1.0 ? "limitation: ust deger korunmuyor" : "PASS");

    // FIFO prensibine gore yani skorlama yokken buffer doluyken yeni paket ne oluyor
    PacketBuffer buf3;
    buffer_init(&buf3);
    for (int i = 1; i <= 20; i++) {
        buffer_add(&buf3, make_packet(i, 1, (double)i));
    }
    int r3 = buffer_add(&buf3, make_packet(999, 1, 999.0));
    printf("Test 3: yeni paket %s\n\n", r3 == 1 ? "kabul edildi (ilk eleman atildi)" : "reddedildi");

    // butce sifir verilirse hicbir sey gonderilmemeli
    PacketBuffer buf4;
    buffer_init(&buf4);
    buffer_add(&buf4, make_packet(1, 2, 0.0));
    Packet out4[20];
    int sent4 = pull_respond(&buf4, 10.0, ORDER_SCORE, out4, 0);
    printf("Test 4: sent=%d, buffer.count=%d\n", sent4, buf4.count);
    printf("%s\n\n", (sent4 == 0 && buf4.count == 1) ? "PASS" : "FAIL");

    // bos buffera istek gelirse cokme olmamali
    PacketBuffer buf5;
    buffer_init(&buf5);
    Packet out5[20];
    int sent5 = pull_respond(&buf5, 10.0, ORDER_SCORE, out5, 5);
    printf("Test 5: sent=%d\n", sent5);
    printf("%s\n\n", sent5 == 0 ? "PASS" : "FAIL");

    // ayni node'a arka arkaya iki istek durumunda ikincisi yok sayilmali
    Node node6;
    node_init(&node6);
    node_on_pull_request(&node6);
    node_on_pull_request(&node6);
    int is_responding = (node6.state == STATE_RESPONDING);
    printf("Test 6: durum degismedi mi = %s\n", is_responding ? "evet" : "hayir");
    printf("%s\n\n", is_responding ? "PASS" : "FAIL");

    // hic paketi olmayan node'larla tur atiliyor
    Node nodes7[2];
    node_init(&nodes7[0]);
    node_init(&nodes7[1]);
    Packet out7[20];
    int sent7 = collector_run_round(nodes7, 2, 10.0, ORDER_SCORE, 5, 2.0, out7, 10);
    printf("Test 7: sent=%d\n", sent7);
    printf("%s\n\n", sent7 == 0 ? "PASS" : "FAIL");

    // collector seviyesinde FIFO modu daha once hic denenmemisti. sonuc FIFO'nun birden fazla node'dan gelen paketlerin birleştiği global havuzda da doğru çalışıyor
    Node nodes8[2];
    node_init(&nodes8[0]);
    node_init(&nodes8[1]);
    buffer_add(&nodes8[0].buffer, make_packet(10, 1, 50.0));
    buffer_add(&nodes8[1].buffer, make_packet(20, 1, 5.0));
    Packet out8[20];
    int sent8 = collector_run_round(nodes8, 2, 10.0, ORDER_FIFO, 5, 2.0, out8, 10);
    printf("Test 8: sent=%d, ilk id=%u\n", sent8, out8[0].packet_id);
    printf("%s\n\n", (sent8 == 2 && out8[0].packet_id == 20) ? "PASS" : "FAIL");

    return 0;
}