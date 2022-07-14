#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED

struct cardInfo{
  char idCardNumber[1000];
  char password[20];
  int  amount[5];
};

int accountCreation(void);

#endif
