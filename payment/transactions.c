#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "transactions.h"
#include "accountFunctions.h"

extern struct cardInfo falcon;
extern struct cardInfo helena;

/***
 * Compra Credito Parcelada
 * Com um Juros de 0.5 * Numero de Parcelas 
 * 
*/
int transactionCreditPs(char* transactionAmount, char* cardNumber, int numParcelas, char* cardPassword){
  //validacao(-1) valores não validos
  float tmpTransAmount = atof(transactionAmount);
  if(tmpTransAmount < 0 || numParcelas <= 1 || numParcelas > 18)
    return -1;
  
  char cardNumberAccount[1024];
  char passWordNumberAccount[1024];
  char creditCardAmountAccount[1024];

  //checkaccounts()
  FILE* fileAccount = fopen("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-card.txt", "r");
  if(fileAccount == NULL){
    //printf("\nErro ao abrir o arquivo\n");
    return -3;
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
  FILE* fileAccountW = fopen("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-card.txt", "w");
  if(fileAccountW == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -3;
  }
  fputs(writeNewValuesAccount, fileAccount);
  fclose(fileAccountW);

  //printf("\n\nTransação no Valor de: R$%s em %d parcelas.\n\n", transValueFinal,numParcelas);
  //fim da transação

  //logarNOarquivodeLogTrans
  logTransaction(cardNumberAccount, transValueFinal);

  return 0;
}

int transactionPix(char* transactionAmount, char* pixChave){
  //validacao(-1) valores não validos
  float tmpTransAmount = atof(transactionAmount);
  if(tmpTransAmount <= 0)
    return -1;

  char pixKeyAccount[1024];
  char pixAmountAccount[1024];

  //checkaccounts()
  FILE* fileAccount = fopen("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-pix.txt", "r");
  if(fileAccount == NULL){
    //printf("Erro ao abrir o arquivo\n");
    return -3;
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
      strcpy(pixKeyAccount, valuesAccount);
    } else {
      strcpy(pixAmountAccount, valuesAccount);
      break;
    }
    strcpy(valuesAccount, strtok(NULL, ";"));
  }

  //-2 validacao se a chave pix está acorreta
  if(strcmp(pixChave, pixKeyAccount) != 0){
    //printf("Credencial Pix incorreta\n");    
    return -2;
  }

  //float juros = tmpTransAmount * (numParcelas * 0.01); 
  float finalValueTransaction;
  //char transValueFinal[1024];
  //sprintf(transValueFinal,"%.2f",finalValueTransaction);
  float tmpAccountAmount = atof(pixAmountAccount);
  finalValueTransaction = tmpAccountAmount - tmpTransAmount;
  sprintf(pixAmountAccount,"%.2f",finalValueTransaction);
  fclose(fileAccount);

  //remotando o arquivo da conta pix
  char writeNewValuesAccount[2048];
  strcpy(writeNewValuesAccount, pixKeyAccount);
  strcat(writeNewValuesAccount, ";");
  strcat(writeNewValuesAccount, pixAmountAccount);
  strcat(writeNewValuesAccount, ";");

  FILE* fileAccountW = fopen("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-pix.txt", "w");
  if(fileAccountW == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -3;
  }
  fputs(writeNewValuesAccount, fileAccount);
  fclose(fileAccountW);

  //printf("\n\nTransação no Valor PIX de: R$%d.\n\n", tmpTransAmount);

  int endTransaction = logTransaction(pixChave, transactionAmount);
  if (endTransaction != 0){
    printf("Erro ao gerar o log de transação");
    return -1;
  }

  return 0;
}

int logTransaction(char* cardNumber, char* amountTrans){
  FILE * LogTransfile;
  LogTransfile = fopen("/home/falcao/estudos_c/projeto_c/project_payment/logTransaction/logTransFile.txt", "w");
  if(LogTransfile == NULL){
    //printf("Erro ao abrir o arquivo\n");
    printf("HERE ENTRANDNO NO IF");
    return -3;
  }
  char transValue[1024];
  strcpy(transValue, cardNumber);
  strcat(transValue, ";");
  strcat(transValue, amountTrans);
  fputs(transValue, LogTransfile);
  fclose(LogTransfile);
  return 0;
}

