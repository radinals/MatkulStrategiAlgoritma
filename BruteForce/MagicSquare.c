#include <stdio.h>
#include <stdlib.h>

#define GET_MAGIC_CONSTANT(n) ((n) * (((n) * (n)) + 1) / 2)

typedef struct MagicSquare {
    int** square;
    int N;
    int M;
}MagicSquare;

int is_valid_square(const MagicSquare* magic_square);
void generate_magic_square();
MagicSquare* new_magic_square(int n);
void print_magic_square(const MagicSquare* ms);


int main()
{
    generate_magic_square();

    return 0;
}

// Recursive function to generate permutations and fill the matrix
void generate_permutations(MagicSquare* ms, int used[], int index) {
    // If all cells are filled (index == 9), check for magic square
    if (index == ms->N * ms->N) {
        if(is_valid_square(ms)) {
            print_magic_square(ms);
        } 
        return;
    }

    int row = index / ms->N;  // Calculate row based on index
    int col = index % ms->N;  // Calculate column based on index

    // Try each number from 1 to 9 if it hasn't been used yet
    for (int i = 1; i <= ms->N * ms->N; i++) {
        if (!used[i]) {
            ms->square[row][col] = i;
            used[i] = 1;
            generate_permutations(ms, used, index + 1);
            used[i] = 0;  // Backtrack
        }
    }
}

void generate_magic_square() {
    MagicSquare* ms = new_magic_square(3);
    
    int used[ms->N * ms->N + 1];
    for(int i = 0; i < ms->N * ms->N + 1; i++) {
        used[i] = 0;
    }

    generate_permutations(ms, used, 0);


    free(ms); 
}

int is_valid_square(const MagicSquare* ms) {
    for (int i = 0; i < ms->N; i++) {
        if (ms->square[i][0] + ms->square[i][1] + ms->square[i][2] != ms->M) {
            return 0;
        }
    }

    // Check sums of columns
    for (int i = 0; i < ms->N; i++) {
        if (ms->square[0][i] + ms->square[1][i] + ms->square[2][i] != ms->M) {
            return 0;
        }
    }

    // Check sums of diagonals
    if (ms->square[0][0] + ms->square[1][1] + ms->square[2][2] != ms->M) {
        return 0;
    }
    if (ms->square[0][2] + ms->square[1][1] + ms->square[2][0] != ms->M) {
        return 0;
    }
    return 1;
}

MagicSquare* new_magic_square(int n) {
    MagicSquare* ms = (MagicSquare*) malloc(sizeof(MagicSquare));
    ms->square = (int**)malloc(sizeof(int*));
    for(int i = 0; i < n; i++) {
        ms->square[i] = (int*)calloc(n, sizeof(int));
    }

    ms->N = n;
    ms->M = GET_MAGIC_CONSTANT(n);

    return ms;
}

void print_magic_square(const MagicSquare* ms) {
        putchar('\n');
    for(int i = 0; i < ms->N; i++) {
        for(int j = 0; j < ms->N; j++) {
                printf("%d ",ms->square[i][j]);
        }
        putchar('\n');
    }
}
