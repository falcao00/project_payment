#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "accountFunctions.h"

#define DATA_SIZE 1000

typedef struct{
     char name[20];
     char password[20];
     int  id[5];
} data;

int accountCreation(void){
  data acc;
  char data[DATA_SIZE];
  
  printf("Inserir Nome:");
  scanf("%s", acc.name);
  printf("\n");
  printf("Inserir Senha:");
  scanf("%s", acc.password);
  printf("\n");
  printf("Confirme as Informações: [Nome: %s];[Senha: %s]\n", acc.name, acc.password);
  sprintf(data, "[Nome: %s];[Senha: %s]", acc.name, acc.password);

  FILE * fileAccount;
  fileAccount = fopen("../accounts/account_id_x.txt", "w");
  if(fileAccount == NULL){
    printf("Erro ao Criar Arquivo\n");
    exit(EXIT_FAILURE);
  }
  fgets(data, DATA_SIZE, stdin);
  fputs(data, fileAccount);
  fclose(fileAccount);
  printf("File created and saved successfully. :) \n");

  return 0;
}
