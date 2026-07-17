#include <stdio.h>
#include "hal.h"

static int sent_count = 0;

void hal_send(Packet p) {
    sent_count++;
    // Gercek donanimda burasi LoRa komutu olacak. Simdilik sadece sayma işi.
}

int hal_get_sent_count(void) {
    return sent_count;
}

void hal_reset(void) {
    sent_count = 0;
}
