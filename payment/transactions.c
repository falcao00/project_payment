#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "transactions.h"
#include "accountFunctions.h"

extern struct cardInfo falcon;
extern struct cardInfo helena;

/***
 * Compra Credito Parcelada
 * Com um Juros de 0.5 * Numero de Parcelas 
 * 
*/
int transactionCreditP(char* transactionAmount, char* cardNumber, int numParcelas, char* cardPassword){
  printf("Logando no Arquivo logTransaction\n");
  printf("\n\n>>Valor do Amount Inputado: %s<<\n\n", transactionAmount);
  printf("\n\n>>Valor do Amount Inputado: %s<<\n\n", cardNumber);
  printf("\n\n>>Valor do Amount Inputado: %d<<\n\n", numParcelas);
  printf("\n\n>>Valor do Amount Inputado: %s<<\n\n", cardPassword);

  //checkaccounts()
  FILE* fileAccount = fopen("../accounts/account-card.txt", "r");
  if(fileAccount == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }
  char tmpAcountValue[1024];
  fgets(tmpAcountValue, sizeof(tmpAcountValue), fileAccount);
  printf("\n\n>>>>>>Valores do Arquivo: %s<<<<<<\n\n", tmpAcountValue); //0001;123;200
  char valuesAccount[sizeof(tmpAcountValue)];
  strcpy(valuesAccount, strtok(tmpAcountValue, ";"));
  while (valuesAccount != NULL)
  {
    printf("Atributo: %s\n\n", valuesAccount);
    strcpy(valuesAccount, strtok(NULL, ";"));
  }
  printf("\n\n>>>>CHEGA AQUI?<<<<\n\n");
  
  fclose(fileAccount);

  //loga a transação no arquivo de estorno
  //logTransaction(cardNumber, transactionAmount);

  return 0;
}

int transactionPix(int transactionAmount, char pixChave){
  
  if(transactionAmount <= 0 /*|| pixChave == NULL*/)
    return -1;

  *falcon.amount = *falcon.amount - transactionAmount;
  printf("Valor final em conta: %d\n", *falcon.amount);
  return 0;
}

int logTransaction(char* value1, char* value2){

  FILE * LogTransfile;
  LogTransfile = fopen("../logTransaction/logTransFile.txt", "w");
  char transValue[20];
  strcpy(transValue, value1);
  strcat(transValue, ";");
  strcat(transValue, value2);
  fputs(transValue, LogTransfile);
  fclose(LogTransfile);
  return 0;
}
