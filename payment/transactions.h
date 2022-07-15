#ifndef TRANSACTIONS_H_INCLUDED
#define TRANSACTIONS_H_INCLUDED

int transactionCreditP(int transactionAmount, int parcelas, char carNumber, char cardPassword);

int transactionPix(int transactionAmount, char pixChave);

int transactionCreditA(void);

int transactionEstorno(void);

#endif
