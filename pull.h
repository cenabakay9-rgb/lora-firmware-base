#ifndef PULL_H
#define PULL_H

#include "buffer.h"

#define LORA_THROUGHPUT 0.5   // yaklasik paket/saniye
#define ORDER_SCORE 0   // PULL: en yuksek skor once 
#define ORDER_FIFO  1   // FIFO: en eski t_gen once

// Contact window'dan gonderim butcesini hesaplar yine yaklasik hesap
// 3s -> 1 paket, 15s -> 7 paket, 30s -> 15 paket butce
int pull_budget(double t_contact);

// PULL_REQUEST'e cevap: bufferdaki paketleri secilen moda gore siralar,
// butce kadar paketi out dizisine kopyalar ve buffer'dan cikarir.
// Donus degeri yani gercekte gonderilen paket sayisi.
// ORDER_SCORE modunda skorlar t_now'a gore yeniden hesaplanir (karar aninda).
int pull_respond(PacketBuffer *buf, double t_now, int order_mode,
                 Packet *out, int budget);

#endif
