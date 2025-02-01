#include <stdio.h>
#include <stdlib.h>
#include "include/pgm.h"

int main(int argc, char *argv[])
{
    pgm img;


	if (argc!=3){
		printf("Formato: \n\t %s <imagemEntrada.pgm> <imagemSaida.pgm>\n",argv[0]);
		exit(1);
	}


	readPGMImage(&img,argv[1]);


	writePGMImage(&img, argv[2]);


	viewPGMImage(&img);


    return EXIT_SUCCESS;
}
