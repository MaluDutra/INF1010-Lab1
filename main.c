Novidade! Atalhos do teclado … Os atalhos de teclado do Drive foram atualizados para oferecer navegação por letras iniciais
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void troca(int* array, int i, int j);
int particiona(int* array, int inicio, int fim);
int particiona_random(int* array, int inicio, int fim);
void quick_sort(int* array, int inicio, int fim);
int buscaBin(int *v, int num, int tamanho);

void troca(int* array, int i, int j) {
	int aux = array[i];
	array[i] = array[j];
	array[j] = aux;
}

int particiona(int* array, int inicio, int fim) {
	int pivo;
	int pivo_indice, i;

	pivo = array[fim];
	pivo_indice = inicio;

	for(i = inicio; i < fim; i++) {
		if(array[i] <= pivo) {
			troca(array, i, pivo_indice);
			pivo_indice++;
		}
	}

	troca(array, pivo_indice, fim);

	return pivo_indice;
}


int particiona_random(int* array, int inicio, int fim) {
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;

	troca(array, pivo_indice, fim);
	return particiona(array, inicio, fim);
}


void quick_sort(int* array, int inicio, int fim) {
	if (inicio < fim) {
		int pivo_indice = particiona_random(array, inicio, fim);
		quick_sort(array, inicio, pivo_indice - 1);
		quick_sort(array, pivo_indice + 1, fim);
	}
}

int buscaBin(int *v, int num, int tamanho) {
	int inicio;
	int meio;
	int fim;

	inicio = 0;
	fim = tamanho - 1;

	while (inicio <= fim) {
		meio = (inicio + fim) / 2;
    
		if (num == v[meio]) {
			return meio;
		} else if (num > v[meio]) {
			inicio = meio + 1;
		} else {
			fim = meio - 1;
		}
	}
	return -1;
}

int main() {
	int vetor[10000];
	int vetorBusca[10000];
	int vetorNEncontrado[10000];
	int indNEncontrado = 0;
	int randomNum;
	
	srand((unsigned) time(NULL));

	clock_t start, end, diff;
	double tempos[10];
	int contTempo = 0;

	for (int i = 0; i<10000; i++) {
		randomNum = rand() % (10001);
		vetor[i] = randomNum;
	}
	quick_sort(vetor, 0, 9999);

	for (int i = 0; i<10000; i++) {
		randomNum = rand() % (10001);
		vetorBusca[i] = randomNum;
	}

	start = clock();
	for (int i = 0; i<10000; i++) {
		if (buscaBin(vetor, vetorBusca[i], 10000) == -1) {
			vetorNEncontrado[indNEncontrado] = vetorBusca[i];
			indNEncontrado++;
		}

		if (((i % 999) == 0) && (i != 0)) {
			end = clock();
			diff = end - start;
			tempos[contTempo] = (double)diff / CLOCKS_PER_SEC;
			contTempo++;
		}
	}
	end = clock();
	
	printf("\n\nNúmeros não encontrados: \n");
	for (int i = 0; i<indNEncontrado; i++){
	    printf("- %d\n", vetorNEncontrado[i]);
	}
	printf("Total = %d\n", indNEncontrado);
	
	printf("Tempos gastos de 1.000 em 1.000 números:\n\n");
	for (int i = 0; i<10; i++) {
		printf("Tempo gasto para %d: %f\n", 1000*(i+1), tempos[i]);
	}

	return 0;
}