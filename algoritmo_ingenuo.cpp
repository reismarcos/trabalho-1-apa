#include<iostream>
using namespace std;

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
    int k = 10;
    int array[] = {28, 53, 31, 19, 34, 93, 81, 23, 35, 85};
    int array_size = sizeof(array)/sizeof(array[0]);
    int k_menor = SelecionaKMenor(array, k, array_size);
    cout << "O K menor elemento é: "
         << k_menor;
         
    return 0;
}