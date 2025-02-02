#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MX_INTERA 10;

#include "../include/cluster.h"

void centroides_iniciais(int k, float *c, pgm *pio){
	for(int i=0; i<k; i++){
		c[i] = pio->pData[rand()%(pio->c*pio->r)];
	}
}
void calcular_distancia(int k, pgm *pio, float *c, unsigned char *dist){
	for(int j=0; j<k; k++){//for para percorrer os centroides
		for(int i=0; i<(pio->r*pio->r); i++){ //for para percorrer os pixels da imagem		
			int dist_atual = abs(c[k]-pio->pData[i]);
			if(j=0){
				dist[i] = dist_atual; 
				pio->mask[i] = j; // j representa o grupo aqui e mask é uma mascara que determina o grupo pertecente a aquele pixel
			}

			if (dist[i] > dist_atual){
				pio->mask[i] = j;
				dist[i] = dist_atual;
				
			}
		}
	}
}


void novosCentroides(pgm *pio, float *c, int k){
	unsigned sum = 0;
	for(int j=0; j<k; j++){
		sum = 0;
		for(int i=0; i<(pio->r*pio->c); i++){
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

void cluster (pgm *pin, pgm *pout, float *c,float *c2, int k, unsigned char *dist){
	int n=0;
	unsigned char naoConvergiu = 0;
	do{
		centroides_iniciais(k, c,pin);
		calcular_distancia(k, pin , c , dist);
		novosCentroides(pin, c, k);
		naoConvergiu = converge(c, c2, k);
		if(n==0){
			for(int i=0; i<k; i++) c2[i] = c[i];
			naoConvergiu = 0;
		}
		n++;
	}while(naoConvergiu || n!=MX_INTERA)
}
