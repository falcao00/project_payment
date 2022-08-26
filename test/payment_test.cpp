#include "gtest/gtest.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "../payment/transactions.h"
#include "../payment/transactions.c"

TEST(paymentTest, pagamentoCreditoParceladoHappyPath) {
    int payresult = 0;

    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "1234-5678-9123-4567";
    char cardPassword[1024] = "159753";
    int  parcelas = 2;

    //result = transactionCreditP(&transactionAmount, &cardNumber, numParcelas, &password);
    int result = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);
    //printf("HERE POS TESTE FUNCTION \n");

    EXPECT_EQ (0,  result);
}

TEST(paymentTest, pagamentoCreditoAmountInvalido) {
    int payresult = 0;

    //setar as variaveis
    char amount[1024] = "-100"; //Valor Negativo
    char cardNumber[1024] = "1234-5678-9123-4567";
    char cardPassword[1024] = "159753";
    int  parcelas = 2;

    //result = transactionCreditP(&transactionAmount, &cardNumber, numParcelas, &password);
    int result = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);
    //printf("HERE POS TESTE FUNCTION \n");

    EXPECT_EQ (-1,  result);
}

TEST(paymentTest, pagamentoCreditoParcelasInvalidas) {
    int payresult = 0;

    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "1234-5678-9123-4567";
    char cardPassword[1024] = "159753";
    int  parcelas = -2;

    int result = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);

    EXPECT_EQ (-1,  result);
}

TEST(paymentTest, pagamentoCreditoParcelasInvalidaMaisde10) {
    int payresult = 0;

    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "1234-5678-9123-4567";
    char cardPassword[1024] = "159753";
    int  parcelas = 20;

    int result = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);

    EXPECT_EQ (-1,  result);
}

TEST(paymentTest, pagamentoCreditoCardInvalido) {
    int payresult = 0;

    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "0";
    char cardPassword[1024] = "159753";
    int  parcelas = 2;

    int result = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);

    EXPECT_EQ (-2,  result);
}

TEST(paymentTest, pagamentoCreditoPasswordInvalid) {
    int payresult = 0;

    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "1234-5678-9123-4567";
    char cardPassword[1024] = "0";
    int  parcelas = 2;

    int result = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);

    EXPECT_EQ (-2,  result);
}

TEST(paymentTest, pagamentoCreditoNoFile) {
    int payresult = 0;

    remove("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-card.txt");

    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "1234-5678-9123-4567";
    char cardPassword[1024] = "159753";
    int  parcelas = 2;

    int result = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);

    FILE* Filetemp = fopen("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-card.txt", "w");
    fputs("1234-5678-9123-4567;159753;395.00;", Filetemp);
    fclose(Filetemp);

    EXPECT_EQ (-3,  result);
}

TEST(paymentTest, pagamentoPixHappyPath) {
    int payresult = 0;
    
    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "idd_jfalcao@email.com";

    //result = transactionCreditP(&transactionAmount, &cardNumber, numParcelas, &password);
    int result = transactionPix(amount, cardNumber);

    EXPECT_EQ (0,  result);
}

TEST(paymentTest, pagamentoPixAmountInvalido) {
    int payresult = 0;
    
    //setar as variaveis
    char amount[1024] = "-100";
    char cardNumber[1024] = "idd_jfalcao@email.com";

    //result = transactionCreditP(&transactionAmount, &cardNumber, numParcelas, &password);
    int result = transactionPix(amount, cardNumber);

    EXPECT_EQ (-1, result);
}

TEST(paymentTest, pagamentoPixEmailInvalido) {
    int payresult = 0;
    
    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "@email.com";

    //result = transactionCreditP(&transactionAmount, &cardNumber, numParcelas, &password);
    int result = transactionPix(amount, cardNumber);

    EXPECT_EQ (-2, result);
}

TEST(paymentTest, pagamentoPixNoFile) {
    int payresult = 0;

    remove("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-pix.txt");
    
    //setar as variaveis
    char amount[1024] = "100";
    char cardNumber[1024] = "@email.com";

    //result = transactionCreditP(&transactionAmount, &cardNumber, numParcelas, &password);
    int result = transactionPix(amount, cardNumber);

    FILE* Filetemp = fopen("/home/falcao/estudos_c/projeto_c/project_payment/accounts/account-pix.txt", "w");
    fputs("idd_jfalcao@email.com;1482.00;", Filetemp);
    fclose(Filetemp);

    EXPECT_EQ (-3, result);
}

//não testado ainda
TEST(paymentTest, logTransactionTestHappyPath) {
    int payresult = 0;

    char amount[1024] = "100";
    char cardNumber[1024] = "1234-5678-9123-4567";
    char cardPassword[1024] = "159753";
    int  parcelas = 2;

    int result1 = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);

    EXPECT_EQ (0, result1);

    FILE* Filetemp = fopen("/home/falcao/estudos_c/projeto_c/project_payment/logTransaction/logTransFile.txt", "r");
    char tempFileString[1024];
    fgets(tempFileString, sizeof(tempFileString), Filetemp);
    fclose(Filetemp);

    EXPECT_STREQ ("1234-5678-9123-4567;102.00", tempFileString);
    //logTransaction(cardNumber, amount);
    
}

//não testado ainda
/*TEST(paymentTest, logTransactionTestNoFile) {
    int payresult = 0;

    char amount[1024] = "100";
    char cardNumber[1024] = "1234-5678-9123-4567";
    char cardPassword[1024] = "159753";
    int  parcelas = 2;

    int result1 = transactionCreditPs(amount, cardNumber, parcelas, cardPassword);

    EXPECT_EQ (0, result1);

    remove("/home/falcao/estudos_c/projeto_c/project_payment/logTransaction/logTransFile.txt");

    int result = logTransaction(cardNumber, amount);
    EXPECT_EQ (-3, result);

    FILE* Filetemp = fopen("/home/falcao/estudos_c/projeto_c/project_payment/logTransaction/logTransFile.txt", "r");
    fclose(Filetemp);
   
}*/