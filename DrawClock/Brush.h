#ifndef DEF_BRUSH
#define DEF_BRUSH

// Colors
#define COLOR_BLACK 0
#define COLOR_WHITE 1
#define COLOR_RED 2
#define COLOR_CUSTOM01 10
#define COLOR_CUSTOM02 11
#define COLOR_CUSTOM03 12

// Brush types
#define BRUSH_LINE02 0
#define BRUSH_LINE10 1
#define BRUSH_LINE15 2
#define BRUSH_LINE20 3
#define BRUSH_LINE30 4
#define BRUSH_LINE40 5
#define BRUSH_LINE50 6
#define BRUSH_LINE60 7
#define BRUSH_LINE70 8
#define BRUSH_LINE80 9
#define BRUSH_TEXT 31
#define BRUSH_FILL 32

#define BRUSH_FILL_WITHLINE10 20
#define BRUSH_FILL_WITHLINE15 21
#define BRUSH_FILL_WITHLINE20 22

void SelectBrush(int BrushType, int BrushColor);
void SelectBrush(int BrushType, int ColorStroke, int ColorFill);

#endif
