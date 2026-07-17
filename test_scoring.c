#include <stdio.h>
#include "scoring.h"

int main(void) {
    int all_pass = 1;

    // Test 1 case senaryolardan biri
    // P=3, tamamen eski age=A_MAX yani freshness=0 ve tamamen redundant sR=1
    // Beklenen skor: 90 + 0 - 5 = 85
    Packet alarm;
    alarm.priority = 3;
    alarm.t_gen    = 0.0;
    double t_now_1 = A_MAX;   // age tam A_MAX'a esit, freshness = 0
    scoring_compute(&alarm, t_now_1, 1.0);

    printf("Test 1: case alarm skoru = %.1f (beklenen: 85.0)\n", alarm.score);
    if (alarm.score == 85.0) {
        printf("Test 1 PASS\n");
    } else {
        printf("Test 1 FAIL\n");
        all_pass = 0;
    }

    // Test 2 best case rutin ornegi degerlendırırsek
    // P=1 tamamen fresh age=0, freshness=1 ve hic redundant degil R=0
    // Beklenen: 10 + 1 - 0 = 11
    Packet routine;
    routine.priority = 1;
    routine.t_gen    = 100.0;
    double t_now_2 = 100.0;   // age = 0, freshness = 1
    scoring_compute(&routine, t_now_2, 0.0);

    printf("Test 2: bestcase rutin skoru = %.1f (beklenen: 11.0)\n", routine.score);
    if (routine.score == 11.0) {
        printf("Test 2 PASS\n");
    } else {
        printf("Test 2 FAIL\n");
        all_pass = 0;
    }

    // Test 3 alarm her zaman agirlik olarak rutinden yuksek olmali:priority dominance
    if (alarm.score > routine.score) {
        printf("Test 3 PASS: alarm skoru rutin skorundan yuksek: priority dominance\n");
    } else {
        printf("Test 3 FAIL\n");
        all_pass = 0;
    }

    printf("\n=== GENEL SONUC: %s ===\n", all_pass ? "PASS" : "FAIL");

    return 0;
}

