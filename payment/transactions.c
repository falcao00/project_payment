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
  /*printf("Logando no Arquivo logTransaction\n");
  printf("\n\n>>Valor do Amount Inputado: %s<<\n\n", transactionAmount);
  printf("\n\n>>Valor do Amount Inputado: %s<<\n\n", cardNumber);
  printf("\n\n>>Valor do Amount Inputado: %d<<\n\n", numParcelas);
  printf("\n\n>>Valor do Amount Inputado: %s<<\n\n", cardPassword);*/

  //checkaccounts()
  FILE* fileAccount = fopen("../accounts/account-card.txt", "r");
  if(fileAccount == NULL){
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }
  char tmpAcountValue[1024];
  fgets(tmpAcountValue, sizeof(tmpAcountValue), fileAccount);
  printf("\n\n>>>>>>Valores do Arquivo: %s<<<<<<\n\n", tmpAcountValue);
  char valuesAccount[sizeof(tmpAcountValue)];
  strcpy(valuesAccount, strtok(tmpAcountValue, ";"));
  //struct cardInfo account;
  //populando as Variaveis com as informações do Cartao
  for (int i = 0; i < 3; i++)
  {
    if(i == 0) {
      printf("Numero do Cartão: %s\n\n", valuesAccount);
      strcpy(cardNumberAccount, valuesAccount);
    } else if (i == 1) {
      printf("Senha do cartão: %s\n\n", valuesAccount);
      strcpy(passWordNumberAccount, valuesAccount);
    } else {
      printf("Credito Disponivel: %s\n\n", valuesAccount);
      strcpy(creditCardAmountAccount, valuesAccount);
      break;
    }
    strcpy(valuesAccount, strtok(NULL, ";"));
  }

  //validacao(-2) digitar o cartao ou senha errada
  //printf("Comparação das Strings1: %d\n\n", strcmp(cardNumber, cardNumberAccount));
  int comp = strcmp(cardNumber, cardNumberAccount);
  int comp2 = strcmp(cardPassword, passWordNumberAccount);
  //||
  if(strcmp(cardNumber, cardNumberAccount) != 0 || strcmp(cardPassword, passWordNumberAccount) != 0)
    return -2;

  /**
   * Juros vai ser calculado adicionando o valor * 0.2
   */
  float juros = tmpTransAmount * (numParcelas * 0.01); //100 * (2*00,1) = 2
  printf(">>>>Valor do Juros: R$: %.2f<<<<\n\n", juros);
  float finalValueTransaction = tmpTransAmount + juros;
  printf(">>>>Valor Final da Transacao: R$: %.2f<<<<\n\n", finalValueTransaction); //102.00
  char transValueFinal[1024];
  sprintf(transValueFinal,"%.2f",finalValueTransaction);
  printf(">>>>Valor Final da Transacao com juros: R$: %s<<<<\n\n", transValueFinal);
  int tmpAccountAmount = atoi(creditCardAmountAccount);
  finalValueTransaction = tmpAccountAmount - finalValueTransaction;
  printf(">>>>Valor Final da Transacao depois de retirar da conta: R$: %.2f<<<<\n\n", finalValueTransaction);
  sprintf(creditCardAmountAccount,"%.2f",finalValueTransaction);
  printf("Valor String ja atualizado: %s\n\n", creditCardAmountAccount);

  fclose(fileAccount);
  char writeNewValuesAccount[3072];
  strcpy(writeNewValuesAccount, cardNumberAccount);
  strcat(writeNewValuesAccount, ";");
  strcat(writeNewValuesAccount, passWordNumberAccount);
  strcat(writeNewValuesAccount, ";");
  strcat(writeNewValuesAccount, creditCardAmountAccount);
  strcat(writeNewValuesAccount, ";");
  printf("Valor que vai ser colocado no arquvi: %s\n\n", writeNewValuesAccount);
  FILE* fileAccountW = fopen("../accounts/account-card.txt", "w");
  fputs(writeNewValuesAccount, fileAccount);
  fclose(fileAccountW);
  //fim da transação

  //logarNOarquivodeLogTrans
  logTransaction(cardNumberAccount, transValueFinal);



  /*strcat(writeNewValuesAccount, creditCardAmountAccount);
  strcat(writeNewValuesAccount, ";");
  sprintf(writeNewValuesAccount, "%s", cardNumberAccount);
  sprintf(writeNewValuesAccount, ";%s", passWordNumberAccount);*/
  //FILE* fileAccountW = fopen("../accounts/account-card.txt", "w");
  //fputs(writeNewValuesAccount, fileAccount);
  //fclose(fileAccountW);

  //itoa(finalValueTransaction, creditCardAmountAccount, 10);


  //printf("Valor Inteiro do TransAmount: %d\n\n", tmpTransAmount);


  /*printf("Os valores Populados na estrutura\nNumero do Cartão: %s\n\n", cardNumberAccount);
  printf("Os valores Populados na estrutura\nSenha do Cartão: %s\n\n", passWordNumberAccount);
  printf("Os valores Populados na estrutura\nCredito Disponivel: %s\n\n", creditCardAmountAccount);*/

  //DANDO SEGMENTED FAULT TODO(FALCAO 02/08)
  //printf("\n\n>>>>CHEGA AQUI?<<<<\n\n");
  

  //loga a transação no arquivo de estorno
  //logTransaction(cardNumber, transactionAmount);

  return 0;
}

int transactionPix(int transactionAmount, char pixChave){
  
  /*if(transactionAmount <= 0 /*|| pixChave == NULL)
    return -1;

  *falcon.amount = *falcon.amount - transactionAmount;
  printf("Valor final em conta: %d\n", *falcon.amount);*/
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
