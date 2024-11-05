#include <stdio.h>

typedef struct {
    int mulai;
    int selesai;
} Aktivitas;

void swap(Aktivitas* a, Aktivitas* b) {
    int tmp_mulai, tmp_selesai;
    tmp_mulai  = a->mulai;
    tmp_selesai  = a->selesai;
    a->mulai = b->mulai;
    a->selesai = b->selesai;
    b->mulai = tmp_mulai;
    b->selesai = tmp_selesai;
}

int main()
{
    Aktivitas aktivitas[11] = {
        {1,4},
        {3,5},
        {0,6},
        {5,7},
        {3,8},
        {5,9},
        {6,10},
        {8,11},
        {8,12},
        {2,13},
        {12,14},
    };
    const int n = 11;

    // urutkan aktifitas bedasarkan waktu selesai
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n - i - 1;j++) {
            if (aktivitas[j].selesai > aktivitas[j+1].selesai)
                swap(&aktivitas[j],&aktivitas[j+1]);
        }
    }

    // iterasikan seluruh aktivitas dan cari yang memiliki waktu selesai tidak
    // berkonflik
    int aktifitas_terakhir = 0;
    for(int i = 0; i < n; i++) {
        if(aktivitas[i].mulai >= aktifitas_terakhir) {
            printf("(%d,%d)\n", aktivitas[i].mulai, aktivitas[i].selesai);
            aktifitas_terakhir = aktivitas[i].selesai;
        }
    }

    return 0;
}
