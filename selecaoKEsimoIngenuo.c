#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/resource.h>
#include <time.h>

void Tempo_CPU_Sistema(double *seg_CPU_total, double *seg_sistema_total)
{
  long seg_CPU, seg_sistema, mseg_CPU, mseg_sistema;
  struct rusage ptempo;

  getrusage(0,&ptempo);

  seg_CPU = ptempo.ru_utime.tv_sec;
  mseg_CPU = ptempo.ru_utime.tv_usec;
  seg_sistema = ptempo.ru_stime.tv_sec;
  mseg_sistema = ptempo.ru_stime.tv_usec;

 *seg_CPU_total     = (seg_CPU + 0.000001 * mseg_CPU);
 *seg_sistema_total = (seg_sistema + 0.000001 * mseg_sistema);
}


int SelecionaKMenor(int array[], int k, int tamanho_array){
    int array_k_menores[k];
    for(int v = 0; v < k; v++){
        int index_menor = 0;
        int menor = array[index_menor];
        for (int i = 1; i < tamanho_array; i++)
            if (array[i] < menor){
                menor = array[i];
                index_menor = i;
            }
        for (int j = index_menor; j < tamanho_array - 1; j++)
            array[j] = array[j+1];
        --tamanho_array;
        array_k_menores[v] = menor;
    }
    return array_k_menores[k-1];
}

int main()
{   
    // int k = 3;
    // int array[] = {28, 53, 31, 19, 34, 93, 81, 23, 35, 85};
    int arr[1000000];
    int i, j, temp;
    srand(time(NULL));
    for(i = 0; i< 1000000; i++){
        arr[i] = i + 1;
    }
    for(i = 0; i< 1000000; i++){
        j = (rand()%9 ) + 1;
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp; 
    }
    int n = sizeof(arr)/sizeof(arr[0]), k = 7652;
    int tamanho_array = sizeof(arr)/sizeof(arr[0]);
    double s_CPU_inicial, s_total_inicial;
    Tempo_CPU_Sistema(&s_CPU_inicial, &s_total_inicial);
    int k_menor = SelecionaKMenor(arr, k, tamanho_array);
    printf("%d\n", k_menor);
    double s_CPU_final, s_total_final;
    Tempo_CPU_Sistema(&s_CPU_final, &s_total_final);
	printf ("Tempo de CPU total = %f\n", s_CPU_final - s_CPU_inicial);
    return 0;
}