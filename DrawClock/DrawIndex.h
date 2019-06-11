#ifndef DEF_DRAW_INDEX
#define DEF_DRAW_INDEX

#include "DrawApi.h"

#define INDEX_SET_THICK 0
#define INDEX_NORMAL 1
#define INDEX_BOLD 2
#define INDEX_THIN 3

void DrawCenter(DPoint center, double radius);
void DrawIndexCenter(DPoint center, double radius, int color);
void DrawSubIndexCenter(DPoint center, double radius, int color);
void DrawIndex(DPoint center, double radius, double angle, int type, int color);

#endif
