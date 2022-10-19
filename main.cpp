/******************************************************************************
 * main.c
 *
 * Parallel construction of succinct trees
 * For more information: http://www.inf.udec.cl/~josefuentes/sea2015/
 *
 ******************************************************************************
 * Copyright (C) 2015 José Fuentes Sepúlveda <jfuentess@udec.cl>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "succinct_tree.cpp"
#include "util.h"

int main(int argc, char** argv) {

  struct timespec stime, etime;
  double time;

  if(argc < 2) {
    fprintf(stderr, "Usage: %s <input parentheses sequence>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  long n;

  BIT_ARRAY *B = parentheses_to_bits(argv[1], &n);

#ifdef MALLOC_COUNT
  size_t s_total_memory = malloc_count_total();
  size_t s_current_memory = malloc_count_current();
  malloc_reset_peak();
#else
  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID , &stime)) {
    fprintf(stderr, "clock_gettime failed");
    exit(-1);
  }
#endif
  
  rmMt *st = st_create(B, n);
  int i=0;
  for(i=0;i<n;i++){
    int32_t test_match = match(st,i);
    int32_t test_naive = match_naive(st,i);
    if(test_match != test_naive){
      printf("%d,%d,%d\n", test_match,test_naive,i);
    }
  } 
  //int test = match(st,2);
#ifdef MALLOC_COUNT
  size_t e_total_memory = malloc_count_total();
  size_t e_current_memory = malloc_count_current();
  printf("%s,%ld,%zu,%zu,%zu,%zu,%zu\n", argv[1], n, s_total_memory,
  e_total_memory, malloc_count_peak(), s_current_memory, e_current_memory);
  // total cantidad de memoria desde el inicio,sin descontar los free
  // current cuanta memoria, se lleva en el momento
  // Unidad bytes
#else
  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID , &etime)) {
    fprintf(stderr, "clock_gettime failed");
    exit(-1);
  }
  
  time = (etime.tv_sec - stime.tv_sec) + (etime.tv_nsec - stime.tv_nsec) / 1000000000.0;
  printf("%s,%lu,%lf\n",  argv[1], n, time);
#endif

  return EXIT_SUCCESS;
}
