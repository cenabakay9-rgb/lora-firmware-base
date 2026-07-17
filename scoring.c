#include <stdio.h>
#include "scoring.h"

double scoring_freshness(double t_now, double t_gen) {
    double age = t_now - t_gen;
    double freshness = 1.0 - (age / A_MAX);

    if (freshness < 0.0) {
        freshness = 0.0;
    }

    return freshness;
}

void scoring_compute(Packet *p, double t_now, double redundancy) {
    double priority_term   = W_P * (p->priority * p->priority);
    double freshness_term  = W_F * scoring_freshness(t_now, p->t_gen);
    double redundancy_term = W_R * redundancy;

    p->score = priority_term + freshness_term - redundancy_term;
}


