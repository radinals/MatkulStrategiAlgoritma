#include <stdio.h>

int main()
{
    const int kelipatan[4] = { 25, 10, 5, 1 };
    const int N = 4;

    int jumlah_uang = 67;

    printf("%d = ", jumlah_uang);
    for(int i = 0; i < N; i++) {
        printf("(%dx%d)", kelipatan[i], jumlah_uang / kelipatan[i]);
        jumlah_uang %= kelipatan[i];
        if((i + 1) < N) {
            printf( " + ");
        }
    }
    putchar('\n');

    return 0;
}
