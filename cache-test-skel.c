#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  int blocks = 0;
  
  flush_cache();
    while(TRUE){        
        flush_cache();
        access_cache(0);
        int i = 1;
        while ( i <= blocks ){
            access_cache(i*block_size);
            i++;
        }
        if ( access_cache(0) ){
            blocks++; 
        }
        else {
            break;
        }        
    }
  return blocks*block_size;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  int assoc = 1;
  flush_cache();
  access_cache(0);
  while (access_cache(0)){
    flush_cache();
    access_cache(0);
    int i = 1;
    while (i<=assoc){
      access_cache(i*size);
      i++;
    }
    assoc++;
  }
  return assoc-1;
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  
  int block_size = 1;
  flush_cache();
  access_cache(0);
  while (access_cache(block_size)) {
      block_size++;
  }

  return block_size;
}

int main(void) {
  int size;
  int assoc;
  int block_size;
  
  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by 
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);
  
  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);


  printf("Cache size: %d bytes\n",size);
  printf("Cache associativity: %d\n",assoc);
  printf("Cache block size: %d bytes\n",block_size);
  
  return EXIT_SUCCESS;
}