# ImageCluster

# Clusterização de Imagens PGM usando K-Means

Este projeto implementa um algoritmo de clusterização K-Means para imagens no formato PGM (Portable Gray Map). O objetivo é agrupar os pixels da imagem em k clusters, onde k é um número fornecido pelo usuário. O algoritmo atribui cada pixel ao cluster mais próximo e recalcula os centroides até que a convergência seja alcançada.

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- *cluster.c*: Contém a implementação do algoritmo K-Means para clusterização de imagens.
- *pgm.c*: Contém funções para leitura e escrita de arquivos PGM.
- *main.c*: Arquivo principal que lida com a entrada do usuário e executa o processo de clusterização.

## Como Compilar e Executar

### Compilação

Para compilar o projeto, utilize o seguinte comando:

```bash
make
```

## Execução

- *Crie o diretório de saida antes de executar o programa*

  ```bash
  mkdir saida
  ```
- Para a execução use ./cluster <diretório_entrada/>  <diretório_saida/> <k_cluster>

  ```bash
  ./cluster dataset/ saida/ k //ex: k = 3
  ```

## Histograma

Os histogramas são feitos a partir de um programa a parte que os armazena em csv

* Crie um diretório para armazenar os histogramas

  ```bash
  mkdir histogramas
  ```
* Compile usando

  ```bash
  gcc -o hist -I include/ histograma.c 
  ```
* Execute

  ```bash
  ./hist dataset/ histogramas
  ```
* Para os visualizar é esperado que no seu computador já tenhas (em uma venv de preferencia)

  - pandas
  - matplotlib
  - tkinter
* A partir daí para visualizar rode o comando:

  ```bash
  python3 ver_hist.py
  ```
  e então selecione o histograma desejado
