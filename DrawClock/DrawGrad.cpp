#include <cstdio>
#include "DrawApi.h"
#include "DrawGrad.h"
#include "Brush.h"

#define ABS(X) (((X) > 0) ? (X) : -(X))

// 0.0 <= gradval <= 1.0
void DrawGraduation(double gradval, DPoint center, double radius, double length)
{
	double angle = 2.0 * MATH_PI * gradval;
	angle = MATH_PI / 2.0 - angle;
	DPoint start = center + DPoint().Polar(radius, angle);
	DPoint end = center + DPoint().Polar(radius + length, angle);
	DrawLine(start, end);
}

void DrawGradTriangle(double gradval, DPoint center, double radius, double length, double tangent)
{
	double angle = 2.0 * MATH_PI * gradval;
	angle = MATH_PI / 2.0 - angle;
	DPoint top = center + DPoint().Polar(radius, angle);
	DPoint bottom = center + DPoint().Polar(radius + length, angle);
	DrawTriangle(top, bottom, tangent);
}

void DrawGradNumber(double gradval, DPoint center, double radius, const char *pText, double size, int mode)
{
	bool IsNear090 = ABS(gradval - 0.25) < 0.001;
	bool IsNear270 = ABS(gradval - 0.75) < 0.001;

	double angle = 2.0 * MATH_PI * gradval;
	angle = MATH_PI / 2.0 - angle;
	DPoint pos = center + DPoint().Polar(radius, angle);
	double theta;
	switch(mode){
	case GRADN_INNER:
		theta = angle - MATH_PI / 2.0;
		break;
	case GRADN_HALF:

		if(IsNear090 || IsNear270 || !IsNear090 && !IsNear270 && sin(angle) >= 0)
			theta = angle - MATH_PI / 2.0;
		else
			theta = angle + MATH_PI / 2.0;
		break;
	case GRADN_NORMAL:
	default:
		theta = 0.0;
	}
	DrawText(pText, pos, theta, size);
}

double DrawChronographGrad(DPoint center, double radius)
{
	static double GradLong = -13.3;
	static double GradShort = -7.6;
	static double TextSize = 14;
	static double TextPos = GradLong - TextSize/2 -0.5;
	double InnerRadius = radius + GradLong;

	int i;

	for(i = 0; i < 60; i++){
		SelectBrush((i % 5 == 0) ? BRUSH_LINE20 : BRUSH_LINE10, COLOR_BLACK);
		DrawGraduation(double(i) / 60, center, radius, GradLong);
	}
	for(i = 0; i < 300; i++)
		if(i % 5)
			DrawGraduation(double(i) / 300, center, radius, GradShort);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; i < 12; i++){
		char szText[256];
		sprintf(szText, "%d", (i == 0) ? 60 : 5 * i);
		DrawGradNumber(double(i) / 12, center, radius + TextPos, szText, TextSize, GRADN_HALF);
	}

	return InnerRadius;
}

