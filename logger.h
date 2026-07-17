#ifndef LOGGER_H
#define LOGGER_H

#include "packet.h"

// Simdilik dosyaya yazma yok deney asamasinda eklenecek
// Tek bir paketin gonderildigini loglar id, priority, skor.
void log_packet_sent(Packet p);

// Bir turun ozetini loglar kac paket gonderildi, hangi mod kullanildi.
void log_round_summary(int round_number, int order_mode, int sent_count);

#endif
