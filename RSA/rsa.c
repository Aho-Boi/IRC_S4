#include "rsa.h"


void create_keys(size_t *res)
{
  size_t e = 7;
  size_t p = createprime(100, 1); //p a prime > 100 000 000 on 4 bytes
  size_t q = createprime(100, 1); //q a prime > 100 000 000 on 4 bytes
  
  size_t n = p * q;
  size_t ph = (p - 1) * (q - 1);
  while( (ph % e == 0) || (p == q)){
    p = createprime(1, 1); //p a prime > 100 000 000 on 4 bytes
    q = createprime(1, 1); //q a prime > 100 000 000 on 4 bytes
    n = p * q;
    ph = (p - 1) * (q - 1);
  }
  printf("p = %lu\nq = %lu\n", p, q);
  size_t d = euclide(e, ph);

  res[0] = n;
  res[1] = e;
  res[2] = d;
}

size_t encrypt(size_t M, size_t n, size_t e)
{
  return pows(M, e) % n;
}

size_t decrypt(size_t C, size_t d, size_t n)
{
  return mod(C, d, n);
}

int main()
{

  
  size_t *keys = malloc(3 * sizeof(size_t));
  //create_keys(keys);
  keys[0] = 5141;
  keys[1] = 7;
  keys[2] = 4279;
  for(size_t i = 0; i < 5000; i++){
    size_t enc = encrypt(i, keys[0], keys[1]);
    size_t dec = decrypt(enc, keys[2], keys[0]);
    printf("The public key is : \n\tn = %lu\n\te = %lu\n\n", keys[0], keys[1]);
    printf("The private key is : \n\td = %lu\n\n", keys[2]);
    printf("Using the public key, %lu is encprypted into %lu\n", i, enc);
    printf("It decrpyts into %lu\n", dec);
    if(dec != i)
      break;
  }
  free(keys);

  
  return 0;
}