double DrawTachyMeter1(DPoint center, double radius)
{
	static int szBoldGrad[] = {
		60, 65, 70, 75, 80, 85, 90, 95, 100, 
		110, 120, 130, 140, 150, 160, 170, 180,
		200, 220, 240, 270, 300, 350, 400, 500, 600, 750, 1000, 0 };
	static int szShortGrad[] = {
		142, 144, 146, 148,
		152, 154, 156, 158,
		165, 175, 190, 210, 230, 250, 260, 280, 290,
		325, 375, 425, 450, 475, 550, 650, 700, 0 };

	static double GradLong = 9.65;
	static double GradShort = GradLong / 2;
	static double TextPos = 11.5;
	static double TextSize = 12;
	double InnerRadius = radius - 12 - 6.5;

	int i, j;

	SelectBrush(BRUSH_LINE15, COLOR_BLACK);
	DrawCircle(center, InnerRadius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	DrawCircle(center, radius);
	for(i = 0; szBoldGrad[i] != 100; i++){
		double interval = szBoldGrad[i + 1] - szBoldGrad[i];
		for(j = 1; j < 5; j++){
			double val = szBoldGrad[i] + interval * j / 5;
			DrawGraduation(60.0 / val, center, InnerRadius, GradShort);
		}
	}
	for(; szBoldGrad[i] != 140; i++){
		double interval = szBoldGrad[i + 1] - szBoldGrad[i];
		for(j = 1; j < 10; j++){
			double val = szBoldGrad[i] + interval * j / 10;
			if(j == 5)
				DrawGraduation(60.0 / val, center, InnerRadius, GradLong);
			else
				DrawGraduation(60.0 / val, center, InnerRadius, GradShort);
		}
	}
	for(i = 0; szShortGrad[i]; i++)
		DrawGraduation(60.0 / szShortGrad[i], center, InnerRadius, GradShort);

	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0; szBoldGrad[i]; i++)
		DrawGraduation(60.0 / szBoldGrad[i], center, InnerRadius, GradShort);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; szBoldGrad[i]; i++){
		char szText[256];
		sprintf(szText, "%d", szBoldGrad[i]);
		DrawGradNumber(60.0 / szBoldGrad[i], center, InnerRadius + TextPos, szText, TextSize, GRADN_HALF);
	}
	DrawGradNumber(60.0 / 62.5, center, InnerRadius + TextPos, "BASE", TextSize, GRADN_HALF);

	return InnerRadius;
}

double DrawTachyMeter2(DPoint center, double radius)
{
	static int szBoldGrad[] = {
		60, 65, 70, 75, 80, 85, 90, 95, 100, 
		110, 120, 130, 140, 150, 160, 170, 180,
		200, 220, 240, 270, 300, 350, 400, 500, 600, 750, 1000, 0 };
	static int szShortGrad[] = {
		142, 144, 146, 148,
		152, 154, 156, 158,
		165, 175, 190, 210, 230, 250, 260, 280, 290,
		325, 375, 425, 450, 475, 550, 650, 700, 0 };

	static double szLength[] = {-6.5, -8.0, -4.6};
	static double TextSize = 13.5;
	static double TextPos = szLength[0] - TextSize/2 -2.5;
	double InnerRadius = radius + szLength[0] - 14 - 1.5;

	int i, j;

#if 1	// Inverse
	for(i = 0; i < 3; i++) szLength[i] = -szLength[i];
	TextPos = -TextPos;
	radius = InnerRadius;
#endif

	SelectBrush(BRUSH_LINE15, COLOR_BLACK);
	DrawCircle(center, radius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; szBoldGrad[i] != 100; i++){
		double interval = szBoldGrad[i + 1] - szBoldGrad[i];
		for(j = 1; j < 5; j++){
			double val = szBoldGrad[i] + interval * j / 5;
			DrawGraduation(60.0 / val, center, radius, szLength[2]);
		}
	}
	for(; szBoldGrad[i] != 140; i++){
		double interval = szBoldGrad[i + 1] - szBoldGrad[i];
		for(j = 1; j < 10; j++){
			double val = szBoldGrad[i] + interval * j / 10;
			if(j == 5){
				SelectBrush(BRUSH_LINE20, COLOR_BLACK);
				DrawGraduation(60.0 / val, center, radius, szLength[1]);
			}else{
				SelectBrush(BRUSH_LINE10, COLOR_BLACK);
				DrawGraduation(60.0 / val, center, radius, szLength[2]);
			}
		}
	}

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; szShortGrad[i]; i++)
		DrawGraduation(60.0 / szShortGrad[i], center, radius, szLength[2]);

	SelectBrush(BRUSH_FILL, COLOR_BLACK);
	for(i = 0; szBoldGrad[i]; i++)
		DrawGradTriangle(60.0 / szBoldGrad[i], center, radius, szLength[0], 0.5);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; szBoldGrad[i]; i++){
		char szText[256];
		sprintf(szText, "%d", szBoldGrad[i]);
		DrawGradNumber(60.0 / szBoldGrad[i], center, radius + TextPos, szText, TextSize, GRADN_HALF);
	}
	DrawGradNumber(60.0 / 62.5, center, radius + TextPos, "BASE", TextSize, GRADN_HALF);
	DrawGradNumber(1.9 / 60.0, center, radius + TextPos, "1000", TextSize, GRADN_HALF);
