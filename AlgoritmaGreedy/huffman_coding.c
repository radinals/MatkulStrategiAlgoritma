#include <stdio.h>
#include <stdlib.h>

// Struktur untuk node dalam pohon Huffman
typedef struct Node {
    char karakter;
    int frekuensi;
    struct Node *kiri, *kanan;
} Node;

// Struktur untuk min heap
typedef struct MinHeap {
    int ukuran;
    int kapasitas;
    Node** array;
} MinHeap;

// Fungsi untuk membuat node baru
Node* buatNode(char karakter, int frekuensi) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->karakter = karakter;
    node->frekuensi = frekuensi;
    node->kiri = node->kanan = NULL;
    return node;
}

// Fungsi untuk membuat min heap
MinHeap* buatMinHeap(int kapasitas) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->ukuran = 0;
    minHeap->kapasitas = kapasitas;
    minHeap->array = (Node**)malloc(minHeap->kapasitas * sizeof(Node*));
    return minHeap;
}

// Fungsi untuk menukar dua node min heap
void tukarNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// Fungsi heapify
void heapify(MinHeap* minHeap, int idx) {
    int terkecil = idx;
    int kiri = 2 * idx + 1;
    int kanan = 2 * idx + 2;

    if (kiri < minHeap->ukuran && minHeap->array[kiri]->frekuensi < minHeap->array[terkecil]->frekuensi) {
        terkecil = kiri;
    }
    if (kanan < minHeap->ukuran && minHeap->array[kanan]->frekuensi < minHeap->array[terkecil]->frekuensi) {
        terkecil = kanan;
    }
    if (terkecil != idx) {
        tukarNode(&minHeap->array[terkecil], &minHeap->array[idx]);
        heapify(minHeap, terkecil);
    }
}

// Fungsi untuk menghapus node dengan frekuensi terkecil dari min heap
Node* ekstrakTerkecil(MinHeap* minHeap) {
    Node* terkecil = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->ukuran - 1];
    --minHeap->ukuran;
    heapify(minHeap, 0);
    return terkecil;
}

// Fungsi untuk memasukkan node baru ke dalam min heap
void masukkanMinHeap(MinHeap* minHeap, Node* node) {
    ++minHeap->ukuran;
    int i = minHeap->ukuran - 1;
    while (i && node->frekuensi < minHeap->array[(i - 1) / 2]->frekuensi) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// Fungsi untuk membangun min heap
MinHeap* buatDanBangunMinHeap(char karakter[], int frekuensi[], int ukuran) {
    MinHeap* minHeap = buatMinHeap(ukuran);
    for (int i = 0; i < ukuran; ++i) {
        minHeap->array[i] = buatNode(karakter[i], frekuensi[i]);
    }
    minHeap->ukuran = ukuran;
    for (int i = (minHeap->ukuran - 1) / 2; i >= 0; --i) {
        heapify(minHeap, i);
    }
    return minHeap;
}

// Fungsi untuk membangun pohon Huffman
Node* bangunHuffmanTree(char karakter[], int frekuensi[], int ukuran) {
    Node *kiri, *kanan, *atas;
    MinHeap* minHeap = buatDanBangunMinHeap(karakter, frekuensi, ukuran);

    while (minHeap->ukuran != 1) {
        kiri = ekstrakTerkecil(minHeap);
        kanan = ekstrakTerkecil(minHeap);
        atas = buatNode('$', kiri->frekuensi + kanan->frekuensi);
        atas->kiri = kiri;
        atas->kanan = kanan;
        masukkanMinHeap(minHeap, atas);
    }

    return ekstrakTerkecil(minHeap);
}

// Fungsi untuk mencetak kode Huffman
void cetakKode(Node* root, int kode[], int atas) {
    if (root->kiri) {
        kode[atas] = 0;
        cetakKode(root->kiri, kode, atas + 1);
    }
    if (root->kanan) {
        kode[atas] = 1;
        cetakKode(root->kanan, kode, atas + 1);
    }
    if (!root->kiri && !root->kanan) {
        printf("KARAKTER: %c, FREKUENSI: %d: KODE: ", root->karakter, root->frekuensi);
        for (int i = 0; i < atas; ++i) {
            printf("%d", kode[i]);
        }
        printf("\n");
    }
}

int main() {
    char karakter[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int frekuensi[] = {5, 9, 12, 13, 16, 45};
    int ukuran = sizeof(karakter) / sizeof(karakter[0]);

    Node* root = bangunHuffmanTree(karakter, frekuensi, ukuran);

    int kode[100];
    printf("Kode Huffman:\n");
    cetakKode(root, kode, 0);

    return 0;
}
