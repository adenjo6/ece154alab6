/*
Aden Jo, Leo Zhu
ECE 154A - Fall 2024
Lab 2 - Mystery Caches
Due: 12/5/2024

Mystery Cache Geometries:
mystery0:
    block size = 
    cache size = 
    associativity = 
mystery1:
    block size = 
    cache size = 
    associativity = 
mystery2:
    block size = 
    cache size = 
    associativity = 
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
    int num_blocks = 1;

    while (TRUE) {
        flush_cache();

        for (int i = 0; i < num_blocks; i++) {
            access_cache(i * block_size);
        }

        if (!access_cache(0)) {
            return (num_blocks - 1) * block_size;
        }

        num_blocks++;
    }

    return -1; 
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int cache_size) {
    int assoc = 1;
    addr_t test_addr = 0;
    int block_size = get_block_size();

    while (TRUE) {
        flush_cache();

        for (int i = 0; i < assoc; i++) {
            access_cache(test_addr + i * cache_size);
        }

        if (!access_cache(test_addr)) {
            return assoc - 1;
        }

        assoc++;

        if (assoc > 64) {
            break; 
        }
    }

    return -1; // Should not reach here
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
    flush_cache();
    addr_t base_addr = 0;
    access_cache(base_addr);
    int block_size = 1;

    while (access_cache(base_addr + block_size)) {
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
