#ifndef CLUSTER_H
#define CLUSTER_H

#define MX_INTERA 10
#define CONVERGIU 1
#define DIVERGIU 0

void centroides_iniciais(unsigned char *imgData, unsigned long tam, int k, float *c );
void calcular_distancia(unsigned char *imgData, unsigned char *clusters, unsigned k, float *c,  float *dist, unsigned long tam);
int novosCentroides(unsigned char *imgData, unsigned char *clusters,  unsigned long tam, float *c, unsigned k);
int converge(float *c,float *c2, int k);
int cluster(unsigned char *pDataIn, unsigned char *pDataOut, const unsigned k, unsigned long tam, float *dist, unsigned char *clusters, float *c, float *c2);
int preencherPGM(const unsigned char *pDataIn, unsigned char *pDataout,const unsigned char *clusters, const unsigned k, const unsigned long tam, float *c);

#endif
