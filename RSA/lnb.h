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
//Initializes a LNB, of blen bytes, each of them equal to 0

lnb *lutolnb(size_t inp);
//Converts a size_t to a lnb, keeping its value

size_t lnbtolu(lnb *inp);
//Converts a lnb to a size_t, make sure that the lnb value is strictly inferior to 2^64

void print_lnb(lnb *inp);
//Prints the lnb byte per byte separated by ' '

void growlnb(lnb *inp, size_t addb);
//Resizes the lnb to addb bytes

void cleanlnb(lnb *inp);
//Removes the useless '0' bytes before the highest power of 256 : '0' '0' '1' '123' becomes '1' '123' which is equal to 256 + 123 = 379

lnb *lcopy(lnb *inp);
//Copies inp

void lsum(lnb *a, lnb *b);
//Computes a += b

void ldif(lnb *a, lnb *b);
//Computes a -= b; Errors if b > a

lnb *lprod(lnb *a, lnb *b);
//Computes the product between 2 lnb and stores it in a new lnb

int cmp(lnb *a, lnb *b);
//Returns 1 if a > b, 0 if not
//Uses cleanlnb on both a and b

lnb *euc(lnb *a, lnb *b);
//Computes a%b

void lrand(lnb *inp);
//Fills inp with randoms from /dev/urandom
#endif
