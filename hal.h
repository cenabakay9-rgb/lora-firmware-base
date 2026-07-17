#ifndef HAL_H
#define HAL_H

#include "packet.h"

// MockHAL gercek LoRa donaniminin yerini tutan mock katman.
// Varsayımsal ve kasıtlı olarak bu modulun ic mantigi olarak minimal.
// MockHAL donanim gelince değişecek part
// Bir paketi gonderir. Su an gercekte hicbir yere gondermiyor,
// sadece kac paket gonderildigini sayar. Donanimda burasi gercek
// LoRa TX komutuyla degisecek.
void hal_send(Packet p);

// Su ana kadar kac paket gonderildigini dondurur test amacli kullanilabilir
int hal_get_sent_count(void);

// Sayaci sifirlar 
void hal_reset(void);

#endif
