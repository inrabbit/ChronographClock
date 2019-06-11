#include "DrawApi.h"
#include "DrawIndex.h"
#include "Brush.h"

void DrawCenter(DPoint center, double radius)
{
	SelectBrush(BRUSH_LINE02, COLOR_BLACK);

	DPoint p1 = center + DPoint(radius, 0.0);
	DPoint p2 = center + DPoint(-radius, 0.0);
	DrawLine(p1, p2);
	p1 = center + DPoint(0.0, radius);
	p2 = center + DPoint(0.0, -radius);
	DrawLine(p1, p2);
}

void DrawIndexCenter(DPoint center, double radius, int color)
{
	static double OuterCenterRadiusRatio = 0.045;
	static double InnerCenterRadiusRatio = 0.012;

	SelectBrush(BRUSH_FILL, color);
	DrawCircle(center, radius * OuterCenterRadiusRatio);
	SelectBrush(BRUSH_FILL, COLOR_WHITE);
	DrawCircle(center, radius * InnerCenterRadiusRatio);
}

void DrawSubIndexCenter(DPoint center, double radius, int color)
{
	static double OuterCenterRadiusRatio = 0.065 + 0.015;
	static double InnerCenterRadiusRatio = 0.025 + 0.001;

	SelectBrush(BRUSH_FILL, color);
	DrawCircle(center, radius * OuterCenterRadiusRatio);
	SelectBrush(BRUSH_FILL, COLOR_WHITE);
	DrawCircle(center, radius * InnerCenterRadiusRatio);
}

void DrawIndex(DPoint center, double radius, double angle, int type, int color)
{
	static double IndexRatio = 0.9;
	static double ThickRatio = 0.02;
	static double Thick;

	DPoint top = center + DPoint().Polar(radius, angle);

	switch(type){
	case INDEX_NORMAL:
		{
			SelectBrush(BRUSH_FILL_WITHLINE10, color, color);

			static double IndexRatio = 0.18;
			DPoint bottom = center + DPoint().Polar(radius * IndexRatio, angle + MATH_PI);
			DrawTriangle(top, bottom, 0.042);
#if 1
			DPoint inv_top = center + DPoint().Polar(radius, angle + MATH_PI);
			DPoint inv_bottom = center + DPoint().Polar(radius * 0.9, angle + MATH_PI);
			DrawTriangle(inv_top, inv_bottom, 0.5);
#endif
		}
		break;
	case INDEX_SET_THICK:
			Thick = radius * ThickRatio;
			break;
	case INDEX_BOLD:
		{
			DPoint delta;
			delta.Polar(radius * IndexRatio, angle);
			DPoint szPoints[5];
			szPoints[0] = center + DPoint().Polar(Thick, angle - MATH_PI / 2.0);
			szPoints[1] = center + DPoint().Polar(Thick, angle + MATH_PI / 2.0);
			szPoints[2] = szPoints[1] + delta;
			szPoints[3] = top;
			szPoints[4] = szPoints[0] + delta;

			SelectBrush(BRUSH_FILL_WITHLINE10, COLOR_WHITE, COLOR_BLACK);
			DrawPolygon(szPoints, 5);
		}
		break;
	case INDEX_THIN:
		{
			SelectBrush(BRUSH_LINE15, COLOR_RED);
			DrawLine(top, center);
		}
		break;
	}
}
