#include <stdio.h>

#include <stdlib.h>
#include <time.h>

int main()
{   

    int arr[100];
    int i, j, temp;
    srand(time(NULL));
    for(i = 0; i< 100; i++){
        arr[i] = i + 1;
    }
    for(i = 0; i< 100; i++){
        j = (rand()%9 ) + 1;
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp; 
    }
    for(i = 0; i< 100; i++){
        printf("  %d", arr[i]);
    }
    printf("\n");

    return 0;
}