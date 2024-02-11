#include <stdio.h>
#include <stdlib.h>

#define COUNT 26

int sum_and_free(int **ptr) {
  // if (ptr == NULL || *ptr == NULL) { SOLUTION
  if (ptr == NULL) { // this version will cause a seg fault
    return 0;
  }

  int curr_val = **ptr;
  // fprintf(stderr, "curr_val: %d\n", curr_val);
  int aggregate = sum_and_free(ptr + 1);

  return curr_val + aggregate;
}

void segfault_example() {
  // make an array of length 26 + 1 of integer pointers
  // each int* points to a value of 3800
  int** nums = (int**)malloc((COUNT + 1) * sizeof(int*));
  for (int i = 0; i < COUNT; i++) {
    nums[i] = (int*)malloc(sizeof(int));
    *nums[i] = 3800;
  }
  nums[COUNT] = NULL;

  // do a useless computation
  int sum = sum_and_free(nums);
  fprintf(stderr, "The average is: %d\n", sum / COUNT);

  // clean up
  for (int i = 0; i < COUNT; i++) {
    if (nums[i] != NULL) {
      free(nums[i]);
    }
  }
  free(nums);
}

