
#ifndef RSA_H_
#define RSA_H_
#include "primes.h"
#include "lnb.h"
void create_keys(size_t *res, size_t maxd);
//Fills res with n, e, d in this order
//( n, e ) is the public key to give to others
//( d ) is the private ekey, to keep in order to decrypt

size_t encrypt(size_t M, size_t n, size_t e);
//Given M and the public key, encrpyts it

size_t decrpyt(size_t C, size_t d, size_t n);
//Given the encrypted C, the private key d and n through public key, decrpyts it

int test_keys(size_t *keys);
//Returns 1 if I did it good
//0 if i'm bad

#endif
