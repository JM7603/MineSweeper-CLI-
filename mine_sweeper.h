
#ifndef MINE_SWEEPER__MINE_SWEEPER_H_
#define MINE_SWEEPER__MINE_SWEEPER_H_

#include <stdbool.h>

#define MAP_SIZE 9
#define MINE_COUNT 10

typedef struct Object {
  bool uncovered;   // 是否被揭开: true 裸露，false 未裸露
  bool is_mine;     // 是否为雷: true 是雷，false 不是雷
} Object;

/* 初始化地图 */
void InitMap();

/* 显示地图 */
void ShowMap();

/* 在随机位置生成雷 */
void GenerateMine();

/* 拿到指定位置的物体周围的雷数 */
int GetRoundMine(int x, int y);

/* 扫雷 */
bool Action(int x, int y);

/* 如果周围没有雷就自动揭开 */
void ShowBlank(int x, int y);

/* 判断是否胜利 */
bool IsWin();

#endif // MINE_SWEEPER__MINE_SWEEPER_H_
