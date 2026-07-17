#include <stdio.h>
#include "logger.h"
#include "pull.h"

void log_packet_sent(Packet p) {
    printf("[LOG] paket gonderildi: id=%u priority=%u skor=%.1f\n",
           p.packet_id, p.priority, p.score);
}

void log_round_summary(int round_number, int order_mode, int sent_count) {
    const char *mode_name = (order_mode == ORDER_SCORE) ? "SCORE" : "FIFO";
    printf("[LOG] Tur %d (%s modu): %d paket gonderildi\n",
           round_number, mode_name, sent_count);
}