int estornoFunction(char* cardNumber, char* cardPassword){

  char logCardAccount[1024];
  char logAmount[1024];

  FILE* fileAccount = fopen("../logTransaction/logTransFile.txt", "r");
  if(fileAccount == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }
  char tmpAcountValue[1024];
  fgets(tmpAcountValue, sizeof(tmpAcountValue), fileAccount);
  char valuesAccount[sizeof(tmpAcountValue)];

  //confere se existe um estorno, caso não exista quebra
  if(strcmp(tmpAcountValue, "") == 0){
    printf("~ Não existe transação para ser estornada ~\n\n");
    return -3;
  }
  
  //char valuesAccount[sizeof(tmpAcountValue)];
  strcpy(valuesAccount, strtok(tmpAcountValue, ";"));

  //popular variaveis com os valores do arquivo de log
  for (int i = 0; i < 2; i++)
  {
    if(i == 0) {
      strcpy(logCardAccount, valuesAccount);
    } else {
      strcpy(logAmount, valuesAccount);
      break;
    }
    strcpy(valuesAccount, strtok(NULL, ";"));
  }
  fclose(fileAccount);

  //abrindo o arquivo do account-card
  FILE * fileAccountcard = fopen("../accounts/account-card.txt", "r");
  if(fileAccountcard == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }
  char valuesAccount2[1024];
  char cardAccount[1024];
  char cardPassw[1024];
  char cardAmount[1024];
  char tmpAcountValue2[1024];
  fgets(tmpAcountValue2, sizeof(tmpAcountValue2), fileAccount);
  //char valuesAccount2[sizeof(tmpAcountValue2)];
  strcpy(valuesAccount2, strtok(tmpAcountValue2, ";"));
  //struct cardInfo account;
  //populando as Variaveis com as informações do Cartao
  for (int i = 0; i < 3; i++)
  {
    if(i == 0) {
      strcpy(cardAccount, valuesAccount2);
    } else if (i == 1) {
      strcpy(cardPassw, valuesAccount2);
    } else {
      strcpy(cardAmount, valuesAccount2);
      break;
    }
    strcpy(valuesAccount2, strtok(NULL, ";"));
  }

  if(strcmp(cardAccount, cardNumber) != 0 || strcmp(cardPassw, cardPassword) != 0){
    printf("Numero do cartão ou senha errados\n\n");
    return -2;
  }

  fclose(fileAccountcard);

  float estornoAmount = atof(logAmount);
  float estornoCardAmount = atof(cardAmount);
  float valorEstornadoFinal = estornoAmount + estornoCardAmount;

  char convertionFinal[1024];
  sprintf(convertionFinal,"%.2f",valorEstornadoFinal);

  //montarInfoCardAccount
  FILE * fileFinalAccount = fopen("../accounts/account-card.txt", "w");
  char finalStringAccount[2048];
  strcpy(finalStringAccount, cardAccount);
  strcat(finalStringAccount, ";");
  strcat(finalStringAccount, cardPassword);
  strcat(finalStringAccount, ";");
  strcat(finalStringAccount, convertionFinal);
  strcat(finalStringAccount, ";");
  fputs(finalStringAccount, fileFinalAccount);
  fclose(fileFinalAccount);

  //FILE * fileLogFinal = fopen()
  FILE* fileLogFinal = fopen("../logTransaction/logTransFile.txt", "w");
  char ResetLog[1024] = "";
  fputs(ResetLog, fileLogFinal);
  fclose(fileLogFinal);

  memset(valuesAccount, 0, sizeof(valuesAccount));
  memset(valuesAccount2, 0, sizeof(valuesAccount2));
  memset(tmpAcountValue, 0, sizeof(tmpAcountValue));
  memset(tmpAcountValue2, 0, sizeof(tmpAcountValue2));

  return 0;
}

int transactionAvista(char* transactionAmount, char* cardNumber, char* cardPassword){

  float tmpTransAmount = atof(transactionAmount);
  if(tmpTransAmount < 0)
    return -1;

  char cardNumberAccount[1024];
  char passWordNumberAccount[1024];
  char creditCardAmountAccount[1024];

  FILE* fileAccount = fopen("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-card.txt", "r");
  if(fileAccount == NULL){
    //printf("\nErro ao abrir o arquivo\n");
    return -3;
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

  int comp = strcmp(cardNumber, cardNumberAccount);
  int comp2 = strcmp(cardPassword, passWordNumberAccount);
  if(strcmp(cardNumber, cardNumberAccount) != 0 || strcmp(cardPassword, passWordNumberAccount) != 0)
    return -2;

  /*float juros = tmpTransAmount * (numParcelas * 0.01); 
  float finalValueTransaction = tmpTransAmount;
  char transValueFinal[1024];
  sprintf(transValueFinal,"%.2f",finalValueTransaction);
  int tmpAccountAmount = atoi(creditCardAmountAccount);
  finalValueTransaction = tmpAccountAmount - finalValueTransaction;
  sprintf(creditCardAmountAccount,"%.2f",finalValueTransaction);*/

  float finalValueTransaction = tmpTransAmount;
  char transValueFinal[1024];
  sprintf(transValueFinal,"%.2f",finalValueTransaction);
  float tmpAccountAmount = atof(creditCardAmountAccount);
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

  FILE* fileAccountW = fopen("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-card.txt", "w");
  if(fileAccountW == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -3;
  }
  fputs(writeNewValuesAccount, fileAccount);
  fclose(fileAccountW);

  logTransaction(cardNumberAccount, transValueFinal);

  return 0;
}
