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
int transactionCreditP(char* transactionAmount, char* cardNumber){
  printf("Logando no Arquivo logTransaction\n");
  printf("\n\n>>Valor do Amount Inputado: %s<<\n\n", transactionAmount);
  printf("\n\n>>Valor do Amount Inputado: %s<<\n\n", cardNumber);
  logTransaction(cardNumber, transactionAmount);

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
