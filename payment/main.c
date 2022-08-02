#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "accountFunctions.h"

int main(void){
  _Bool aplicationMain = true;
  _Bool aplicationMain2 = true;
  int parcelas;
  char amount[1024];
  char cardNumber[1024];
  char cardPassword[1024];
  //strcpy(cardNumber, "1234-5678-9123-4567");
  /*strcpy(amount, "100");
  printf("%s\n", amount);
  printf("%s\n", cardNumber);*/
  while(aplicationMain){
    printf("Menu de Opções\n");
    printf("[1]-Realizar Pagamento\n");
    int functionValue = 0;
    scanf("%d", &functionValue);
    switch(functionValue){
      case 1:
        /*printf("Digitar os valores: \n");
        printf("Numero do Cartão: ");
        scanf("%s", cardNumber);
        printf("\nValor da Transação: ");
        scanf("%s", amount);
        printf("\nNumero de Parcelas: ");
        scanf("%d", &parcelas);
        printf("\nSenha do Cartão: ");
        scanf("%s", cardPassword);
        int result = transactionCreditP(&amount, &cardNumber, parcelas, &cardPassword);*/
        int result = transactionCreditP("100", "123456789", 2, "123456");
        break;
      default:
        aplicationMain = false;
        break;
    }
    /*printf("Menu de Opções\n");
    printf("[1]-Realizar Pagamento\n");
    printf("[2]-Estorno\n");
    printf("[3]-Sair\n\n");
    printf("Selecione a Opção: ");
    int functionValue = 0;
    scanf("%d", &functionValue);
    switch(functionValue){
      case 1:
        int functionValue2;
        while (aplicationMain2){
          printf("[1]-Credito Parcelado\n");
          printf("[2]-Credito Avista\n");
          printf("[3]-PIX\n");
          printf("[4]-Sair\n\n");
          functionValue2 = 0;
          printf("Selecione a Opção: ");
          scanf("%d", &functionValue2);
          switch (functionValue2){
            case 1:
              printf("Iniciando uma compra Credito Parcelada\n");
              printf("Valor da Transação: ");
              scanf("%s", amount);
              printf("Numero de Parcelas: ");
              scanf("%d", &parcelas);
              printf("Numero do Cartão: ");
              scanf("%s", cardnumber);
              printf("Senha do Cartão: ");
              scanf("%s", &cardpass);
              int result = transactionCreditP(amount, parcelas, cardnumber, cardpass);
              if(result != 0)
                printf("Falha na Transação\n");
              break;
            case 2:
              printf("Iniciando uma compra Credito Avista\n");
              break;
            case 3:
              printf("Iniciando uma compra PIX\n");
              printf("Valor da Transação: ");
              scanf("%s", &amount);
              printf("Chave Pix: ");
              scanf("%s", &chavePix);
              int iret =transactionPix(amount, chavePix);
              if(result != 0)
                printf("Falha na Transação\n");
              break;
            case 4:
              aplicationMain2 = false;
              break;
            default:
              aplicationMain2 = false;
              break;
          }
        }
        break;
      default:
        aplicationMain = false;
        break;
    };*/
  };

  return 0;
}
