#include "generic_vector.h"
#include <stdio.h>
#include <stdlib.h>

ITEM integer_init_copy(ITEM hInt);
void integer_destroy(ITEM *phInt);

int main(int argc, char *argv[]) {
  GENERIC_VECTOR hVector;
  int i;
  int j;

  hVector = generic_vector_init_default(integer_init_copy, integer_destroy);
  if (hVector == NULL) {
    printf("Failed to allocate space for generic vector.\n");
    exit(1);
  }
  for (i = 0; i < 10; i++) {
    if (generic_vector_push_back(hVector, &i) == FAILURE) {
      printf("Failed to push_back %d\n", i);
      exit(1);
    }
    printf("%d/%d\n", generic_vector_get_size(hVector),
           generic_vector_get_capacity(hVector));
  }

  for (j = 0; j < generic_vector_get_size(hVector); j++) {
    printf("%d\n", *((int *)(*generic_vector_at(hVector, j))));
  }

  while (!generic_vector_is_empty(hVector)) {
    printf("popping %d\n",
           *((int *)(*generic_vector_at(
               hVector, generic_vector_get_size(hVector) - 1))));
    generic_vector_pop_back(hVector);
  }

  generic_vector_destroy(&hVector);
  return 0;
}

ITEM integer_init_copy(ITEM hInt) {
  int *pInt;
  int *pArg = (int *)hInt;
  pInt = (int *)malloc(sizeof(int));
  if (pInt != NULL) {
    *pInt = *pArg;
  }
  return pInt;
}

void integer_destroy(ITEM *phInt) {
  int *pInt = (int *)*phInt;
  free(pInt);
  *phInt = NULL;
}
