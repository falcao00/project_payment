#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED

struct cardInfo{
  char idCardNumber[1024];
  char* password[1024];
  char*  amount[1024];
};

int accountCreation(void);

#endif
