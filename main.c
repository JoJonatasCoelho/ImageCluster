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
	

	cluster(&img, &out, k);
	writePGMImage(&img, argv[2]);

    return EXIT_SUCCESS;
}
