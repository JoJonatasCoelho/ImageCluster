/****************************************************************************
*                                                                          
* Aluno: Jonatas Cleyton Fonseca Coelho                                                
* Matricula: 20241045050120                                                          
*                                                                          
* Avaliacao 04: Trabalho Final                                              
* 04.505.23-2024.2 - Prof. Daniel Ferreira                                  
*                                                                          
* Compilador: gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04)                    
*                                                                           
****************************************************************************/
#include <stdio.h>
#include "../include/histograma.h"

Histograma calcular_histograma(const unsigned char *imagem, unsigned long tamanho) {
    Histograma hist = {{0}, 0};

    // conta intensidades
    for (unsigned long i = 0; i < tamanho; i++) {
        int intensidade = *(imagem + i);
        hist.bins[intensidade]++;
    }

    // encontra o valor máximo para normalização
    for (int i = 0; i < 256; i++) {
        if (hist.bins[i] > hist.max_count) {
            hist.max_count = hist.bins[i];
        }
    }

    return hist;
}

void salvar_histograma(const Histograma *h, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao criar arquivo de histograma");
        return;
    }

    fprintf(file, "Intensidade,Contagem,Normalizado\n");
    for (int i = 0; i < 256; i++) {
        float normalizado = (h->max_count > 0) ? (float)h->bins[i] / h->max_count : 0;
        fprintf(file, "%d,%d,%.4f\n", i, h->bins[i], normalizado);
    }

    fclose(file);
}
