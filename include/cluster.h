#ifndef CLUSTER_H
#define CLUSTER_H
#include "pgm.h"

void centroides_iniciais(int k, float *c, pgm *pio);
void calcular_distancia(int k, pgm *pio, float *c, unsigned char *clusters, float *dist);
void novosCentroides(pgm *pio, float *c, int k);
int converge(float *c,float *c2, int k);
void preencherPGM(const unsigned char const *pDataIn, unsigned char *pDataout,const unsigned char *clusters, const unsigned k, const unsigned long tam, float *c);
int cluster (pgm *pin, pgm *pout, const unsigned k);
#endif