#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "node_fsm.h"
#include "pull.h"

#define MAX_NODES 6
#define MAX_POOL  120

// Collector'in bir turu demek N node'a istek at, cevaplari topla, en iyi skorluları sec.
// nodes: node dizisi, node_count: kac node var, per_node_budget: her node'a PULL_REQUEST'te verilecek butce.
// transmit_time_per_packet: havuzdaki her paket icin, sirasina gore eklenecek iletim süresi saniye cinsinden
// iletim gecikmesi 0 ise hic gecikme yokmus gibi davranir.
// out: base station'a forward edilecek paketleri içerir.
// forward_budget: base station'a en fazla kac paket gonderilecek.
// Donus degeri: çevresel faktörlere bağlı gercekte forward edilen paket sayisi.
int collector_run_round(Node *nodes, int node_count, double t_now,
                        int order_mode, int per_node_budget,
                        double transmit_time_per_packet,
                        Packet *out, int forward_budget);

#endif
