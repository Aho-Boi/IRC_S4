#include "primes.h"

size_t pows(size_t a, int b)
{
  size_t res = 1;
  for(int i = 0; i < b; i++, res *= a);
  return res;
}

int isprime(size_t p)
{
  if ( !(p % 2) )
    return 0;
  for(size_t i = 3; i* i  <= p; i += 2){
    if ( !(p % i) )
      return 0;
  }
  return 1;
}

size_t createrandom(size_t bsize)
{
  int fdurd;
  if ( (fdurd = open("/dev/urandom", O_RDONLY)) == -1 )
    errx(EXIT_FAILURE, "Open fails in funtion 'createrandom'");
  char *random = malloc(bsize);
  if ( read(fdurd, random, bsize) < 0 )
    errx(EXIT_FAILURE, "Read fails in function 'createrandom'");
  close(fdurd);

  size_t res = 0;
  for(size_t i = 0; i != bsize; i++){
    if ( random[i] < 0)
      random[i] *= -1;
    res += random[i] * pows(2, 8*i);
  }
  free(random);
  return res;

  
  
}

size_t createprime(size_t min, size_t bytesize)
{
  size_t r = 0;
  for(; !r || ( min && r < min);r = createrandom(bytesize) ){
    continue;
  } 

    if ( !(r % 2) ) r+=1;
  for(; !(isprime(r)); r += 2 );
  return r;
}

size_t euclide(size_t a, size_t b)
{
  long u = 1, v = 0, u1 = 0, v1 = 1, q, rs, us, vs;
  long r = a;
  long r1 = b;
 
  while ( r1 != 0 ){
    q = r / r1;
    rs = r;
    us = u;
    vs = v;
    r = r1;
    u = u1;
    v = v1;
    r1 = rs - q * r1;
    u1 = us - q * u1;
    v1 = vs - q * v1;
  }
  if ( u >= 0 )
    return u;
  return -1 * u;
}

size_t mod(size_t a, size_t pow, size_t n)
{
  size_t b = 1;
  for(size_t i = 0; i < pow; i++){
    b *= a;
    b %= n;
  }
  return b;
}

/*

int main(int argc, char *argv[])
{
  char *end;
  size_t p = strtol(argv[1], &end, 10);
  if ( isprime(p) )
    printf("That number is prime\n");
  else
    printf("This number is not prime\n");
  return 0*argc;
}

*/
/*
int main(void)
{
  size_t *era = malloc(100000 * sizeof(size_t));
  size_t *mem = era;
  for(size_t i = 2; i != 1000001; i++){
    if ( isprime(i) ){
      printf("%lu is prime\n", i);
      *era = i;
      era++;
    }
  }
  *era = 0;
  size_t j = 0;
  for (; *(mem + j); j++){
    printf(" %lu,", *(mem + j));
  }
  printf("\tAre prime, for a total of %lu primes to 100\n", j);
  free(mem);

  return 0;
}
*/


