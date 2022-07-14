#ifndef TRANSACTIONS_H_INCLUDED
#define TRANSACTIONS_H_INCLUDED

int transactionCreditP(int transactionAmount, int parcelas, char carNumber, char cardPassword);

int transactionCreditA(void);

int transactionPix(void);

int transactionEstorno(void);

#endif
