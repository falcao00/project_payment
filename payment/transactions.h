#ifndef TRANSACTIONS_H_INCLUDED
#define TRANSACTIONS_H_INCLUDED

int transactionCreditPs(char* transactionAmount, char* cardNumber, int numParcelas, char* cardPassword);

int transactionAvista(char* transactionAmount, char* cardNumber, char* cardPassword);

int transactionPix(char* transactionAmount, char* pixChave);

int logTransaction(char* cardNumber, char* amountTrans);

int estornoFunction(char* cardNumber, char* cardPassword);

#endif
