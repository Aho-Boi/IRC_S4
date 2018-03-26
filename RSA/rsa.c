#include "rsa.h"


void create_keys(size_t *res, size_t maxd)
{
  size_t e = 65537;
  size_t p = createprime(1000, 2); //p a prime > 100 000 000 on 4 bytes
  size_t q = createprime(1000, 2); //q a prime > 100 000 000 on 4 bytes
  
  size_t n = p * q;
  size_t ph = (p - 1) * (q - 1);
  size_t d = euclide(e, ph);
  while( (ph % e == 0) || (p == q) || !( p % q ) || !(q % p) || d > maxd){
    p = createprime(1000, 2); //p a prime > 100 000 000 on 4 bytes
    q = createprime(1000, 2); //q a prime > 100 000 000 on 4 bytes
    n = p * q;
    ph = (p - 1) * (q - 1);
    d = euclide(e, ph);
  }

  res[0] = n;
  res[1] = e;
  res[2] = d;
}

size_t encrypt(size_t M, size_t n, size_t e)
{
  return mod(M, e, n);
}

size_t decrypt(size_t C, size_t d, size_t n)
{
  return mod(C, d, n);
}

int test_keys(size_t *keys)
{
  for(size_t i = 0; i < 10; i++){
    size_t enc = encrypt(i, keys[0], keys[1]);
    size_t dec = decrypt(enc, keys[2], keys[0]);
    if(dec != i)
      return 0;
  }
  return 1;
}

int main()
{
  /*  
  size_t *keys = malloc(3 * sizeof(size_t));
  create_keys(keys, 10000000);

  while(!test_keys(keys)){
    create_keys(keys, 10000000);
  }
  printf("The public key is : \n\tn = %lu\n\te = %lu\n\n", keys[0], keys[1]);
  printf("The private key is : \n\td = %lu\n\n", keys[2]);

  char mes[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 abcdefghijklmnopqrstuvwxyz";


  
  size_t len = 0;
  for(; mes[len]; len++);
  int *encrypted = malloc(len * sizeof(int));
  for(size_t i = 0; i < len; i++){
    *(encrypted + i) = encrypt(mes[i], keys[0], keys[1]);
    printf("The letter %c is encrypted into %d\n", mes[i], encrypted[i]);
  }
  
  printf("\n");

  char *decrypted = malloc(len);
  for(size_t i = 0; i < len; i++){
    *(decrypted + i) = decrypt(encrypted[i], keys[2], keys[0]); 
    printf("The letter %c is decrypted into %c\n", mes[i], decrypted[i]);
  }
  

  free(decrypted);
  free(encrypted);
  free(keys);
  */

  /*
  printf("%lu\n", pows(3, 10));
  lnb *test = lutolnb(pows(3,10));
  print_lnb(test);
  printf("\n%lu\n", lnbtolu(test));
  free(test->bytes);
  free(test);
  */
  
  lnb *test = lutolnb(255);
  lnb *pro = lutolnb(2558924);
  lnb *real = lutolnb(255 * 255);
  print_lnb(test);
  print_lnb(pro);
  printf("Is the first one superior to the other one ? %d\n", cmp(test, pro));
  //lsum(test, pro);
  //growlnb(test, 1);
  lnb *res = lprod(test, pro);

  cleanlnb(res);
  cleanlnb(real);
  printf("Here is the result : ");
  print_lnb(res);
  printf("And here is the expected result : ");
  print_lnb(real);

  printf("The real takes %lu bytes and the calculated one takes %lu\n", real->blen, res->blen);
  
  free(test->bytes);
  free(test);
  free(pro->bytes);
  free(pro);
  free(res->bytes);
  free(res);
  free(real->bytes);
  free(real);

  return 0;


}
