#ifndef LNB_H_
#define LNB_H_

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "primes.h"


typedef struct large_number{
  unsigned char *bytes;
  size_t blen;  
}lnb;

lnb *lnb_init(size_t blen);


lnb *lutolnb(size_t inp);

size_t lnbtolu(lnb *inp);

void print_lnb(lnb *inp);

void growlnb(lnb *inp, size_t addb);

void lsum(lnb *a, lnb *b);

lnb *lprod(lnb *a, lnb *b);

#endif
