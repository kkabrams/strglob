#include"strglob.h"

int **results = NULL;

void cartprod_results(int *arr) {
  static size_t anindex = 0;

  results[anindex] = arr;

  anindex++;

  return;
}

void cartesian_product(int **sets, int *setLengths, int *currentSet, const int numSets, const int times) {
  int *restrict r = NULL;
  register int i = 0;

  if(!results) {
    register size_t total_length = 1;
    register int *slp = setLengths;

    for(;*slp && *slp > 0;slp++)
      total_length *= *slp; 

#ifdef DEBUG_STRGLOB
  fprintf(stderr, "total_length (product of multiplied set lengths): %lu \t *slp (set length pointer): %d\n", total_length, *slp);
#endif

    results = malloc((1 + total_length) * (sizeof*results));

    if(!results)
      exit_verbose("malloc", __FILE__, __LINE__);

    results[total_length] = 0;
  }

#ifdef DEBUG_STRGLOB
  fprintf(stderr, "times: %d numSets (number of given sets plus one): %d\n", times, numSets);
#endif

	if(times < numSets) {
    register int j = 0;

		for(;j < setLengths[times];j++) {
#ifdef DEBUG_STRGLOB
  fprintf(stderr, "j: %d times: %d numSets: %d sets[times][j]: %d setLengths[times]: %d\n", j, times, numSets, sets[times][j], setLengths[times]);
#endif

			currentSet[times] = sets[times][j];

      cartesian_product(sets, setLengths, currentSet, numSets, times + 1);
    }
  }

  if((times + 1) != numSets) {
#ifdef DEBUG_STRGLOB
  fputs("RETURNING", stderr);
#endif
    return;
  }

  r = malloc((1 + times) * sizeof *r);

  if(!r)
    exit_verbose("malloc", __FILE__, __LINE__);

  r[times] = -1;

  for(i = 0;i < times;i++) 
    r[i] = currentSet[i];

  cartprod_results(r);

  return;
}