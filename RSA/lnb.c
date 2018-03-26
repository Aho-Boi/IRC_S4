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
  for(; ! *(inp->bytes + i); i--){
    continue;
  }
  inp->blen = i + 1;
  if (  (inp->bytes = realloc(inp->bytes, inp->blen)) == NULL)
    errx(EXIT_FAILURE, "Realloc fails in cleanlnb");
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
    /*
    aret = ret;
    ret = 0;
    if ( a->bytes[i] + b->bytes[i] + aret > 255 )
      ret = 1;
    */   
  }
  while ( ret ){
    mem = (a->bytes[i] + ret);
    a->bytes[i] = mem % 256;
    ret = mem / 256;
    i++;
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
  else if( a->blen < b->blen )
    return 0;
  size_t i = a->blen - 1;
  for(; i > 0; i--){
    if ( a->bytes[i] > b->bytes[i] )
      return 1;
    else if( a->bytes[i] < b->bytes[i] )
      return 0;
  }
  return 0;
}

/*
lnb *euc(lnb *a, lnb *b){
  size_t max = a->blen;
  if ( b->blen > max )
    max = b->blen;
  lnb *res = lnb_init(max);

  for(size_t i = 0; i < max; )
}




*/
