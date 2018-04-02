#include "lnb.h"

lnb *lnb_init( size_t blen )
{
  if( blen == 0 )
    return NULL;

  lnb *res = malloc( sizeof(lnb) );
  if ( res == NULL)
    errx(EXIT_FAILURE, "Error in lnb_init's malloc");
  if ( (res->bytes = calloc(blen, 1)) == NULL )
       errx(EXIT_FAILURE, "Error in lnb_init's calloc");
  res->blen = blen;
  return res;
}


lnb *lutolnb(size_t inp)
{
  
  lnb *res = lnb_init(sizeof(size_t));
  size_t i = 0;
  for(; inp != 1 && i < sizeof(size_t); i++){
    *( res->bytes + i) = inp % 256;
    inp /= 256;
  }
  if ( inp == 1 )
    res->bytes[i] += 1; 
  return res;
}

size_t lnbtolu(lnb *inp)
{
  if(inp->blen > sizeof(size_t)){
    printf("lnb too large for 8 bytes");
    return 0;
  }
  size_t res = 0;
  for(size_t i = 0; i < inp->blen; i++){
    res += inp->bytes[i] * pows(256, i);
  }
  return res;
}

void print_lnb(lnb *inp)
{
  
  for(size_t i = inp->blen-1; i; i--){
    printf("'%u'", inp->bytes[i]);
  }
  printf("'%u'\n", inp->bytes[0]);
}

void growlnb(lnb *inp, size_t addb)
{
  inp->blen += addb;
  if( (inp->bytes = realloc(inp->bytes, inp->blen)) == NULL)
    errx(EXIT_FAILURE, "Realloc fails in growlnb");
  for(size_t i = 0; i < addb; i++ ){
    inp->bytes[inp->blen - addb + i] = 0;
  }
}

void cleanlnb(lnb *inp){
  size_t i = inp->blen - 1;
  for(; (! *(inp->bytes + i)) && i; i--){
    continue;
  }
  if ( (!i) && !(inp->bytes[0])){
    return;
  }
  inp->blen = i + 1;
  if (  (inp->bytes = realloc(inp->bytes, inp->blen)) == NULL)
    errx(EXIT_FAILURE, "Realloc fails in cleanlnb");
}

lnb *lcopy(lnb *inp){
  lnb *res = lnb_init(inp->blen);
  for(size_t i = 0; i < inp->blen; i++){
    res->bytes[i] = inp->bytes[i];
  }
  return res;
}

void lsum(lnb *a, lnb *b)
{
  if(a->blen <= b->blen)
    growlnb(a, b->blen - a->blen + 1);
  size_t ret = 0;
  size_t mem;
  size_t i = 0;
  for(; i < b->blen; i++){
    mem = (a->bytes[i] +  b->bytes[i] + ret);
    a->bytes[i] = mem % 256;

    ret = mem / 256;
  }
  while ( ret ){
    mem = (a->bytes[i] + ret);
    a->bytes[i] = mem % 256;
    ret = mem / 256;
    i++;
  }
}

void ldif(lnb *a, lnb *b){
  cleanlnb(a);
  cleanlnb(b);
  if ( (b->blen > a->blen)  ||
       (b->blen == a->blen && (a->bytes[a->blen - 1] < b->bytes[b->blen - 1])))
    errx(EXIT_FAILURE, "difference problem, substract ends in a negative");
  for(size_t i = 0; i < b->blen; i++){
    if ( a->bytes[i] >= b->bytes[i] ){
      a->bytes[i] -= b->bytes[i];
      continue;
    }
    size_t j = i + 1;
    while( !(a->bytes[j]) ){
      a->bytes[j] = 255;
      j++;
    }
    a->bytes[j] -= 1;
    a->bytes[i] = 256 - b->bytes[i] + a->bytes[i];
  }
}

lnb *lprod(lnb *a, lnb *b){
  lnb *res = lnb_init(a->blen + b->blen);

  int ret = 0;
  size_t mem = 0;
  for(size_t i = 0; i < a->blen; i++){
    for(size_t j = 0; j < b->blen; j++){
      mem = res->bytes[i + j];
      res->bytes[i + j] = (mem + a->bytes[i] * b->bytes[j]) % 256;
      ret = (a->bytes[i] * b->bytes[j] + mem ) / 256;
      res->bytes[i + j + 1] += ret;
    }
  }
  return res;
}

int cmp(lnb *a, lnb *b){
  cleanlnb(a);
  cleanlnb(b);

  if ( a->blen > b->blen )
    return 1;
  if( a->blen < b->blen )
    return 0;
  size_t i = a->blen - 1;
  for(; i < a->blen; i--){
    if ( a->bytes[i] > b->bytes[i] )
      return 1;
    if( a->bytes[i] <= b->bytes[i] )
      return 0;
  }
  return 0;
}


lnb *euc(lnb *a, lnb *b){
  cleanlnb(b);
  cleanlnb(a);
  if ( b->blen <= sizeof(size_t) ){
    size_t sres = 0;
    size_t sb = lnbtolu(b);
    size_t ipow = 1;
    for(size_t i = 0; i < a->blen; i++){
      sres = (sres + (ipow * a->bytes[i] % sb )) % sb; 
      ipow *= (256 % sb);
      ipow %= 256;
    }
    return lutolnb(sres);
  }
  lnb *res = lcopy(a);
  for(; !cmp(b, res);){
    ldif(res, b);
  }
  return res;;
}
