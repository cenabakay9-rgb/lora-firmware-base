#include <stdio.h>
#include "collector.h"
#include "scoring.h"

int collector_run_round(Node *nodes, int node_count, double t_now,
                        int order_mode, int per_node_budget,
                        double transmit_time_per_packet,
                        Packet *out, int forward_budget) {

    Packet pool[MAX_POOL];
    int pool_count = 0;

    for (int i = 0; i < node_count; i++) {
        node_on_pull_request(&nodes[i]);

        Packet received[BUFFER_CAPACITY];
        int got = node_respond_and_sleep(&nodes[i], t_now, order_mode,
                                         received, per_node_budget);

        for (int j = 0; j < got; j++) {
            pool[pool_count] = received[j];
            pool_count++;
        }
    }

    if (order_mode == ORDER_SCORE) {
        for (int i = 0; i < pool_count; i++) {
            double arrival_time = t_now + (i * transmit_time_per_packet);
            scoring_compute(&pool[i], arrival_time, 0.0);
        }
    }

    int sent = 0;
    while (sent < forward_budget && sent < pool_count) {
        int best = sent;
        for (int i = sent + 1; i < pool_count; i++) {
            if (order_mode == ORDER_SCORE) {
                if (pool[i].score > pool[best].score) {
                    best = i;
                }
            } else {
                if (pool[i].t_gen < pool[best].t_gen) {
                    best = i;
                }
            }
        }
        Packet tmp = pool[sent];
        pool[sent] = pool[best];
        pool[best] = tmp;

        out[sent] = pool[sent];
        sent++;
    }

    return sent;
}
