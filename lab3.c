#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

#define MAX_RANDOM_FLOAT 100000.0

long long int dim;
int nthreads;
float *vetor, minimo, maximo;

int ChecaCorretude(long int sequencial, long int paralela) {
   return sequencial == paralela;
}

//fluxo das threads
void * FuncaoDaThread(void * arg) {
   long int id = (long int) arg; 
   long int *contagemThread; 
   contagemThread = (long int*) malloc(sizeof(long int));

   if(contagemThread==NULL) {exit(1);}

   long int tamBloco = dim/nthreads;  
   long int ini = id * tamBloco; 
   long int fim; 
   
   if(id == nthreads-1) fim = dim;
   else fim = ini + tamBloco; 
  
   for(long int i=ini; i<fim; i++)
      if(vetor[i] > minimo && vetor[i] < maximo)
         *contagemThread = *contagemThread + 1;
  
   pthread_exit((void *) contagemThread); 
}

int main(int argc, char *argv[]) {

    // Variáveis para medição de tempo
    double inicio, fim;

    // recebe os limites mínimo e máximo, e o número de threads
    if(argc < 4) {
        fprintf(stderr, "Digite: %s <dimensao do vetor> <limite inferior> <limite superior> <numero threads>\n", argv[0]);
        return 1;
    }

    dim = atoi(argv[1]);
    nthreads = atoi(argv[4]);
    minimo = atoi(argv[2]);
    maximo = atoi(argv[3]);
    vetor = (float*) malloc(dim * sizeof(float));

    if(vetor == NULL) {
        fprintf(stderr, "Erro - Dimensão do vetor grande demais");
        return 1;
    }
    
    // preenche o vetor com floats aleatórios até a constante MAX_RANDOM_FLOAT
    srand((unsigned int)time(NULL));

    for(long int i = 0; i<dim; i++) {
        vetor[i] =  ((float)rand()/(float)(RAND_MAX)) * MAX_RANDOM_FLOAT;
    }

    // Implementação seguencial
    GET_TIME(inicio);

    long int resultadoSequencial = 0;
    for(long int i = 0; i<dim; i++)
        if(vetor[i] > minimo && vetor[i] < maximo)
            resultadoSequencial++;
    
    GET_TIME(fim);

    printf("Tempo Sequencial: %lf\n", fim - inicio);
    printf("Contagem Sequencial: %ld\n", resultadoSequencial);
    // Implementação paralela

   GET_TIME(inicio);
   pthread_t *tid;
   long int resultadoConcorrente = 0;
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);

   if(tid==NULL) {
      fprintf(stderr, "ERRO - Número de threads muito grande");
      return 1;
   }

    // Dispara as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, FuncaoDaThread, (void*) i)){
         fprintf(stderr, "Erro ao criar thread\n");
         return 1;
      }
   }


   //aguardar o termino das threads

   long int *resultadoThread;

   for(long int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), (void**) &resultadoThread)){
         fprintf(stderr, "Erro ao criar thread\n");
         return 1;
      }
      //soma global
      resultadoConcorrente += *resultadoThread;
   }

   GET_TIME(fim);

   printf("Tempo concorrente:  %lf\n", fim-inicio);
   printf("Contagem concorrente: %ld\n", resultadoConcorrente);


   if(ChecaCorretude(resultadoSequencial, resultadoConcorrente) == 1) {
      fprintf(stdout, "Resultado correto\n");
   } else {
      fprintf(stdout, "Resultado incorreto\n");
   }
   free(vetor);
   free(tid);

   return 0;
}



