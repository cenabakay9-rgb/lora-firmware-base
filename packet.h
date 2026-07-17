#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

// paketin tasidigi 8 alan sırasıyla
typedef struct {
    uint32_t packet_id;      // paketin kendine ozgu kimligi
    uint8_t  source_node;    // hangi node'dan geldigi (1-4)
    uint32_t event_id;       // hangi olcumden uretildigi
    double   t_gen;          // uretim zamani (saniye)
    uint8_t  priority;       // P: 1, 2 veya 3
    double   payload;        // olcum degeri (ornek: sicaklik)
    double   ttl;            // gecerlilik suresi (saniye)
    uint32_t checksum;       // basit hata kontrolu

    double   score;          // hesaplanan skor (Sk), sonra doldurulacak
} Packet;

#endif

