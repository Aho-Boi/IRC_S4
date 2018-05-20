#include "primes.h"

#define LIM pows(2, 64) - 1

size_t pows(size_t a, int b)
{
  size_t res = 1;
  for(int i = 0; i < b; i++, res *= a);
  return res;
}

int isprime(size_t p)
{
  if (p == 1)
    return 0;
  if ( !(p % 2) )
    return 0;
  for(size_t i = 3; i* i  <= p; i += 2){
    if ( !(p % i) )
      return 0;
  }
  write(STDOUT_FILENO, "IN", 2);
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
  write(STDOUT_FILENO, "meh", 3);
  for(; !r || ( min && r < min);r = createrandom(bytesize) ){
    continue;
  }
  write(STDOUT_FILENO, "oui", 3);

  if ( !(r % 2) ) r+=1;
  write(STDOUT_FILENO, "BE", 2);
  for(; !(isprime(r)); r += 2 ){
    if ( (r + 2  == LIM) || (r + 1  == LIM))
      return createprime(min, bytesize);
  }
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

/* size_t mod(size_t a, size_t pow, size_t n) */
/* { */
/*   size_t b = 1; */
/*   for(size_t i = 0; i < pow; i++){ */
/*     b *= a; */
/*     b %= n; */
/*   } */
/*   return b; */
/* } */

size_t mod2(size_t a, size_t pow, size_t n){
  size_t res = 1;
  size_t a2 = a;
  for(; pow; pow /= 2){
    if ( pow % 2 )
      res *= a2 % n;
    res %= n;
    printf("%lu\n", res);
    a2 *= a2;
    a2 %= n;
  }
  return res;
}

size_t mod(size_t a, size_t pow, size_t n)
{
  size_t act = a;
  size_t res = 1;
  for(; pow > 0; pow /= 2){
    res *= pows(act, pow % 2 );
    res %= n;
    act = pows(act, 2) % n;
  }
  return res % n;
}


void save_primes(size_t max){
  FILE *f = fopen("primes.save", "w+");
  if ( !f )
    errx(EXIT_FAILURE, "save_primes");
  size_t meh = 2;
  fprintf(f, "%lu\n", meh);
  for(size_t i = 3; i <= max; i++){
    if(!(i%100000))
      printf("%lu\n", i);
    if(isprime(i)){
      fprintf(f, "%lu\n", i);
    }
  }
  fclose(f);
}

int fisprime(size_t in){
  FILE *f = fopen("primes.save", "r");
  if ( !f )
    errx(EXIT_FAILURE, "fisprime");
  size_t *p = malloc(sizeof(size_t));

  for(; (*p) * (*p) < in;){
    fscanf(f,"%lu\n", p);
    if (!(*p) ||  !(in % (*p)) ){
      fclose(f);
      return 0;
    }
  }
  fclose(f);
  return 1;
}
