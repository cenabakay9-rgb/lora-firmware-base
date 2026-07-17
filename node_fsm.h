#ifndef NODE_FSM_H
#define NODE_FSM_H

#include "buffer.h"

// Node'un olabilecegi durumlar 
typedef enum {
    STATE_SLEEP,       // hicbir sey yapmiyor, pil tasarrufu 
    STATE_LISTENING,   // PULL_REQUEST var mi diye kontrol ediyor
    STATE_RESPONDING   // PULL_REQUEST alindi, paket gonderiyor
} NodeState;

// Nodeun tum durumunu bir arada tutan yapi icin
typedef struct {
    NodeState    state;   
    PacketBuffer buffer; 
} Node;

// Nodeu SLEEP durumunda bos buffer ile baslatir
void node_init(Node *node);

// Node'a PULL_REQUEST geldi olayini bildirir.
// Node SLEEP veya LISTENING durumundaysa RESPONDING'e gecer.
void node_on_pull_request(Node *node);

// RESPONDING durumundaki node'u cevap verdirip tekrar SLEEP'e dondurur.
int node_respond_and_sleep(Node *node, double t_now, int order_mode,
                           Packet *out, int budget);

#endif
