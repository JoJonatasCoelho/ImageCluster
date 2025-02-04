#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MX_INTERA 10

#include "../include/cluster.h"
#include "../include/pgm.h"

void centroides_iniciais(unsigned char *imgData, unsigned long tam, int k, float *c ){
	for(int i=0; i<k; i++){
		c[i] = imgData[rand()%(tam)];
	}
}

void calcular_distancia(unsigned char *imgData, unsigned char *clusters, unsigned k, float *c,  float *dist, unsigned long tam){

		for(int j=0; j<k; j++){//for para percorrer os centroides
			for(unsigned long i=0; i<(tam); i++){ //for para percorrer os pixels da imagem
				float dist_atual = fabsf(c[j] - imgData[i]);
				if(j==0){
					dist[i] = dist_atual;
					clusters[i] = j; // j representa o grupo aqui e mask é uma mascara que determina o grupo pertecente a aquele pixel
				}

				if (dist[i] > dist_atual){
					clusters[i] = j;
					dist[i] = dist_atual;
				}
			}
		}
}


int novosCentroides(unsigned char *imgData, unsigned char *clusters,  unsigned long tam, float *c, unsigned k){

	unsigned long *sums = NULL;
	if((*sums= malloc(k * sizeof(unsigned long))) == NULL)
		return EXIT_FAILURE;
	
	unsigned long *counts = NULL;
	if((*counts= malloc(k * sizeof(unsigned long))) == NULL)
		return EXIT_FAILURE;

	unsigned cluster = 0;
	for(unsigned long  i=0; i<tam; i++){
		cluster = *(clusters + i);		
		*(sums + cluster) += *(imgData + i);
		*(counts + cluster) += 1;
	}

	for (unsigned i = 0; i < k; i++)
	{
		*(c + i) = *(sums + i) / *(counts + i);
	}
	free(counts);
    free(sums);

	return EXIT_SUCCESS;
	
}

int converge(float *c,float *c2, int k){
	int convergiu = 0;
	for(int j=0; j<k; j++){
		if (c2[j] == c[j]) convergiu ++;
	}
	if (convergiu = k)
		return 1;
	return 0;
}
int preencherPGM(const unsigned char const *pDataIn, unsigned char *pDataout,const unsigned char *clusters, const unsigned k, const unsigned long tam, float *c){
	unsigned char *cores = malloc(sizeof(unsigned char) * k);

    if (!cores) {
	    fprintf(stderr, "Erro ao alocar memória para cores.\n");
        return EXIT_FAILURE;
    }


		for(unsigned char i=0; i<k; i++){
			cores[i] = pDataIn[(int) c[i]];

		}
		for(unsigned long j=0; j<tam; j++){
			pDataout[j] = cores[clusters[j]];
		}
		
		return EXIT_SUCCESS;
}

int cluster (unsigned char *pDataIn, unsigned char *pDataOut, const unsigned k, unsigned long tam){

	unsigned char convergiu = 0;

	float *dist=malloc((tam) * sizeof(float));

	unsigned char *clusters = malloc((tam) * sizeof(unsigned char));
	if(!clusters)
		return EXIT_FAILURE;

	float *c = malloc(k * sizeof(float));
	if(!c)
		return EXIT_FAILURE;

	float *c2 = malloc(k * sizeof(float));
	if(!c2)
		return EXIT_FAILURE;

	for(int n = 0; n <= MX_INTERA; n++){
		centroides_iniciais(pDataIn, tam, k, c);
		calcular_distancia(pDataIn, clusters, k, c, dist, tam);
		for(int i=0; i<k; i++){
			c2[i] = c[i];
		}
		novosCentroides(pDataIn, clusters, tam, c, k);
		convergiu = converge(c, c2, k);
		if(n == 0){
			for(int i=0; i<k; i++) c2[i] = c[i];
			convergiu = 0;
		}

		if(convergiu == k)
			break;

	}

	free(dist);
	free(c2);


	preencherPGM(pDataIn, pDataOut, clusters, k, tam, c);

	free(c);
	free(clusters);

	return EXIT_SUCCESS;
}
