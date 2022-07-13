#include <stdio.h>
#include <stdbool.h>
#include "accountFunctions.h"

int main(void){
  _Bool aplicationMain = true;
  while(aplicationMain){
    printf("Bem vindo Usuário, Qual operação deseja executar?\n\n1 - Criar uma conta\n\n2 - Acessar uma conta\n\n3 - Fazer uma Transação\n\n");
    int functionValue = 0;
    scanf("%d", &functionValue);
    switch(functionValue){
      case 1:
        printf("Função de Criação de Conta\n");
        accountCreation();
        break;
      case 2:
        printf("Função de Acessar uma conta existente\n");
        break;
      case 3:
        printf("Função Transacional\n");
        break;
      default:
        aplicationMain = false;
        break;
    };
  };

  return 0;
}
