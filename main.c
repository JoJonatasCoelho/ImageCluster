#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include "include/pgm.h"
#include "include/cluster.h"
#include "include/dice.h"

#define QTDIMG 1000

int main(int argc, char *argv[])
{

   	if (argc!=4){
    	printf("Formato: \n\t %s <./input dir> <output dir> <k clusters>\n",argv[0]);
	    exit(1);
   	}


	clock_t begin, end;
	double time_per_img, time_total=0;


    begin = clock();


	int k = atoi(argv[3]);

    float *dist = NULL;
    unsigned char *clusters = NULL;
    float *c = NULL;
    float *c2 = NULL;

	for (unsigned long i=0; i<QTDIMG; i++){

        pgm img = {0};
        pgm out = {0};

	    readPGMImage(&img,argv[1]);

    	out.c  = img.c;
	    out.r = img.r;
    	out.mv = img.mv;
    	out.tipo = img.tipo;
    	out.pData = (unsigned char*) malloc(img.c * img.r * sizeof(unsigned char));
        if (!out.pData) {
            fprintf(stderr, "Erro ao alocar memória para out.pData.\n");
            exit(1);
        }

        if (!dist) dist = malloc(img.c * img.r * sizeof(float));
        if (!clusters) clusters = malloc(img.c * img.r * sizeof(unsigned char));
        if (!c) c = malloc(k * sizeof(float));
        if (!c2) c2 = malloc(k * sizeof(float));

        if (!dist || !clusters || !c || !c2) {
            fprintf(stderr, "Erro ao alocar memória para buffers reutilizáveis.\n");
            free(img.pData);
            free(out.pData);
            return EXIT_FAILURE;
        }


        if (cluster(img.pData, out.pData, k, img.c * img.r, dist, clusters, c, c2)) {
		    puts("Erro ao clusterizar imagem");
	    }


        if (!img.pData || !out.pData) {
            fprintf(stderr, "Erro: img.pData ou out.pData é NULL.\n");
            exit(1);
        }

	    writePGMImage(&out, argv[2]);

        free(img.pData);

        free(out.pData);
	}


	end = clock();


	time_total = (double)(end - begin) / CLOCKS_PER_SEC;


	printf("Tempo Total: %lf\n",time_total);


    return EXIT_SUCCESS;
}
