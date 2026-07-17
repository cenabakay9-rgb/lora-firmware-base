#ifndef SCORING_H
#define SCORING_H

#include "packet.h"

#define A_MAX 2400.0   // freshness K=20 * T_event=120s
#define W_P   10.0     // priority katsayisi
#define W_F   1.0      // freshness katsayisi
#define W_R   5.0      // redundancy katsayisi

// freshness(Fk) hesaplar: paketin yasina gore [0,1] araliginda bir deger alacak
double scoring_freshness(double t_now, double t_gen);

// final skoru(Sk) hesaplar ve paketin .score alanina yazar
void scoring_compute(Packet *p, double t_now, double redundancy);

#endif

