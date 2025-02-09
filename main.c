/****************************************************************************
*                                                                          
* Aluno: Jonatas Cleyton Fonseca Coelho                                                      
* Matricula: 12345                                                          
*                                                                          
* Avaliacao 04: Trabalho Final                                              
* 04.505.23-2024.2 - Prof. Daniel Ferreira                                  
*                                                                          
* Compilador: gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04)                    
*                                                                           
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include "include/pgm.h"
#include "include/cluster.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

   	if (argc!=4){
    	printf("Formato: \n\t %s <input_dir/> <output_dir/> <k clusters>\n",argv[0]);
	    exit(1);
   	}

    DIR *d;
    struct dirent *dir;

    d = opendir(argv[1]);

	clock_t begin, end;
	double time_total=0;


    begin = clock();

    if(!d){
        perror("Erro ao abrir diretório");
        return EXIT_FAILURE;
    }

    int k = atoi(argv[3]);

    float *dist = NULL;
    unsigned char *clusters = NULL;
    float *c = NULL;
    float *c2 = NULL;


    char filepath[1024]; // buffer para armazenar o caminho completo
    char outpath[1024]; // mesma coisa para o caminho de saida



    while ((dir = readdir(d)) != NULL){

        pgm img = {0};
        pgm out = {0};
        // zero o valor dos structs sempre

        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) { // pra se livrar de um bug
            continue;
        }

        snprintf(filepath, sizeof(filepath), "%s%s", argv[1], dir->d_name); //formatando o caminho para "filepath"

        readPGMImage(&img, filepath);

        if (!img.pData) {
            fprintf(stderr, "Erro ao ler a imagem: %s\n", filepath);
            return EXIT_FAILURE; //para a execuçao do programa caso aja falha ao ler uma imagem sequer
        }

        out.c = img.c;
        out.r = img.r;
        out.mv = img.mv;
        out.tipo = img.tipo;

        out.pData = (unsigned char*) malloc(img.c * img.r * sizeof(unsigned char));
        if (!out.pData) {
            fprintf(stderr, "Erro ao alocar memória para out.pData.\n");
            continue;
        }

        if (!c) c = malloc(k * sizeof(float));
        if (!c2) c2 = malloc(k * sizeof(float));

        dist = malloc(img.c * img.r * sizeof(float));
        clusters = malloc(img.c * img.r * sizeof(unsigned char));

        if (!dist || !clusters || !c || !c2) {
            fprintf(stderr, "Erro ao alocar memória para buffers reutilizáveis.\n");
            free(img.pData);
            free(out.pData);
            closedir(d);
            return EXIT_FAILURE; // se os buffers nao sao criados adequamente apenas fecho o programa
        }


        if (cluster(img.pData, out.pData, k, img.c * img.r, dist, clusters, c, c2)) {
            fprintf(stderr, "Erro ao clusterizar imagem.\n");
            return EXIT_FAILURE; // a clusterizaçao falhou
        }


        if (!img.pData || !out.pData) {
            fprintf(stderr, "Erro: img.pData ou out.pData é NULL.\n");
            return EXIT_FAILURE;
        }

        snprintf(outpath, sizeof(outpath), "%s%s%s",  argv[2], "out-",dir->d_name); // formatando saida

        writePGMImage(&out, outpath);

        if (img.pData) {
            free(img.pData);
            img.pData = NULL;
        }

        if (out.pData) {
            free(out.pData);
            out.pData = NULL;
        }
    }

    closedir(d); //fecha o arquivo do diretorio

    if (dist) free(dist);
    if (clusters) free(clusters);
    if (c) free(c);
    if (c2) free(c2);

    //frees

	end = clock();


	time_total = (double)(end - begin) / CLOCKS_PER_SEC;


	printf("Tempo Total: %lf\n",time_total);


    return EXIT_SUCCESS;
}
