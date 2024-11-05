#include <stdio.h>
#include <stdbool.h>

#define V 5 // Jumlah vertex

// Fungsi untuk mencetak warna setiap vertex
void cetakWarna(int warna[]) {
    printf("Warna Vertex:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %c ---> Warna %d\n", 'A' + i, warna[i]);
    }
}

// Fungsi untuk melakukan pewarnaan graph menggunakan algoritma greedy
void greedyColoring(int graph[V][V]) {
    int warna[V];

    // Inisialisasi semua warna vertex dengan -1 (belum diwarnai)
    for (int i = 0; i < V; i++) {
        warna[i] = -1;
    }

    // Beri warna pertama untuk vertex pertama
    warna[0] = 0;

    // Array untuk melacak warna yang tersedia
    bool warnaTersedia[V];
    for (int i = 0; i < V; i++) {
        warnaTersedia[i] = true;
    }

    // Assign warna untuk sisa vertex
    for (int u = 1; u < V; u++) {
        // Tandai warna-warna yang digunakan oleh tetangga sebagai tidak tersedia
        for (int i = 0; i < V; i++) {
            if (graph[u][i] && warna[i] != -1) {
                warnaTersedia[warna[i]] = false;
            }
        }

        // Temukan warna terkecil yang tersedia
        int warnaDipilih;
        for (warnaDipilih = 0; warnaDipilih < V; warnaDipilih++) {
            if (warnaTersedia[warnaDipilih]) {
                break;
            }
        }

        warna[u] = warnaDipilih;

        // Reset warnaTersedia untuk iterasi berikutnya
        for (int i = 0; i < V; i++) {
            warnaTersedia[i] = true;
        }
    }

    // Cetak hasil pewarnaan
    cetakWarna(warna);
}

int main() {
    // Graph dengan vertex V = {A, B, C, D, E} dan edge E
    int graph[V][V] = {
        {0, 1, 1, 0, 0}, // A terhubung dengan B dan C
        {1, 0, 1, 1, 0}, // B terhubung dengan A, C, dan D
        {1, 1, 0, 1, 0}, // C terhubung dengan A, B, dan D
        {0, 1, 1, 0, 1}, // D terhubung dengan B, C, dan E
        {0, 0, 0, 1, 0}  // E terhubung dengan D
    };

    printf("Hasil Pewarnaan Graph:\n");
    greedyColoring(graph);

    return 0;
}
