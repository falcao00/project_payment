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
int transactionCreditP(int transactionAmount, int parcelas, char carNumber, char cardPassword){
  //int juros = parcelas * 0.5;
  float jurosAplicados, valorFinalTransaction;
  if(transactionAmount <= 0 || parcelas <= 0 || 
      carNumber != *falcon.idCardNumber || cardPassword != *falcon.password)
    return -1;

  if(parcelas > 5)
    return -2;

  jurosAplicados = (0.5) * parcelas;
  printf("Juros: %.2f\n", jurosAplicados);
  valorFinalTransaction = transactionAmount + jurosAplicados;
  printf("Valor Final: %.2f\n", valorFinalTransaction);
  *falcon.amount = *falcon.amount - valorFinalTransaction;
  printf("Valor final em conta: %d\n", *falcon.amount);

  return 0;
}

int transactionPix(int transactionAmount, char pixChave){
  
  if(transactionAmount <= 0 /*|| pixChave == NULL*/)
    return -1;

  *falcon.amount = *falcon.amount - transactionAmount;
  printf("Valor final em conta: %d\n", *falcon.amount);
  return 0;
}
