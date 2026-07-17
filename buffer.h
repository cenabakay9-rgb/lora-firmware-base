#ifndef BUFFER_H
#define BUFFER_H

#include "packet.h"

#define BUFFER_CAPACITY 20   // Section 3.3 - K=20, node basina sabit

typedef struct {
    Packet items[BUFFER_CAPACITY];
    int    count;             // su an buffer'da kac paket var (0-20)
} PacketBuffer;

// Buffer'i bos halde baslat
void buffer_init(PacketBuffer *buf);

// Yeni paket ekle. Buffer doluysa en dusuk skorluyu silip yerine bunu koyar.
// Basarili eklemede 1, basarisiz durumda 0 donecek.
int buffer_add(PacketBuffer *buf, Packet p);

// Buffer'daki en dusuk skorlu paketin index'ini bulur ve -1 ise buffer bos)
int buffer_find_lowest_score_index(PacketBuffer *buf);

#endif
