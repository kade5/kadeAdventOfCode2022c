#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct SmallestMax {
  int value;
  int index;
  int set;
};

void print_array(int array[], int size) {
  printf("[ ");
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("]\n");
}

int is_number(char *input) {
  int max_loop = 128;
  if (input == NULL || *input == '\0') {
    return false;
  }

  int i = 0;
  while (*input && i < max_loop && *input != '\n') {
    if (!isdigit(*input)) {
      return false;
    }
    i++;
    input++;
  }
  return true;
}

void set_smallest_max(struct SmallestMax *sm, int top_elves[],
                      int num_top_elves) {
  if (sm->set == 1) {
    return;
  }
  for (int i = 0; i < num_top_elves; i++) {
    if (top_elves[i] < sm->value) {
      sm->value = top_elves[i];
      sm->index = i;
    }
  }
  sm->set = 1;
}

void initialize_zeros(int array[], int size) {
  for (int i = 0; i < size; i++) {
    array[i] = 0;
  }
}

int sum_calories(int array[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += array[i];
  }

  return sum;
}

int calorie_counter(char *filename, int num_top_elves) {
  int top_elves[num_top_elves];
  initialize_zeros(top_elves, num_top_elves);
  struct SmallestMax smallest_max;
  smallest_max.value = 0;
  smallest_max.index = 0;
  smallest_max.set = 1;
  int current_calories = 0;
  char line[128];
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("File not found\n");
    return 0;
  }

  while (fgets(line, 128, fp)) {
    if (line[0] == '\n') {
      set_smallest_max(&smallest_max, top_elves, num_top_elves);
      if (current_calories > smallest_max.value) {
        top_elves[smallest_max.index] = current_calories;
        smallest_max.value = current_calories;
        smallest_max.set = 0;
      }
      current_calories = 0;
      print_array(top_elves, num_top_elves);
      printf("%d\n", smallest_max.index);
    } else {
      if (!is_number(line)) {
        printf("Not a valid file\n");
        return 0;
      }

      current_calories += strtol(line, NULL, 10);
    }
  }
  set_smallest_max(&smallest_max, top_elves, num_top_elves);
  if (current_calories > smallest_max.value) {
    top_elves[smallest_max.index] = current_calories;
  }
  return sum_calories(top_elves, num_top_elves);
}

int main() {
  printf("%d\n", calorie_counter("elf.txt", 3));
  return EXIT_SUCCESS;
}
