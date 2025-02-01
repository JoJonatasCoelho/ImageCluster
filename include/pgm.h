#ifndef PGM_H
#define PGM_H

typedef struct {
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
}pgm;


void readPGMImage(pgm *pio, char *filename);
void writePGMImage(pgm *pio, char *filename);
void viewPGMImage(pgm *pio);


#endif
