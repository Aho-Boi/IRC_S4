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

int main(int argc, char **argv)
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

  if ( argc != 2 )
    errx(EXIT_FAILURE, "Needs an argument");
  
  size_t i;

  sscanf(*(argv + 1), "%lu", &i);

  
  lnb *r = lnb_init(i);
  lrand(r);

  if( i == 1 )
    i++;
  
  lnb *su = lnb_init(i - 1);
  lrand(su);
  for(; cmp(su, r) ;){
    lrand(su);
  }
 
  cleanlnb(r);
  cleanlnb(su);
  lnb *cp = lcopy(r);
  print_lnb(r);
  printf("  +  \n");
  print_lnb(su);
  printf("  =\n");
  lsum(r, su);
  print_lnb(r);

  printf("\n");
  if ( i < 9 )
    printf("\n\nWhich is : %lu + %lu = %lu\n\n"
	   , lnbtolu(cp), lnbtolu(su), lnbtolu(r));
  lfree(cp);
  printf("\n");
  cleanlnb(r);
  cleanlnb(su);
  lnb *cp2 = lcopy(r);
  print_lnb(r);
  printf("  -  \n");
  print_lnb(su);
  printf("  =\n");
  ldif(r, su);
  print_lnb(r);
  
  if ( i < 9 )
    printf("\n\nWhich is : %lu - %lu = %lu\n\n"
	   , lnbtolu(cp2), lnbtolu(su), lnbtolu(r));
  lfree(cp2);

  printf("\n\n");
  cleanlnb(r);
  cleanlnb(su);  
  print_lnb(r);
  printf("  %%  \n");
  print_lnb(su);
  printf("  =\n");
  lnb *di = euc(r, su);
  cleanlnb(di);
  print_lnb(di);

  if ( i < 9 )
    printf("\n\nWhich is : %lu %% %lu = %lu\n\n"
	   , lnbtolu(r), lnbtolu(su), lnbtolu(di));
  

  printf("\n\n");
  
  print_lnb(r);
  printf("  *  \n");
  print_lnb(su);
  printf("  =\n");
  lnb * pro = lprod(r, su);
  cleanlnb(pro);
  print_lnb(pro);

  if ( i < 9 && pro->blen < 9)
    printf("\n\nWhich is : %lu * %lu = %lu\n\n"
	   , lnbtolu(r), lnbtolu(su), lnbtolu(pro));

  
  lfree(pro);
  lfree(r);
  lfree(su);
  lfree(di);
  
  return 1;
}