#if 1
	// To draw character M underline
	double grad = 2.6 / 60.0;
	DrawGradNumber(grad, center, radius + TextPos + 1.0, "M", TextSize - 3, GRADN_HALF);
	double angle = 2.0 * MATH_PI * (0.25 - grad);
	DPoint LineCenter = center + DPoint().Polar(radius + TextPos - TextSize / 2 + 1.0, angle);
	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	DrawLine(LineCenter + DPoint().Polar(2.8, angle + MATH_PI / 2), LineCenter + DPoint().Polar(2.8, angle - MATH_PI / 2));
#endif
#if 0
	DrawGradNumber(2.0 / 60.0, center, radius + TextPos - 5.0, "TACHY", TextSize, GRADN_HALF);
	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	DrawCircle(center, radius + 2.5);
#endif

	return InnerRadius;
}

void DrawSubSecondGrad(DPoint center, double radius)
{
	static double GradLong = -10.5;
	static double GradShort = -5.7;
	static double TextPos = -22.7;
	static double TextSize = 12;

	int i;

	SelectBrush(BRUSH_FILL_WITHLINE15, COLOR_BLACK, COLOR_WHITE);
	DrawCircle(center, radius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; i < 20; i++)
		if(i % 2)
			DrawGraduation(double(i) / 20, center, radius, GradShort);

	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0; i < 10; i++)
		DrawGraduation(double(i) / 10, center, radius, GradLong);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; i < 10; i += 2){
		char szText[256];
		sprintf(szText, "%1.1f", 0.1 * i);
		DrawGradNumber(double(i) / 10, center, radius + TextPos, szText, TextSize, GRADN_NORMAL);
	}
}

void DrawSecondGrad(DPoint center, double radius)
{
	static double GradLong = -9;
	static double GradShort = -4.9;
	static double TextPos = -17;
	static double TextSize = 12;

	int i;

	SelectBrush(BRUSH_FILL_WITHLINE15, COLOR_BLACK, COLOR_WHITE);
	DrawCircle(center, radius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; i < 60; i++)
		if(i % 5)
			DrawGraduation(double(i) / 60, center, radius, GradShort);

	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0; i < 12; i++)
		DrawGraduation(double(i) / 12, center, radius, GradLong);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; i < 12; i += 2){
		char szText[256];
		sprintf(szText, "%02d", (i == 0) ? 60 : 5 * i);
		DrawGradNumber(double(i) / 12, center, radius + TextPos, szText, TextSize, GRADN_HALF);
	}
}

double DrawMinuteGrad(DPoint center, double radius)
{
	static double GradLong = -9;
	static double GradShort = -4.9;
	static double TextSize = 12;
	static double TextPos = GradLong - TextSize/2 - 2.0;
	static double InnerRadius = radius + TextPos - TextSize/2 - 3.0;

	int i;

	SelectBrush(BRUSH_FILL_WITHLINE15, COLOR_BLACK, COLOR_WHITE);
	DrawCircle(center, radius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; i < 60; i++)
		if(i % 5)
			DrawGraduation(double(i) / 60, center, radius, GradShort);

	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0; i < 12; i++)
		DrawGraduation(double(i) / 12, center, radius, GradLong);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; i < 12; i += 2){
		char szText[256];
		sprintf(szText, "%d", (i == 0) ? 60 : 5 * i);
		DrawGradNumber(double(i) / 12, center, radius + TextPos, szText, TextSize, GRADN_HALF);
	}

	return InnerRadius;
}

