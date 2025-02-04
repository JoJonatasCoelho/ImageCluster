#include <stdio.h>
#include <stdlib.h>
#include "include/pgm.h"
#include "include/cluster.h"

int main(int argc, char *argv[])
{
    pgm img;
	pgm out;

	if (argc!=4){
		printf("Formato: \n\t %s <imagemEntrada.pgm> <imagemSaida.pgm> <numeroCluster>\n",argv[0]);
		exit(1);
	}
	int k = atoi(argv[3]);

	readPGMImage(&img,argv[1]);

	out.c  = img.c ;
	out.r = img.r;
	out.mv = img.mv;
	out.tipo = img.tipo;
	

	cluster(img.pData, out.pData, k, img.c * img.r );

	writePGMImage(&out, argv[2]);

    return EXIT_SUCCESS;
}
