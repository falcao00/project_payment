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
  //validacao(-1) valores não validos
  int tmpTransAmount = atoi(transactionAmount);
  if(tmpTransAmount < 0 || numParcelas <= 1 || numParcelas > 18)
    return -1;
  
  char cardNumberAccount[1024];
  char passWordNumberAccount[1024];
  char creditCardAmountAccount[1024];

  //checkaccounts()
  FILE* fileAccount = fopen("../accounts/account-card.txt", "r");
  if(fileAccount == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }
  char tmpAcountValue[1024];
  fgets(tmpAcountValue, sizeof(tmpAcountValue), fileAccount);
  char valuesAccount[sizeof(tmpAcountValue)];
  strcpy(valuesAccount, strtok(tmpAcountValue, ";"));
  //struct cardInfo account;
  //populando as Variaveis com as informações do Cartao
  for (int i = 0; i < 3; i++)
  {
    if(i == 0) {
      strcpy(cardNumberAccount, valuesAccount);
    } else if (i == 1) { 
      strcpy(passWordNumberAccount, valuesAccount);
    } else {
      strcpy(creditCardAmountAccount, valuesAccount);
      break;
    }
    strcpy(valuesAccount, strtok(NULL, ";"));
  }

  //validacao(-2) digitar o cartao ou senha errada
  int comp = strcmp(cardNumber, cardNumberAccount);
  int comp2 = strcmp(cardPassword, passWordNumberAccount);
  if(strcmp(cardNumber, cardNumberAccount) != 0 || strcmp(cardPassword, passWordNumberAccount) != 0)
    return -2;

  //logica da transação
  float juros = tmpTransAmount * (numParcelas * 0.01); 
  float finalValueTransaction = tmpTransAmount + juros;
  char transValueFinal[1024];
  sprintf(transValueFinal,"%.2f",finalValueTransaction);
  int tmpAccountAmount = atoi(creditCardAmountAccount);
  finalValueTransaction = tmpAccountAmount - finalValueTransaction;
  sprintf(creditCardAmountAccount,"%.2f",finalValueTransaction);

  fclose(fileAccount);
  char writeNewValuesAccount[3072];
  strcpy(writeNewValuesAccount, cardNumberAccount);
  strcat(writeNewValuesAccount, ";");
  strcat(writeNewValuesAccount, passWordNumberAccount);
  strcat(writeNewValuesAccount, ";");
  strcat(writeNewValuesAccount, creditCardAmountAccount);
  strcat(writeNewValuesAccount, ";");
  FILE* fileAccountW = fopen("../accounts/account-card.txt", "w");
  if(fileAccountW == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }
  fputs(writeNewValuesAccount, fileAccount);
  fclose(fileAccountW);

  printf("\n\nTransação no Valor de: R$%s em %d parcelas.\n\n", transValueFinal,numParcelas);
  //fim da transação

  //logarNOarquivodeLogTrans
  logTransaction(cardNumberAccount, transValueFinal);

  return 0;
}

int transactionPix(char* transactionAmount, char* pixChave){
  //validacao(-1) valores não validos
  int tmpTransAmount = atoi(transactionAmount);
  if(tmpTransAmount < 0)
    return -1;

  char pixKeyAccount[1024];
  char pixAmountAccount[1024];

  printf("Valores Da transação: %s\n\n", transactionAmount);
  printf("Chave pix passada: %s\n\n", pixChave);

  //checkaccounts()
  FILE* fileAccount = fopen("../accounts/account-pix.txt", "r");
  if(fileAccount == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }
  char tmpAcountValue[1024];
  fgets(tmpAcountValue, sizeof(tmpAcountValue), fileAccount);
  char valuesAccount[sizeof(tmpAcountValue)];
  strcpy(valuesAccount, strtok(tmpAcountValue, ";"));
  //struct cardInfo account;
  //populando as Variaveis com as informações do Cartao
  for (int i = 0; i < 2; i++)
  {
    if(i == 0) {
      printf("Chave Pix: %s\n\n", valuesAccount);
      strcpy(pixKeyAccount, valuesAccount);
    } else {
      printf("Valor Disponivel na conta: %s\n\n", valuesAccount);
      strcpy(pixAmountAccount, valuesAccount);
      break;
    }
    strcpy(valuesAccount, strtok(NULL, ";"));
  }

  //-2 validacao se a chave pix está acorreta
  if(strcmp(pixChave, pixKeyAccount) != 0)
    return -2;

  //float juros = tmpTransAmount * (numParcelas * 0.01); 
  float finalValueTransaction;
  //char transValueFinal[1024];
  //sprintf(transValueFinal,"%.2f",finalValueTransaction);
  int tmpAccountAmount = atoi(pixAmountAccount);
  finalValueTransaction = tmpAccountAmount - tmpTransAmount;
  sprintf(pixAmountAccount,"%.2f",finalValueTransaction);
  printf("Valor final transação: %.2f\n\n", finalValueTransaction);
  fclose(fileAccount);

  //remotando o arquivo da conta pix
  char writeNewValuesAccount[2048];
  strcpy(writeNewValuesAccount, pixKeyAccount);
  strcat(writeNewValuesAccount, ";");
  strcat(writeNewValuesAccount, pixAmountAccount);
  strcat(writeNewValuesAccount, ";");
  printf("Remontando o arquivo com valores atualizados: %s\n\n", writeNewValuesAccount);

  FILE* fileAccountW = fopen("../accounts/account-pix.txt", "w");
  if(fileAccountW == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }
  fputs(writeNewValuesAccount, fileAccount);
  fclose(fileAccountW);

  printf("\n\nTransação no Valor PIX de: R$%d.\n\n", tmpTransAmount);

  //logTransaction(pixChave, transactionAmount);

  return 0;
}

int logTransaction(char* value1, char* value2){
  FILE * LogTransfile;
  LogTransfile = fopen("../logTransaction/logTransFile.txt", "w");
  char transValue[1024];
  strcpy(transValue, value1);
  strcat(transValue, ";");
  strcat(transValue, value2);
  fputs(transValue, LogTransfile);
  fclose(LogTransfile);
  return 0;
}
