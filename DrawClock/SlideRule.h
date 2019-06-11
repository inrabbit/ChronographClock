#ifndef DEF_SLIDERULE
#define DEF_SLIDERULE

#include "DrawApi.h"

double DrawSlideRuleOuter(DPoint center, double radius);
double DrawSlideRuleInner(DPoint center, double radius);
double DrawSlideRuleInnerHours(DPoint center, double radius);

void DrawSlideRuleStatNaut(DPoint center, double radius, double StatGrad);

#endif