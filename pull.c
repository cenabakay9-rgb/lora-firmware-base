#include <stdio.h>
#include "pull.h"
#include "scoring.h"

int pull_budget(double t_contact) {
    return (int)(t_contact * LORA_THROUGHPUT);
}

static int find_next_index(PacketBuffer *buf, int order_mode) {
    if (buf->count == 0) {
        return -1;
    }

    int best = 0;
    for (int i = 1; i < buf->count; i++) {
        if (order_mode == ORDER_SCORE) {
            if (buf->items[i].score > buf->items[best].score) {
                best = i;
            }
        } else {
            if (buf->items[i].t_gen < buf->items[best].t_gen) {
                best = i;
            }
        }
    }
    return best;
}

static void remove_at(PacketBuffer *buf, int index) {
    buf->items[index] = buf->items[buf->count - 1];
    buf->count--;
}

int pull_respond(PacketBuffer *buf, double t_now, int order_mode,
                 Packet *out, int budget) {

    if (order_mode == ORDER_SCORE) {
        for (int i = 0; i < buf->count; i++) {
            scoring_compute(&buf->items[i], t_now, 0.0);
        }
    }

    int sent = 0;
    while (sent < budget && buf->count > 0) {
        int idx = find_next_index(buf, order_mode);
        out[sent] = buf->items[idx];
        remove_at(buf, idx);
        sent++;
    }

    return sent;
}
