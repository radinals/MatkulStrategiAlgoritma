#include <stdio.h>

typedef struct {
    int bobot;
    int nilai;
} Item;

typedef struct {
    int max_bobot;
    int total_bobot;
    int total_nilai;
    int jmlh_item;
    Item item[];
} Tas;

double getRasioItem(const Item*const item) {
    return (double)item->nilai / (double)item->bobot;
}

void swap(Item* a, Item* b) {
    int tmp_bobot, tmp_nilai;

    tmp_bobot = a->bobot;
    tmp_nilai = a->nilai;

    a->bobot = b->bobot;
    a->nilai = b->nilai;

    b->bobot = tmp_bobot;
    b->nilai = tmp_nilai;
}

Item getSebagianItem(int berat_diambil, const Item*const item) {
    Item sebagian;
    sebagian.nilai = (int)(berat_diambil * getRasioItem(item));
    sebagian.bobot = berat_diambil;
    return sebagian;
}

int main()
{
    Item items[3] = {
        {10,60},
        {20,100},
        {30,120},
    };
    const int n = 3;

    Tas tas;
    tas.max_bobot = 50;
    tas.total_bobot = 0;
    tas.jmlh_item = 0;
    tas.total_nilai = 0;


    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n - i - 1;j++) {
            if (getRasioItem(&items[j]) < getRasioItem(&items[j+1]))
                swap(&items[j],&items[j+1]);
        }
    }
 // Memilih item sesuai dengan pendekatan greedy
    for(int i = 0; i < n; i++) {
        // Jika item bisa dimasukkan seluruhnya
        if (tas.total_bobot < items[i].bobot) {
            tas.total_bobot += items[i].bobot;
            tas.total_nilai += items[i].nilai;
            printf("Seluruh Item dengan berat %d kg dan nilai %d\n", items[i].bobot, items[i].nilai);
        }
        // Jika tidak bisa dimasukkan seluruhnya, ambil sebagian
        else {
            double fraction = (double) (tas.max_bobot-tas.total_bobot) / items[i].bobot;
            tas.total_nilai += items[i].nilai * fraction;
            printf("Sebagian dari item (%.2f) dengan berat %d kg dan nilai %d (Nilai yang diperoleh: %.2f)\n",
                   fraction, items[i].bobot, items[i].nilai, items[i].nilai * fraction);
            tas.total_bobot += items[i].bobot * fraction;
            break; // Knapsack penuh setelah mengambil sebagian
        }
    }

    printf("total nilai di dalam tas: %d\n",tas.total_nilai);
    printf("total berat di dalam tas: %d\n",tas.total_bobot);
    return 0;
}
