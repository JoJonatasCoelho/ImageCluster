#ifndef CLUSTET_H
#define CLUSTER_H
void centroides_iniciais(int k, float *c, pgm *pio);
void calcular_distancia(int k, pgm *pio, float *c, unsigned char *dist);
void novosCentroides(pgm *pio, float *c, int k);
int converge(float *c,float *c2, int k);
void cluster(pgm *pin, pgm *pout, float *c,float *c2, int k, unsigned char *dist);
#endif