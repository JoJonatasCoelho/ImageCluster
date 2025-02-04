#ifndef CLUSTER_H
#define CLUSTER_H
#include "pgm.h"

void centroides_iniciais(unsigned char *imgData, unsigned long tam, int k, float *c );
void calcular_distancia(unsigned char *imgData, unsigned char *clusters, unsigned k, float *c,  float *dist, unsigned long tam);
int novosCentroides(unsigned char *imgData, unsigned char *clusters,  unsigned long tam, float *c, unsigned k);
int converge(float *c,float *c2, int k);
int preencherPGM(const unsigned char const *pDataIn, unsigned char *pDataout,const unsigned char *clusters, const unsigned k, const unsigned long tam, float *c);
int cluster (unsigned char *pDataIn, unsigned char *pDataOut, const unsigned k, unsigned long tam);
#endif