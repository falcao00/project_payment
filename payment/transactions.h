#ifndef TRANSACTIONS_H_INCLUDED
#define TRANSACTIONS_H_INCLUDED

int transactionCreditP(char* transactionAmount, char* cardNumber, int numParcelas, char* cardPassword);

int transactionPix(int transactionAmount, char pixChave);

int logTransaction(char* value1, char* value2);

int transactionCreditA(void);

int transactionEstorno(void);

#endif
