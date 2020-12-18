#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "./linkedList.c"

// Global variables go here.

pthread_mutex_t corretores_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t inquilinos_mutex = PTHREAD_MUTEX_INITIALIZER;
#define NUM_THREADS 16
List * imoveisDisponiveis;
List * imoveisEntregues;

// Corretores thread actions start here.


void corretor_add_imovel(void * threadId){

  //Finds last item on the list so to add the new imovel there;
  int indexToAdd = imoveisDisponiveis->size;

  //Generates a random number between 1-150 to be used as an address;
  char endereco[10];
  int random_int = (rand() % 150) + 1;
  sprintf(endereco, "%d", random_int);

  //Creates new imovel with random number set as address.
  imovel* novo_imovel = spawn_imovel(indexToAdd, endereco, 0, "");

  pthread_mutex_lock(&corretores_mutex);
    add(indexToAdd, novo_imovel, imoveisDisponiveis);
    printf("Corretor %d adiciona imovel: %s\n", * (int*)threadId, novo_imovel->endereco);
  pthread_mutex_unlock(&corretores_mutex);

  sleep(2); 
}

void corretor_disponibiliza_imoveis(void *threadId){
  //Finds last item on the list so to add the new imovel there;
  int indexToAdd = imoveisDisponiveis->size;

  int i;

  //Check if there any imoveis to move;
  if(imoveisEntregues->size > 0){
    Node * node = malloc(sizeof(Node));
    //Finds each imovel from the list, adds to imoveisDisponiveis then deletes it from imoveisEntregues.
    for (i = 1; i <= imoveisEntregues->size; i++){
      node = getNodeAtIndex(i, imoveisEntregues);

      pthread_mutex_lock(&corretores_mutex);
        add(indexToAdd, node->imovel, imoveisDisponiveis);
        delete(node->imovel, imoveisEntregues);
        printf("Corretor %d disponibiliza imoveis da lista de entregues\n", * (int*)threadId);
      pthread_mutex_unlock(&corretores_mutex);

      sleep(2); 
    }
  } else {
    printf("Corretor %i sem imovel para disponibilizar\n", * (int*)threadId);
  } 
}

void corretor_deleta_imovel(void *threadId){

  if(imoveisDisponiveis->size > 0){
    Node * node = malloc(sizeof(Node));

    //Gets id from random imovel from imoveisDisponiveis and finds it's node;
    int imovel_to_delete = (rand() % imoveisDisponiveis->size) + 1;
    node = getNodeAtIndex(imovel_to_delete, imoveisDisponiveis);

    //Deletes it from the list.
    pthread_mutex_lock(&corretores_mutex);
      printf("Corretor %d remove imovel: %s\n", * (int*)threadId, node->imovel->endereco);
      delete(node->imovel, imoveisDisponiveis);
    pthread_mutex_unlock(&corretores_mutex); 


    sleep(2);

  } else {
    printf("Corretor %i sem imovel para remover\n", * (int*)threadId);
  } 
}

void *init_corretores_thread(void *arg){
    int acao_aleatoria = (rand() % 3) + 1;
    
    switch (acao_aleatoria){
    case 1:
      corretor_add_imovel(arg);
    break;
    case 2:
      corretor_deleta_imovel(arg);
    break;
    case 3:
      corretor_disponibiliza_imoveis(arg);
    break;
    default:
      printf("Acao nao encontrada na init_corretores_thread ");
    }      

    pthread_exit(NULL);
}



//Inquilinos thread actions start here.

   
void *init_inquilino_thread(void *arg){

    // Locks thread to define the id, did this because there were bugs assigning wrong ids after inquilinos slept at line 135;
    pthread_mutex_lock(&inquilinos_mutex);
        int id_inquilino = * (int*)arg;
    pthread_mutex_unlock(&inquilinos_mutex);

    Node * node = malloc(sizeof(Node));

    if(imoveisDisponiveis->size > 0){
      // Gets random index for imovel from imoveisDisponiveis list and finds its node;
      int random_index = (rand() % imoveisDisponiveis->size) + 1;
      node = getNodeAtIndex(random_index, imoveisDisponiveis);

      //Deletes imovel from imoveisDisponiveis;
      pthread_mutex_lock(&inquilinos_mutex);
          delete(node->imovel, imoveisDisponiveis);
          printf("Inquilino %d aluga imovel: %s\n", id_inquilino, node->imovel->endereco);
      pthread_mutex_unlock(&inquilinos_mutex);    
    } else{
      printf("Inquilino %d nao acha imovel para alugar\n", id_inquilino);
    }

    //Random interval from 1-10s;
    int sleep_secs = (rand() % 10) + 1;
    sleep(sleep_secs); 
    
    //Adds the imovel to the imoveisEntregues list.
    if(node){
      pthread_mutex_lock(&inquilinos_mutex);  
        add(node->id, node->imovel, imoveisEntregues);
        printf("Inquilino %d entrega imovel: %s\n", id_inquilino, node->imovel->endereco);
      pthread_mutex_unlock(&inquilinos_mutex);
    } else {
      printf("O inquilino %d nao entrega nenhuma propriedade\n", id_inquilino);
    }
    sleep(2);
    pthread_exit(NULL);
}



int main(void){
  //Inits random function with seed;
  time_t t;
  srand((unsigned) time(&t));

  //Create two arrays of threads to separate inquilinos from corretores;
  pthread_t inq[NUM_THREADS];
  pthread_t cor[NUM_THREADS];

  //Inits lists that will house imoveis;
  imoveisDisponiveis = makelist();
  imoveisEntregues = makelist();

  //Populates the lists with some imoveis to start with;
  int i;
  char int_to_char[10];
  for (i = 1; i <= NUM_THREADS; i++){
    sprintf(int_to_char, "%d", (rand() % 150) + 1);
    add(i, spawn_imovel(i,int_to_char,0, ""), imoveisDisponiveis);
  }
  for (i = 1; i <= NUM_THREADS/2; i++){
    sprintf(int_to_char, "%d", (rand() % 150) + 1);
    add(i, spawn_imovel(i,int_to_char,0, ""), imoveisEntregues);
  }

  //Prints the imoveis lists;
  printf("INÍCIO:\n");   
  printf("------------IMOVEIS ENTREGUES-----------\n");
  display(imoveisEntregues);
  printf("-----------IMOVEIS DISPONIVEIS------------\n");
  display(imoveisDisponiveis);
  printf("-----------------------\n");

  //Starts threads;
  for (i = 1; i <= NUM_THREADS; i++){
    pthread_create(&cor[i], NULL, init_corretores_thread, &i);
    pthread_create(&inq[i], NULL, init_inquilino_thread, &i); 
    sleep(1);   
  }

  //Ends threads;
  for (i = 1; i <= NUM_THREADS; i++){      
    pthread_join(cor[i], NULL);
    pthread_join(inq[i], NULL);
  }
  pthread_mutex_destroy(&corretores_mutex);
  pthread_mutex_destroy(&inquilinos_mutex);

  //Prints the final results.
  printf("FIM:\n");   
  printf("------------IMOVEIS ENTREGUES-----------\n");
  display(imoveisEntregues);
  printf("-----------IMOVEIS DISPONIVEIS------------\n");
  display(imoveisDisponiveis);

  return 0;
}