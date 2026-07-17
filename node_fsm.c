#include <stdio.h>
#include "node_fsm.h"
#include "pull.h"

void node_init(Node *node) {
    node->state = STATE_SLEEP;
    buffer_init(&node->buffer);
}

void node_on_pull_request(Node *node) {
    if (node->state == STATE_SLEEP || node->state == STATE_LISTENING) {
        node->state = STATE_RESPONDING;
    }
    // RESPONDING durumundayken tekrar istek gelirse yok sayilacak zaten mesgul
}

int node_respond_and_sleep(Node *node, double t_now, int order_mode,
                           Packet *out, int budget) {
    if (node->state != STATE_RESPONDING) {
        return 0;  // istek alinmadan cevap verilemez 
    }

    int sent = pull_respond(&node->buffer, t_now, order_mode, out, budget);

    node->state = STATE_SLEEP;  // is bitti tekrar uykuya don komutu
    return sent;
}
