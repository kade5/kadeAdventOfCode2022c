#include <stdio.h>
#include <stdlib.h>
int mget(char a) {
  int start = 'A';
  int end = 'Z';
  if (a < start || a > end) {
    printf("%c is not a valid character", a);
    exit(EXIT_FAILURE);
  }
  return a - start;
}

void initialize_char_map(int map[]) {
  int size = 26;
  map[mget('A')] = 1;
  map[mget('B')] = 2;
  map[mget('C')] = 3;
  map[mget('X')] = 1;
  map[mget('Y')] = 2;
  map[mget('Z')] = 3;
}

int get_opponent_play_win(int play) { return (((play - 1) + 2) % 3) + 1; }
int get_opponent_play_lose(int play) { return (((play - 1) + 1) % 3) + 1; }

int game_score1(char o, char p, int char_map[]) {
  int o_play = char_map[mget(o)];
  int p_play = char_map[mget(p)];

  if (o_play == p_play) {
    return p_play + 3;
  } else if (o_play == get_opponent_play_win(p_play)) {
    return p_play + 6;
  } else {
    return p_play;
  }
}

int rps_total_score(char *filename, int game_logic(char, char, int[])) {
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("File not found\n");
    exit(EXIT_FAILURE);
  }
  int char_map[26];
  initialize_char_map(char_map);
  int total_score = 0;
  char line[128];

  while (fgets(line, 128, fp)) {
    if (line[3] != '\n' || line[1] != ' ') {
      printf("Current line is not valid \n%s\n", line);
      exit(EXIT_FAILURE);
    }

    total_score += game_logic(line[0], line[2], char_map);
  }
  return total_score;
}

int main() {
  char filename[] = "rps.txt";
  printf("Your total score for part 1 is %d\n",
         rps_total_score(filename, game_score1));
  return EXIT_SUCCESS;
}
