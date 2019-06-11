#include <cstdio>
#include "DrawApi.h"
#include "SlideRule.h"
#include "Brush.h"

double GetSlideRuleAngle(double gradval);
void DrawSlideRuleGraduation(double gradval, DPoint center, double radius, double length);
void DrawSlideRuleText(double gradval, DPoint center, double radius, const char *pText, double size);
void DrawSlideRuleTriangle(double gradval, DPoint center, double radius, double length, double tangent);

#define OUTER_DELTA 0
#define INNER_DELTA 0

// 1.0 <= gradval <= 10.0
double GetSlideRuleAngle(double gradval)
{
	double standard = 2.0 * MATH_PI * log10(6.0);
	double angle = 2.0 * MATH_PI * log10(gradval);
	angle = angle + 2.0 * MATH_PI - standard;
	angle = MATH_PI / 2.0 - angle;
	return angle;
}

void DrawSlideRuleGraduation(double gradval, DPoint center, double radius, double length)
{
	double angle = GetSlideRuleAngle(gradval);
	DPoint start = center + DPoint().Polar(radius, angle);
	DPoint end = center + DPoint().Polar(radius + length, angle);
	DrawLine(start, end);
}

void DrawSlideRuleText(double gradval, DPoint center, double radius, const char *pText, double size)
{
	double angle = GetSlideRuleAngle(gradval);
	DPoint pos = center + DPoint().Polar(radius, angle);
	DrawText(pText, pos, (angle - MATH_PI / 2.0), size);
}

void DrawSlideRuleTriangle(double gradval, DPoint center, double radius, double length, double tangent)
{
	double angle = GetSlideRuleAngle(gradval);
	DPoint top = center + DPoint().Polar(radius, angle);
	DPoint bottom = center + DPoint().Polar(radius + length, angle);
	DrawTriangle(top, bottom, tangent);
}

double DrawSlideRuleOuter(DPoint center, double radius)
{
	static double szBoldGrad[] = {
		1.0, 1.05, 1.1, 1.15, 1.2,
		1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5,
		3.0, 3.5, 4.0, 4.5, 5.0, 5.5,
		6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5,
		10.0 };
	static double szNumbGrad[] = {
		1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9,
		2.0, 2.1, 2.2, 2.3, 2.4, 2.5,
		3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5,
		8.0, 8.5, 9.0, 9.5, 10.0 };

	static double szLength[] = {12.5 +OUTER_DELTA, 8.75 +OUTER_DELTA, 5 +OUTER_DELTA};
	static double TextSize = 17;
	static double TextPos = szLength[0] + TextSize/2;
	double InnerRadius = radius - TextPos - TextSize/2 - 2.0 - 2.0;

	int i, j;

	SelectBrush(BRUSH_FILL_WITHLINE20, COLOR_BLACK, COLOR_WHITE);
	DrawCircle(center, radius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; szBoldGrad[i] != 10.0; i++){
		double interval = szBoldGrad[i + 1] - szBoldGrad[i];
		for(j = 1; j < 5; j++){
			double grad = szBoldGrad[i] + interval * j / 5;
			DrawSlideRuleGraduation(grad, center, InnerRadius, szLength[1]);
		}
		if(szBoldGrad[i] >= 2.5 && szBoldGrad[i + 1] <= 6.0){
			for(j = 1; j < 10; j += 2){
				double grad = szBoldGrad[i] + interval * j / 10;
				DrawSlideRuleGraduation(grad, center, InnerRadius, szLength[2]);
			}
		}
	}

	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0 ; szBoldGrad[i] != 10.0; i++)
		if(szBoldGrad[i] != 1.0 && szBoldGrad[i] != 6.0)
			DrawSlideRuleGraduation(szBoldGrad[i], center, InnerRadius, szLength[0]);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0 ; szNumbGrad[i] != 10.0; i++){
		char szText[256];
		sprintf(szText, "%d", (int)(szNumbGrad[i] * 10.0));
		DrawSlideRuleText(szNumbGrad[i], center, InnerRadius + TextPos, szText, TextSize);
	}

	static double Pos10Out = szLength[0] - 1.25;
	static double PosMphOut = szLength[0] - 1.25;
	static double Pos36OutBeg = szLength[1];
	static double Pos36OutEnd = szLength[1] +7.5 +INNER_DELTA;

	SelectBrush(BRUSH_FILL, COLOR_RED);
	DrawSlideRuleTriangle(1.0, center, InnerRadius, Pos10Out, 0.4);
	DrawSlideRuleTriangle(6.0, center, InnerRadius, PosMphOut, 0.4);
	DrawSlideRuleTriangle(3.6, center, InnerRadius + Pos36OutBeg, Pos36OutEnd - Pos36OutBeg, 0.5);

	return InnerRadius;
}

