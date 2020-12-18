/*
    Linked list taken from: https://github.com/skorks/c-linked-list/blob/master/linkedlist.c,
    All rights to Alan Sorkins for providing the code on GitHub.
    Some of the methods were modified to better suit the system.
*/

// Imovel struct will be defined here to be used in the linked list code.
typedef struct Imovel{
    int codigo;
    char endereco[10];
    float preco;
    char bairro[10];
} imovel;

// Imovel constructor based on the struct.
imovel* spawn_imovel(int codigo, char *endereco, float preco, char *bairro) { 
  imovel* new_imovel = malloc(sizeof(imovel));
  
  new_imovel->codigo = codigo;
  strcpy(new_imovel->endereco, endereco);
  new_imovel->preco = preco;
  strcpy(new_imovel->bairro, bairro);

  return new_imovel;
}


typedef struct node {
  imovel* imovel;
  int id;
  struct node * next;
  struct node * previous;
  struct node * current;

} Node;

typedef struct list {
  Node * head; 
  int size;
} List;

Node * createnode(imovel* imovel, int id){
  Node * newNode = malloc(sizeof(Node));
  if (!newNode) {
    return NULL;
  }
  newNode->imovel = imovel;
  newNode->id = id;
  newNode->next = NULL;
  return newNode;
}

List * makelist(){
  List * list = malloc(sizeof(List));
  if (!list) {
    return NULL;
  }
  list->head = NULL;
  return list;
}

void display(List * list) {
  Node * current = list->head;
  if(list->head == NULL) 
    return;
  
  for(; current != NULL; current = current->next) {
    printf("%s\n", current->imovel->endereco);
  }
}

void add(int id, imovel* imovel, List * list){
  Node * current = NULL;
  if(list->head == NULL){
    list->head = createnode(imovel, id);
  }
  else {
    current = list->head; 
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createnode(imovel, id);
  }
  list->size++;
}

void delete(imovel* imovel, List * list){
  Node * current = list->head;            
  Node * previous = current;           
  while(current != NULL){           
    if(current->imovel == imovel){      
      previous->next = current->next;
      if(current == list->head)
        list->head = current->next;
      list->size--; 
      return;
    }                               
    previous = current;             
    current = current->next;  
  }                                 
}

Node* getNodeAtIndex(int id, List * list){
  Node * current = list -> head;
  int count = 1;
  while(current!=NULL){
    if(count == id){
      return current;
    }
    count++;
    current = current ->next;
  } 
  return NULL;                    
}