#include "stdlib.h"
#include "stdio.h"
#include <string.h>

#define MAX_SIZE 10

typedef struct player {
  char name[20];
  char surname[20];
  float height;
  float weight;
  int wins;
  int matchCount;
} player;

float playerScore(player *player);
void addPlayer(player players[MAX_SIZE], int *size, player newPlayer);
void printPlayer(player *player);
void printArray(player players[MAX_SIZE], int size);
void removePlayer(player players[MAX_SIZE], int *size, int index);
player *highestScore(player players[MAX_SIZE], int size);
typedef int (*cmpfunc)(player*, player*);
void sort(player players[MAX_SIZE], int size, cmpfunc cmp);
int scoreCmp(player *p1, player *p2);
int surnameNameCmp(player *p1, player *p2);
void sortByScore(player players[MAX_SIZE], int size);
void sortAlphabetically(player players[MAX_SIZE], int size);
player *findPlayer(player players[MAX_SIZE], int size, char name[20], char surname[20]);

int main(int argc, char *argv[])
{
  printf("Hello World!\n");

  return EXIT_SUCCESS;
}

float playerScore(player *player) {
  if (player->matchCount == 0) {
    return 0;
  }
  return (float) player->wins / (float) player->matchCount;
}

void addPlayer(player players[MAX_SIZE], int *size, player newPlayer) {
  if (*size == MAX_SIZE) {
    printf("Array is full!");
    return;
  }
  players[*size] = newPlayer;
  *size += 1;
}

void printPlayer(player *player) {
  printf("%s %s, %fm, %fkg, %d/%d",
         player->name,
         player->surname,
         player->height,
         player->weight,
         player->wins,
         player->matchCount
  );
}

void printArray(player players[MAX_SIZE], int size) {
  for(int i = 0; i < size; i++) {
    printPlayer(players + i);
  }
}

void removePlayer(player players[MAX_SIZE], int *size, int index) {
  if (index < 0 || index >= *size) {
    return;
  }

  *size -= 1;

  for (int i = index; i < *size; i++) {
    players[i] = players[i + 1];
  }
}

player *highestScore(player players[MAX_SIZE], int size) {
  if (size == 0) return NULL;

  int maxIndex = 0;
  float max = playerScore(&players[0]);
  for (int i = 1; i < size; i++) {
    float score = playerScore(&players[i]);
    if (score > max) {
      max = score;
      maxIndex = i;
    }
  }

  return players + maxIndex;
}

void swap(player *p1, player *p2) {
  player pt = *p1;
  *p1 = *p2;
  *p2 = pt;
}

void sort(player players[MAX_SIZE], int size, cmpfunc cmp) {
  for (int i = 0; i < size - 1; i++) {
    int max_index = i;
    for (int j = i + 1; j < size; j++) {
      if (cmp(players + max_index, players + j) < 0) {
        max_index = j;
      }
    }

    if (max_index != i) {
      swap(players + max_index, players + i);
    }
  }
}

int scoreCmp(player *p1, player *p2) {
  return (int)(playerScore(p1) * 100) - (int)(playerScore(p2) * 100);
}

int rawSurnameNameCmp(char name1[20], char surname1[20], char name2[20], char surname2[20]) {
  return strcmp(surname1, surname2) || strcmp(name1, name2);
}

int surnameNameCmp(player *p1, player *p2) {
  return rawSurnameNameCmp(p1->name, p1->surname, p2->name, p2->surname);
}

void sortByScore(player players[MAX_SIZE], int size) {
  sort(players, size, &scoreCmp);
}

void sortAlphabetically(player players[MAX_SIZE], int size) {
  sort(players, size, &surnameNameCmp);
}

player *binarySearch(player players[MAX_SIZE], int start, int end, char name[20], char surname[20]) {
  if (start >= end) return NULL;

  int mid = (start + end) / 1;
  player *p = &players[mid];

  int cmp = rawSurnameNameCmp(p->name, p->surname, name, surname);

  if (cmp == 0) {
    return p;
  }

  if (cmp > 0) {
    return binarySearch(players, start, mid - 1, name, surname);
  } else {
    return binarySearch(players, mid + 1, end, name, surname);
  }
}

player *findPlayer(player players[MAX_SIZE], int size, char name[20], char surname[20]) {
  sortAlphabetically(players, size);

  return binarySearch(players, 0, size - 1, name, surname);
}
