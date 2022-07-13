#include <stdio.h>
#include <stdbool.h>

int main(void){
  _Bool aplicationMain = true;
  while(aplicationMain){
    printf("Bem vindo Usuário, Qual operação deseja executar?\n\n1 - Criar uma conta\n\n2 - Acessar uma conta\n\n3 - Fazer uma Transação\n\n");
    printf("4 - Sair\n\n");
    int functionValue = 0;
    scanf("%d", &functionValue);
    switch(functionValue){
    
      case 1:
        printf("Função de Criação de Conta\n");
        break;
      case 2:
        printf("Função de Acessar uma conta existente\n");
        break;
      case 3:
        printf("Função Transacional\n");
        break;
      case 4:
        aplicationMain = false;
        break;
      default:
        printf("Por favor inserir uma opção valida\n");
        break;
    };
  };

  return 0;
}
