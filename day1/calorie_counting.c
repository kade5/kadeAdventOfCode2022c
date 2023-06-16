#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

int calorie_counter(char *filename) {
  int max_calories = 0;
  int current_calories = 0;
  char line[128];
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("File not found\n");
    return 0;
  }

  while (fgets(line, 128, fp)) {
    if (line[0] == '\n') {
      if (current_calories > max_calories) {
        max_calories = current_calories;
      }
      current_calories = 0;
    } else {
      if (!is_number(line)) {
        printf("Not a valid file\n");
        return 0;
      }

      current_calories += strtol(line, NULL, 10);
    }
  }
  if (current_calories > max_calories) {
    return current_calories;
  }
  return max_calories;
}

int main() {
  printf("%d\n", calorie_counter("elf.txt"));
  return EXIT_SUCCESS;
}