double DrawSlideRuleInner(DPoint center, double radius)
{
	static double szBoldGrad[] = {
		1.0, 1.05, 1.1, 1.15, 1.2,
		1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5,
		3.0, 3.5, 4.0, 4.5, 5.0, 5.5,
		6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5,
		10.0 };
	static double szNumbGrad[] = {
		1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9,
		2.0, 2.1, 2.2, 2.3, 2.4, 2.5,
		3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0,
		7.0, 8.0, 9.0, 10.0 };

	static double szLength[] = {-6.25 -INNER_DELTA, -5.75 -INNER_DELTA, -3.5 -INNER_DELTA};
	static double TextSize = 16;
	static double TextPos = szLength[0] - TextSize/2 - (-0.25);
	double InnerRadius = radius + TextPos - TextSize/2 - 2.25;

	int i, j;

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	DrawCircle(center, radius);
	for(i = 0; szBoldGrad[i] != 10.0; i++){
		double interval = szBoldGrad[i + 1] - szBoldGrad[i];
		for(j = 1; j < 5; j++){
			double grad = szBoldGrad[i] + interval * j / 5;
			DrawSlideRuleGraduation(grad, center, radius, szLength[1]);
		}
		if(szBoldGrad[i] >= 2.5 && szBoldGrad[i + 1] <= 6.0){
			for(j = 1; j < 10; j += 2){
				double grad = szBoldGrad[i] + interval * j / 10;
				DrawSlideRuleGraduation(grad, center, radius, szLength[2]);
			}
		}
	}

	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0; szBoldGrad[i] != 10.0; i++)
		if(szBoldGrad[i] != 1.0 && szBoldGrad[i] != 6.0)
			DrawSlideRuleGraduation(szBoldGrad[i], center, radius, szLength[0]);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; szNumbGrad[i] != 10.0; i++){
		char szText[256];
		int numb = (szNumbGrad[i] > 6.0) ? (int)szNumbGrad[i] : (int)(szNumbGrad[i] * 10.0);
		sprintf(szText, "%d", numb);
		DrawSlideRuleText(szNumbGrad[i], center, radius + TextPos, szText, TextSize);
	}

	static double Pos10In  = szLength[0];
	static double Pos36InBeg  = szLength[1];
	static double Pos36InEnd  = szLength[1] -7.5 -INNER_DELTA;

	SelectBrush(BRUSH_FILL, COLOR_RED);
	DrawSlideRuleTriangle(1.0, center, radius, Pos10In, 0.5);
	DrawSlideRuleTriangle(6.0, center, radius, InnerRadius - radius, 0.25);
	DrawSlideRuleTriangle(3.6, center, radius + Pos36InBeg, Pos36InEnd - Pos36InBeg, 0.5);

	SelectBrush(BRUSH_TEXT, COLOR_RED);
	DrawSlideRuleText(5.82, center, radius + TextPos, "MPH", 15);

	return InnerRadius;
}

double DrawSlideRuleInnerHours(DPoint center, double radius)
{
	static double szLongGrad[] = {
		1.05, 1.15, 1.3, 1.4, 1.6, 1.7, 1.9,
		2.0, 2.2, 2.3, 2.5, 2.6, 2.8, 2.9,
		3.3, 3.9, 4.5, 5.1, 5.7,
		/*6.0, */6.5, 7.5, 8.5, 9.5, -1 };
	static double szShortGrad[] = {
		3.1, 3.2, 3.4, 3.5, 3.7, 3.8, 4.0, 4.1, 4.3, 4.4, 4.6, 4.7, 4.9,
		5.0, 5.2, 5.3, 5.5, 5.6, 5.8, 5.9, -1 };
	static double szNumbGrad[] = {
		1.0, 1.1, 1.2, 1.5, 1.8, 2.1, 2.4, 2.7, 3.0, 3.6, 4.2, 4.8, 5.4,
		6.0, 7.0, 8.0, 9.0, -1 };

	static double szLength[] = {-6.5, -8.0, -4.6};
	static double TextSize = 14;
	static double TextPos = TextSize/2;
	double InnerRadius = radius + szLength[0] - TextSize - 1.5;

	int i;

	SelectBrush(BRUSH_LINE15, COLOR_BLACK);
	DrawCircle(center, radius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; szShortGrad[i] > 0; i++)
		DrawSlideRuleGraduation(szShortGrad[i], center, radius, szLength[2]);

	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0; szLongGrad[i] > 0; i++)
		DrawSlideRuleGraduation(szLongGrad[i], center, radius, szLength[1]);

	for(i = 0; szNumbGrad[i] > 0; i++){
		SelectBrush(BRUSH_FILL, COLOR_BLACK);
		DrawSlideRuleTriangle(szNumbGrad[i], center, radius, szLength[0], 0.5);

		int minutes = (int)(szNumbGrad[i] * 100.0);
		if(minutes > 600) minutes = minutes / 10;
		char szText[256];
		sprintf(szText, "%d:%02d", minutes / 60, minutes % 60);
		SelectBrush(BRUSH_TEXT, COLOR_BLACK);
		DrawSlideRuleText(szNumbGrad[i], center, InnerRadius + TextPos, szText, TextSize);
	}

	return InnerRadius;
}

#define STAT 0.621371192237334
#define NAUT 0.539957269941486 
void DrawSlideRuleStatNaut(DPoint center, double radius, double StatGrad)
{
	static double Length = -7.5 -INNER_DELTA;
	static double TextPos = -14.75 -INNER_DELTA;
	static double TextSize = 14;

	double KmGrad = StatGrad / STAT;
	double NautGrad = KmGrad * NAUT;

	SelectBrush(BRUSH_FILL, COLOR_RED);
	DrawSlideRuleTriangle(StatGrad, center, radius, Length, 0.5);
	DrawSlideRuleTriangle(NautGrad, center, radius, Length, 0.5);
	DrawSlideRuleTriangle(KmGrad  , center, radius, Length, 0.5);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	DrawSlideRuleText(StatGrad, center, radius + TextPos, "STAT.", TextSize);
	DrawSlideRuleText(NautGrad, center, radius + TextPos, "NAUT.", TextSize);
	DrawSlideRuleText(KmGrad  , center, radius + TextPos, "kM", TextSize);
}
