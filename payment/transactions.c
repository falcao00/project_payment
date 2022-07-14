#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "transactions.h"
#include "accountFunctions.h"

extern struct cardInfo falcon;

int transactionCreditP(int transactionAmount, int parcelas, char carNumber, char cardPassword){
  int juros = parcelas * 0.5;
  if(transactionAmount <= 0 || parcelas <= 0 || 
      carNumber != *falcon.idCardNumber || cardPassword != *falcon.password)
    return -1;
  
  
  printf("Amount in Falcon: %d\n", *falcon.amount);

  return 0;
}
