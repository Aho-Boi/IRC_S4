#ifndef PRIMES_H
#define PRIMES_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

size_t pows(size_t a, int b);
//Computes a^b

int isprime(size_t p);
//returns 1 if p is prime, 0 if not

size_t createrandom(size_t bsize);
//returns a size_t filled with bsize bytes of randoms from dev/urandom. atm, bsize <= sizeof(size_t) (= 8)

size_t createprime(size_t min, size_t bytesize);
//returns a prime > min, of bytesize bytes

size_t euclide(size_t a, size_t b);
//returns the reverse of a mod b
//Some size issues may happen : given 2 size_t, return long;
//if either a > 2^7 or b > 2^7 

size_t mod(size_t a, size_t pow,  size_t n);
//Returns (a^pow) % n

void save_primes(size_t max);

int fisprime(size_t in);
#endif
