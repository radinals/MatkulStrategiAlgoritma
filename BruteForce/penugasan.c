#include <stdio.h>


int main()
{
    int C[4][4] = {
        {9,2,7,8},
        {6,4,3,7},
        {5,8,1,4},
        {7,6,9,4},
    };

    for (int i = 0; i < 4; i++) {
        int min = -1;
        int k = -1;
        for (int j=0; j < 4; j++) {
            if (min < 0 || C[i][j] < min) {
                min = C[i][j];
                k = j;
            }
        }
        printf(
            "orang ke %c dapat pekerjaan ke %d dengan biaya %d \n",
            i + 'a',k+1,min);
   }

    return 0;
}
