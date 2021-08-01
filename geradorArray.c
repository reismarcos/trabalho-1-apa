#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#define TAMANHO_ARRAY 100

int main()
{   

    int arr[TAMANHO_ARRAY];
    int i, j, temp;
    srand(time(NULL));
    for(i = 0; i< TAMANHO_ARRAY; i++){
        arr[i] = i + 1;
    }
    for(i = 0; i< TAMANHO_ARRAY; i++){
        j = (rand()%(TAMANHO_ARRAY-1)) + 1;
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp; 
    }
    for(i = 0; i< TAMANHO_ARRAY; i++){
        printf("  %d", arr[i]);
    }
    printf("\n");

    return 0;
}