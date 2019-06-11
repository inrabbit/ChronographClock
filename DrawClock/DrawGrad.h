#ifndef DEF_DRAWGRAD
#define DEF_DRAWGRAD

#include "DrawApi.h"

#define GRADN_NORMAL 0
#define GRADN_INNER 1
#define GRADN_HALF 2

void DrawGraduation(double gradval, DPoint center, double radius, double length);
void DrawGradNumber(double gradval, DPoint center, double radius, const char *pText, double size, int mode);

double DrawChronographGrad(DPoint center, double radius);
double DrawTachyMeter1(DPoint center, double radius);
double DrawTachyMeter2(DPoint center, double radius);

void DrawSubSecondGrad(DPoint center, double radius);
void DrawSecondGrad(DPoint center, double radius);
double DrawMinuteGrad(DPoint center, double radius);
void DrawMinuteGradInner(DPoint center, double radius);
double DrawCalender(DPoint center, double radius, int days);
void DrawCalenderInner(DPoint center, double radius);

void DrawYearCalenderBox(double grad, DPoint center, double radius);
void DrawCalenderBox(DPoint center, double width);

#endif
