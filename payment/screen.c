#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "accountFunctions.h"
#include "transactions.h"
#include "screen.h"

int aplicationStart(){
  _Bool aplicationMain = true;
  _Bool aplicationMain2 = true;
  int parcelas, result;
  char amount[1024];
  char cardNumber[1024];
  char cardPassword[1024];
  char pixKey[1024];
  //char estornoCard[1024];
  while(aplicationMain){
    printf("Menu de Opções\n");
    printf("[1]- Credito Parcelado\n");
    printf("[2]- Credito Avista\n");
    printf("[3]- Pagamento Pix\n");
    printf("[4]- Estorno\n");
    int functionValue = 0;
    scanf("%d", &functionValue);
    switch(functionValue){
      case 1:
        printf("Digitar os valores: \n");
        printf("Numero do Cartão: ");
        scanf("%s", cardNumber);
        printf("\nValor da Transação: ");
        scanf("%s", amount);
        printf("\nNumero de Parcelas: ");
        scanf("%d", &parcelas);
        printf("\nSenha do Cartão: ");
        scanf("%s", cardPassword);
        result = transactionCreditPs(&amount, &cardNumber, parcelas, &cardPassword);
        if (result != 0){
          printf("\n\nERRO: %d\n\n", result);
        }
        break;
      case 2:
        printf("Digitar os valores: \n");
        printf("Numero do Cartão: ");
        scanf("%s", cardNumber);
        printf("\nValor da Transação: ");
        scanf("%s", amount);
        printf("\nSenha do Cartão: ");
        scanf("%s", cardPassword);
        result = transactionAvista(&amount, &cardNumber, &cardPassword);
        if (result != 0){
          printf("\n\nERRO: %d\n\n", result);
        }
        break;
      case 3:
        printf("Digitar os valores: \n");
        printf("Chave Pix: ");
        scanf("%s", pixKey);
        printf("\nValor da Transação: ");
        scanf("%s", amount);
        result = transactionPix(&amount, &pixKey);
        if (result != 0){
          printf("\n\nERRO: %d\n\n", result);
        }
        break;
      case 4:
        printf("Digite as informacoes do cartao para o estorno: \n");
        printf("Numero do Cartão: ");
        scanf("%s", cardNumber);
        printf("\nSenha do Cartão: ");
        scanf("%s", cardPassword);
        result = estornoFunction(cardNumber, cardPassword);
        if (result != 0){
          printf("\n\nERRO: %d\n\n", result);
        }
        break;
      default:
        aplicationMain = false;
        break;
    }
  };
}