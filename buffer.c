#include <stdio.h>
#include "buffer.h"

void buffer_init(PacketBuffer *buf) {
    buf->count = 0;
}

int buffer_find_lowest_score_index(PacketBuffer *buf) {
    if (buf->count == 0) {
        return -1;
    }

    int lowest_index = 0;
    double lowest_score = buf->items[0].score;

    for (int i = 1; i < buf->count; i++) {
        if (buf->items[i].score < lowest_score) {
            lowest_score = buf->items[i].score;
            lowest_index = i;
        }
    }

    return lowest_index;
}

int buffer_add(PacketBuffer *buf, Packet p) {
    if (buf->count < BUFFER_CAPACITY) {
        buf->items[buf->count] = p;
        buf->count++;
        return 1;
    }

    int lowest_index = buffer_find_lowest_score_index(buf);

    if (p.score > buf->items[lowest_index].score) {
        buf->items[lowest_index] = p;
        return 1;
    }

    return 0;
}
