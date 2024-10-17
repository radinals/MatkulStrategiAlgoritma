#include <stdio.h>

#define MAX_SOLUTIONS 2
#define COMBINATION_LENGTH 3

int total_solutions_found = 0;
int solutions[MAX_SOLUTIONS][COMBINATION_LENGTH];

int is_new_solution(int a, int b, int c) {

    for (int i=0; i < MAX_SOLUTIONS; i++) {
        for(int j=0; j < COMBINATION_LENGTH; j++) {
            int saved_index = solutions[i][j];
            if (saved_index == a || saved_index == b || saved_index == c ) {
                return 0;
            }
        }
    }

    return 1;
}

int add_solution(int a, int b, int c) {
    if (total_solutions_found >= MAX_SOLUTIONS) {
        return 0;
    }

    solutions[total_solutions_found][0] = a;
    solutions[total_solutions_found][1] = b;
    solutions[total_solutions_found][2] = c;

    total_solutions_found++;

    return 1;
}

void init() {
    for (int i=0; i < MAX_SOLUTIONS; i++) {
        for (int j=0; j < COMBINATION_LENGTH; j++) {
            solutions[i][j] = -1;
        }
    }
}

int get_total(const int array[], int array_size) {
        int total = 0;
        for(int i = 0; i < array_size; i++) {
            total += array[i];
        }
        return total;
}

void findSolution(const int array[], int array_size) {
    int target = get_total(array, array_size) / 2;
    if (target % 2 != 0) {
        printf("NO POSSIBLE SOLUTIONS\n");
        return;
    }

    // x - -  
    for(int a = 0; a < array_size; a++) {
        // - x -  
        for (int b = 0; b < array_size; b++) {
            // - - x 
            for (int c = 0; c < array_size; c++) {

                if(a != b && a != c && b != c) {
                    int n_a, n_b, n_c;
                    n_a = array[a]; n_b = array[b]; n_c = array[c];
                    if ((n_a + n_b + n_c) == target) {
                        if (is_new_solution(a, b, c)) {
                            add_solution(a, b, c);   
                        }
                    }
                }
            }
        }

    }
}

void printSolutions(const int array[]) {
    for (int i=0; i < MAX_SOLUTIONS; i++) {
        printf("solution %d: ", i+1);
        for (int j=0; j < COMBINATION_LENGTH; j++) {
            printf("%d ", array[solutions[i][j]]);
        }
        putchar('\n');
    }
}

int main()
{
    
    init();

    int angka[6] = { 3, 8, 4, 6, 1, 2 };

    findSolution(angka,6);

    printSolutions(angka);

    return 0;
}
