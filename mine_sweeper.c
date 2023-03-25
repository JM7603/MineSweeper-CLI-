#include "mine_sweeper.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

bool is_win = false;
int wall = MAP_SIZE * MAP_SIZE - MINE_COUNT;  // 除雷以外的墙
Object map[MAP_SIZE][MAP_SIZE];               // 地图大小 9 * 9

void InitMap() {
  for (int i = 0; i < MAP_SIZE; ++i) {
    for (int j = 0; j < MAP_SIZE; ++j) {
      map[i][j].uncovered = false;
      map[i][j].is_mine = false;
    }
  }
}

void ShowMap() {
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  printf("  ");
  for (int i = 0; i < MAP_SIZE; ++i) {
    // 这里输出红色
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | 0);
    printf("%d ", i);
    // 变回原来的颜色
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0);
  }
  putchar('\n');

  // printf("■  ");
  // printf("@  ");
  for (int i = 0; i < MAP_SIZE; ++i) {
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | 0);
    printf("%d ", i);
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | 0);
    for (int j = 0; j < MAP_SIZE; ++j) {
      if (!map[i][j].uncovered) { // 未揭开
        printf("■ ");
      } else if (!map[i][j].is_mine && map[i][j].uncovered) { // 揭开显示周围雷数
        int count = GetRoundMine(i, j);
        if (count > 0) {
          printf("%d ", count);
        } else {
          printf("  ");
        }
      }
      /* else if (map[i][j].is_mine) {
        printf("@  ");
      } */

    }
    putchar('\n');
  }
  printf("wall: %d\n", wall);
}

void GenerateMine() {
  for (int i = 0; i < MINE_COUNT;) {
    int pos_x = rand() % 9;
    int pos_y = rand() % 9;
    if (!map[pos_x][pos_y].is_mine) {
      map[pos_x][pos_y].is_mine = true;
      i++;
    }
  }
}

int GetRoundMine(int x, int y) {
  int count = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (x + i >= 0 && y + j >= 0 && x + i < MAP_SIZE && y + j < MAP_SIZE)
        if (map[x + i][y + j].is_mine) count++;
    }
  }
  return count;
}

bool Action(int x, int y) {
  if (x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE) {
    if (map[x][y].is_mine) {
      return false;
    } else {
      // map[x][y].uncovered = true;
      ShowBlank(x, y);
    }
  }
  if (wall == 0) is_win = true;
  return true;
}

// 这里我想了好久，最后还是在别人代码的基础上改的QAQ
void ShowBlank(int x, int y) {
  if (x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE) {
    int count = GetRoundMine(x, y);
    if (count > 0 && !map[x][y].uncovered) {
      map[x][y].uncovered = true;
      wall--;
    } else if (!map[x][y].uncovered) {
      map[x][y].uncovered = true;
      wall--;
      for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
          ShowBlank(x + i, y + j);
        }
      }
    } else return;
  }
}

bool IsWin() { return is_win; }
