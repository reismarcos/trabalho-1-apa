#include<iostream>
#include<algorithm> // Para utilizar o metodo sort()

using namespace std;

#define TAMANHO_PARTICAO 5

int Particao(int arr[], int p, int r, int k);

int Mediana(int arr[], int n);

int KMenor(int arr[], int p, int r, int k);

void Troca(int *a, int *b);

// Retorna o Kesimo menor elemento de um vetor dado, em O(n) no pior caso
int KMenor(int arr[], int p, int r, int k)
{   
    // Verifica se k pode ser achado dentro do vetor, isto é, k menor que numero de elementos
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
                                 KMenor(medianas, 0, i-1, i/2);

        // Particiona o vetor e retorna o indice do elemento pivot no vetor ordenado
        int pos = Particao(arr, p, r, medianaFinal);

        // Se posiçao for igual ao k procurado
        if (pos-p == k-1)
            return arr[pos];
        if (pos-p > k-1)
            return KMenor(arr, p, pos-1, k); // se posiçao for maior do que o k procurado, procura à esquerda recursivamente

         // Caso contrario procura à direita
        return KMenor(arr, pos+1, r, k-pos+p-1);
    }
    
     // Se k for maior do que numero de elementos retorna qualquer coisa
    return -1;
}

// Acha mediana de um vetor dado, note que o calculo ta fixo para um array de tamanho impar
int Mediana(int arr[], int n)
{
    sort(arr, arr+n);
    return arr[n/2];
}

// Troca dois elementos
void Troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Particiona o vetor usando x como pivot
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
    cout << "O K menor elemento é: "
         << KMenor(arr, 0, n-1, k);
    return 0;
}