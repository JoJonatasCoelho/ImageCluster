#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MX_INTERA 10

#include "../include/cluster.h"
#include "../include/pgm.h"

void centroides_iniciais(int k, float *c, pgm *pio){
	for(int i=0; i<k; i++){
		c[i] = pio->pData[rand()%(pio->c*pio->r)];
	}
}
void calcular_distancia(int k, pgm *pio, float *c, unsigned char *clusters, float *dist){
	

		for(int j=0; j<k; j++){//for para percorrer os centroides
			for(unsigned long i=0; i<(pio->r * pio->c); i++){ //for para percorrer os pixels da imagem		
				float dist_atual = fabsf(c[j]-pio->pData[i]);
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


void novosCentroides(pgm *pio, float *c, int k){
	unsigned sum = 0;
	for(int j=0; j<k; j++){
		sum = 0;
		for(unsigned long i=0; i<(pio->r*pio->c); i++){
			sum += pio->pData[i];
		}
		c[j] = sum/(pio->r*pio->c);
	}
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
void preencherPGM(const unsigned char const *pDataIn, unsigned char *pDataout,const unsigned char *clusters, const unsigned k, const unsigned long tam, float *c){
	unsigned char *cores = malloc(sizeof(unsigned char) * k);
		
		for(unsigned char i=0; i<k; i++){
			cores[i] = pDataIn[(int) c[i]];

		} 
		for(unsigned long j=0; j<tam; j++){
			pDataout[j] = cores[clusters[j]];
		}	
}

int cluster (pgm *pin, pgm *pout, const unsigned k){
	//int n=0;
	unsigned char convergiu = 0;

	float *dist=malloc((pin->c*pin->r)*sizeof(float));
	
	unsigned char *clusters = malloc((pin->r*pin->c) * sizeof(unsigned char));
	if(!clusters)
		return 1;

	float *c = malloc(k * sizeof(float));
	if(!c)
		return 1;
	float *c2 = malloc(k * sizeof(float));
	if(!c2)
		return 1;

	unsigned long tam = ((pin->c)*(pin->r));

/*

	/*do{
		centroides_iniciais(k, c,pin);
		calcular_distancia(k, pin , c , clusters, dist);
		for(int i=0; i<k; i++){
			c2[i] = c[i];
		}
		novosCentroides(pin, c, k);
		naoConvergiu = converge(c, c2, k);
		if(n == 0){
			for(int i=0; i<k; i++) c2[i] = c[i];
			naoConvergiu = 0;
		}
		n++;
	}while(naoConvergiu || n != MX_INTERA);

	*/

	for(int n = 0; n <= MX_INTERA; n++){
		centroides_iniciais(k, c,pin);
		calcular_distancia(k, pin , c , clusters, dist);
		for(int i=0; i<k; i++){
			c2[i] = c[i];
		}
		novosCentroides(pin, c, k);
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


	preencherPGM(pin->pData,pout->pData, clusters, k, tam, c);
	
	free(c);
	free(clusters);

	return 0;
}
