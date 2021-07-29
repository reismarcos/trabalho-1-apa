#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/resource.h>

#define TAMANHO_PARTICAO 7

int Particao(int arr[], int p, int r, int k);

int Mediana(int arr[], int n);

int SelecionaKMenor(int arr[], int p, int r, int k);

void Troca(int *a, int *b);

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

// Metodo de ordenaçao usa insertion sort como descrito no livro cap 9.3.
// Na verdade o  metodo de ordenaçao nao vai ser tao determinante pois vai sempre ordenar 'q' elementos, sendo 'q' o tamanho do grupo
void Ordena(int vetor[], int tamanho)
{
	int chave;
    int elemento_anterior;
	for (int i = 1; i < tamanho; i++) {
		chave = vetor[i];
		elemento_anterior = i - 1;

		while (elemento_anterior >= 0 && vetor[elemento_anterior] > chave) {
			vetor[elemento_anterior + 1] = vetor[elemento_anterior];
			elemento_anterior = elemento_anterior - 1;
		}
		vetor[elemento_anterior + 1] = chave;
	}
    
}


// Retorna o Kesimo menor elemento de um vetor dado, em O(n) no pior caso
int SelecionaKMenor(int arr[], int p, int r, int k)
{   
    // verifica se k pode ser achado dentro do vetor, isto é, k menor que numero de elementos
    if (k > 0 && k <= r - p + 1)
    {
        // Numero de elementos do vetor atual vetor[p..r]
        int n = r - p + 1;

         // Divide vetor em grupos de tamanho x, calcula mediana de cada um e salva num vetor intermediario
        int i, medianas[(n+4)/TAMANHO_PARTICAO];
        for (i=0; i<n/TAMANHO_PARTICAO; i++)
            medianas[i] = Mediana(arr+p+i*TAMANHO_PARTICAO, TAMANHO_PARTICAO);
        if (i*5 < n)//Caso o ultimo grupo tenha menos de 5 elementos 
        {
            medianas[i] = Mediana(arr+p+i*TAMANHO_PARTICAO, n%TAMANHO_PARTICAO);
            i++;
        }   

        // Acha medianas de todas as medianas do array de medianas recursivamente, caso so tenha um elemento nao precisa fazer recursao 
        int medianaFinal = (i == 1)? medianas[i-1]:
                                 SelecionaKMenor(medianas, 0, i-1, i/2);

        // Particiona o vetor e retorna o indice do elemento pivot no vetor ordenado
        int pos = Particao(arr, p, r, medianaFinal);

        // se posiçao for igual ao k procurado
        if (pos-p == k-1)
            return arr[pos];
        if (pos-p > k-1)
            return SelecionaKMenor(arr, p, pos-1, k); // se posiçao for maior do que o k procurado, procura à esquerda recursivamente

         // caso contrario procura à direita
        return SelecionaKMenor(arr, pos+1, r, k-pos+p-1);
    }
    
     // Se k for maior do que numero de elementos retorna qualquer coisa
    return -1;
}

// Acha mediana de um vetor dado, ordenando antes, note que o calculo ta fixo para um array de tamanho impar
// Mediana supoe que a entrada de dados esta ordenada em alguma ordem de crescimento, entao dai surge a necessidade de se ordenar antes
int Mediana(int arr[], int n)
{
    Ordena(arr, n);
    return arr[n/2];
}

// Troca dois elementos de lugar  
void Troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// particiona o vetor usando x como pivot
int Particao(int arr[], int p, int r, int x)
{
    int i;
    for (i=p; i<r; i++)
        if (arr[i] == x)
           break;
    Troca(&arr[i], &arr[r]);
 
    i = p;
    for (int j = p; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            Troca(&arr[i], &arr[j]);
            i++;
        }
    }
    Troca(&arr[i], &arr[r]);
    return i;
}


int main()
{
    int arr[] = {28, 53, 31, 19, 34, 93, 81, 23, 35, 85};
    int n = sizeof(arr)/sizeof(arr[0]), k = 1;
	// Tempo_CPU_Sistema(0, 0);
    printf("O K menor elemento é: %d \n", SelecionaKMenor(arr, 0, n-1, k));
	// Tempo_CPU_Sistema(0, 0);
	// printf ("Tempo de CPU total = %d\n", 0 - 0);
    return 0;
}