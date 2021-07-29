#include<iostream>
using namespace std;

int SelecionaKMenor(int array[], int k, int tamanho_array);

int SelecionaKMenor(int array[], int k, int tamanho_array){
    int array_k_menores[k]; // Array que guardará os k menores elementos encontrados

    // Busca o menor elemento k vezes e o remove do array original
    for(int v = 0; v < k; v++){
        int index_menor = 0;
        int menor = array[index_menor];
        for (int i = 1; i < tamanho_array; i++) // Percorre o array buscando o menor elemento
            if (array[i] < menor){
                menor = array[i]; // Salva novo valor do menor elemento encontrado
                index_menor = i; // Salva o index do menor elemento encontrado
            }

        for (int j = index_menor; j < tamanho_array - 1; j++)
            array[j] = array[j+1]; // Remove o menor elemento encontrado do array

        --tamanho_array;
        array_k_menores[v] = menor; // Adiciona o menor elemento encontrado no array de k menores elementos
    }
    return array_k_menores[k-1]; // Retorna o k menor elemento encontrado
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