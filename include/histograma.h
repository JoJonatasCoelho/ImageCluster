#ifndef HISTOGRAMA_H
#define HISTOGRAMA_H

typedef struct {
    int bins[256];    // contagem para cada intensidade (0-255)
    int max_count;    // maior contagem encontrada (para normalização)
} Histograma;

Histograma calcular_histograma(const unsigned char *imagem, unsigned long tamanho);
void salvar_histograma(const Histograma *h, const char *filename);

#endif
