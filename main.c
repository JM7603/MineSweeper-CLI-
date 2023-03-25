#include "mine_sweeper.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int x = 0, y = 0;
  InitMap();
  srand((unsigned int) time(NULL));
  GenerateMine();
  system("cls");
  do {
    ShowMap();
    printf("请输入坐标(x y): ");
    scanf_s("%d %d", &x, &y);
    if (!Action(x, y)) break;
    system("cls");
  } while (!IsWin());

  if (IsWin()) {
    printf("恭喜你扫雷成功!\n");
  } else {
    printf("败北!\n");
  }
  return 0;
}
