#include <stdio.h>

void minMax(int array[], int i, int j, int* min, int* max) {
    int min1,min2, max1, max2;

    if (i == j) {
        *min = *max= array[i];
    } else {
        if (i == j-1) {
            if (array[i] < array[j]) {
                *min = array[i];
                *max = array[j];
            } else {
                *min = array[j];
                *max = array[i];
            }

        } else {
            int k = (i+j)/2;

            minMax(array,i,k,&min1,&max1);
            minMax(array,k+1,j,&min2,&max2);

            *min = (min1 < min2) ? min1 : min2; 
            *max = (max1 < max2) ? max2 : max1; 
        }
    }
}

int main()
{
    int min=0,max=0;
    int angka[9] = {4,12,23,9,21,1,35,2,24};

    minMax(angka,0,8,&min,&max);

    printf("min: %d\nmax: %d\n", min, max);

    return 0;
}