void DrawMinuteGradInner(DPoint center, double radius)
{
	static double TextRatio = -23; // ratio[%] of radius
	static double GradLongRatio = -10;	// ratio[%] of radius
	static double GradShortRatio = -14;	// ratio[%] of radius
	static double TextSize = 12;

	int i;
	
	SelectBrush(BRUSH_LINE02, COLOR_BLACK);
	DrawCircle(center, radius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 1; i < 12; i += 2)
		DrawGraduation(double(i) / 12, center, radius, radius * GradShortRatio / 100.0);

//	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0; i < 6; i++)
		DrawGraduation(double(i) / 6, center, radius, radius * GradLongRatio / 100.0);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; i < 6; i++){
		char szText[256];
		sprintf(szText, "%d", (i == 0) ? 12 : 2 * i);
		DrawGradNumber(double(i) / 6, center, radius * (1.0 + TextRatio / 100.0), szText, TextSize, GRADN_NORMAL);
	}
}

#define NUMBER_PER_DATE 3
double DrawCalender(DPoint center, double radius, int days)
{
	static double GradLong = -9;
	static double GradHalf = -3.25;
	static double GradShort = -6.5;
	static double TextSize = 12;
	static double TextPos = GradLong - TextSize/2 - 2.0;
	static double InnerRadius = radius + TextPos - TextSize/2 - 3.0;

	int i;

	SelectBrush(BRUSH_FILL_WITHLINE15, COLOR_BLACK, COLOR_WHITE);
	DrawCircle(center, radius);

	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; i < days; i++){
		if(i % NUMBER_PER_DATE)
			DrawGraduation(double(i) / days, center, radius, GradShort);
		DrawGraduation((double(i) + 0.5) / days, center, radius, GradHalf);
	}

	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	for(i = 0; i < days; i++)
		if(i % NUMBER_PER_DATE == 0)
			DrawGraduation(double(i) / days, center, radius, GradLong);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	for(i = 0; i < days; i++){
		if(i % 3) continue;
		char szText[256];
		sprintf(szText, "%d", i + 1);
		DrawGradNumber(double(i) / days, center, radius + TextPos, szText, TextSize, GRADN_HALF);
	}

	return InnerRadius;
}

void DrawCalenderInner(DPoint center, double radius)
{
	static double TextRatio = -26 + 2; // ratio[%] of radius
	static double GradShortRatio = -6;	// ratio[%] of radius
	static double TextSize = 12;

	int i;
	
	SelectBrush(BRUSH_LINE02, COLOR_BLACK);
	DrawCircle(center, radius);

#if 0
	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	for(i = 0; i < 7; i++)
		DrawGraduation(double(i) / 7, center, radius, radius * GradShortRatio / 100.0);
#endif
	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	static const char *pszDay[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
	for(i = 0; i < 7; i++){
		DrawGradNumber(double(i) / 7, center, radius * (1.0 + TextRatio / 100.0), pszDay[i], TextSize, GRADN_NORMAL);
		//DrawGradNumber(double(i) / 7, center, radius * (1.0 + (TextRatio + 4) / 100.0), pszDay[i], TextSize, GRADN_HALF);
	}
}

void DrawYearCalenderBox(double grad, DPoint center, double radius)
{
	static double TextSize = 14;
	static DPoint BoxSize(68, 18);

	SelectBrush(BRUSH_FILL_WITHLINE10, COLOR_BLACK, COLOR_WHITE);
	double angle = 2.0 * MATH_PI * (0.25 - grad);
	DPoint BoxCenter = center + DPoint().Polar(radius, angle);
	DrawBox(BoxCenter, BoxSize, angle + MATH_PI / 2);

	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	DrawGradNumber(grad, center, radius, "SEP 2004", TextSize, GRADN_HALF);
}

void DrawCalenderBox(DPoint center, double width)
{
	SelectBrush(BRUSH_FILL_WITHLINE10, COLOR_BLACK, COLOR_WHITE);
	DrawBox(center, DPoint(width, 25), 0.0);
	SelectBrush(BRUSH_TEXT, COLOR_BLACK);
	DrawText("SUN, OCT, 10, 2004", center, 0.0, 15);
}
