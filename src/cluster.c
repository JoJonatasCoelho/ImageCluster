/****************************************************************************
*                                                                          
* Aluno: Jonatas Cleyton Fonseca Coelho, Luiz Henrique Leite Porto Maia                                                      
* Matricula: 20241045050120 , 20241045050618                                                         
*                                                                          
* Avaliacao 04: Trabalho Final                                              
* 04.505.23-2024.2 - Prof. Daniel Ferreira                                  
*                                                                          
* Compilador: gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04)                    
*                                                                           
****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#include "../include/cluster.h"

void centroides_iniciais(unsigned char *imgData, unsigned long tam, int k, float *c ){
	#pragma omp parallel for
	for(int i = 0; i < k; i++){
		*(c + i) = imgData[rand() % tam];//escolhendo os centroides de forma aleatória
	}
}

void calcular_distancia(unsigned char *imgData, unsigned char *clusters, unsigned k, float *c,  float *dist, unsigned long tam){

    memset(dist, 0, tam * sizeof(float));

		#pragma omp parallel for
		for(int j = 0; j < k; j++){//for para percorrer os centroides
			for(unsigned long i = 0; i < tam; i++){ //for para percorrer os pixels da imagem
				float dist_atual = fabsf(c[j] - imgData[i]); // calculo da distancia de forma linear por conta dos valores das cores mudarem linearmente
				if(j == 0){ // na primeira iteração todos sao do mesmo grupo
					dist[i] = dist_atual;
					clusters[i] = j; // j representa o grupo aqui e clusters é uma mascara que determina o grupo pertecente a aquele pixel
				}

				if (dist[i] > dist_atual){ // a partir das próximas iteraçoes e achado o verdadeiro grupo de cada pixel
					clusters[i] = j;
					dist[i] = dist_atual;
				}
			}
		}
}


int novosCentroides(unsigned char *imgData, unsigned char *clusters,  unsigned long tam, float *c, unsigned k){

	unsigned long sums = 0; // variaveis necessarias para fazer a media do kmeans

	unsigned long counts = 0;

	
	for (unsigned i = 0; i < k; i++)
	{
        sums = 0;
        counts = 0;

	    for(unsigned long j = 0; j < tam; j++){
		    sums += (*(clusters + j) == i) ? *(imgData + j) : 0;
    		counts += (*(clusters + j) == i) ? 1 : 0;
    	}

		if (counts != 0){
		    *(c + i) = (float) sums / counts;
            *(c + i) = (*(c + i) > 255) ? 255 : *(c + i); // o valor maximo e 255 por isso e feito esse ternario
        }else
            *(c + i) = *(c + i); // caso haja erro na media o cluster continua o mesmo
}

	return EXIT_SUCCESS;

}

int converge(float *c,float *c2, int k){
	int convergiu = 0;

	#pragma omp parallel for reduction(+:convergiu)
	for(int j = 0; j < k; j++){
		if (c2[j] == c[j]) convergiu ++;
	}
	if (convergiu == k)
		return CONVERGIU;
	return DIVERGIU;
}
int preencherPGM(const unsigned char *pDataIn, unsigned char *pDataout,const unsigned char *clusters, const unsigned k, const unsigned long tam, float *c){
	#pragma omp parallel for
	for(unsigned long j = 0; j < tam; j++){
		*(pDataout + j) = (int)*(c + *(clusters + j));
	}

	return EXIT_SUCCESS;
}

int cluster(unsigned char *pDataIn, unsigned char *pDataOut, const unsigned k, unsigned long tam, float *dist, unsigned char *clusters, float *c, float *c2) {
    unsigned char convergiu = 0;

    for (int n = 0; n <= MX_INTERA; n++) {
        centroides_iniciais(pDataIn, tam, k, c);
        calcular_distancia(pDataIn, clusters, k, c, dist, tam);
        for (int i = 0; i < k; i++) {
            c2[i] = c[i];
        }
        if (novosCentroides(pDataIn, clusters, tam, c, k)) return EXIT_FAILURE;
        convergiu = converge(c, c2, k);
        if (n == 0) {
            for (int i = 0; i < k; i++) c2[i] = c[i];
            convergiu = 0;
        }

        if (convergiu == k)
            break;
    }

    if (preencherPGM(pDataIn, pDataOut, clusters, k, tam, c)) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
