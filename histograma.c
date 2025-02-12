#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "include/histograma.h"
#include "include/pgm.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Formato: \n\t %s <input_dir>/ <output_dir>/\n", argv[0]);
        exit(1);
    }

    DIR *d = opendir(argv[1]);
    if (!d) {
        perror("Erro ao abrir diretório");
        return EXIT_FAILURE;
    }

    struct dirent *dir;
    char filepath[1024];
    char outpath[1024];

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        if (strstr(dir->d_name, ".pgm") == NULL) continue;

        pgm img = {0};
        snprintf(filepath, sizeof(filepath), "%s%s", argv[1], dir->d_name);

        readPGMImage(&img, filepath);
        if (!img.pData) {
            fprintf(stderr, "Erro ao ler: %s\n", filepath);
            continue;
        }

        Histograma hist = calcular_histograma(img.pData, img.c * img.r);

        snprintf(outpath, sizeof(outpath), "%shist_%s.csv", argv[2], dir->d_name);
        salvar_histograma(&hist, outpath);

        free(img.pData);
    }

    closedir(d);
    return EXIT_SUCCESS;
}


