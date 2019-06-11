#include <cstdio>
#include <cstdlib>
#include "DrawApi.h"
#include "SlideRule.h"
#include "DrawGrad.h"
#include "DrawIndex.h"
#include "Brush.h"

#define ORDER_FILE "C:\\DrawOrder.bin"

double GetRandomAngle()
{
#if 0
	int k = rand() % 3600;
	return 2.0 * MATH_PI * k / 3600;
#else
	return MATH_PI / 2.0;
#endif
}

double DrawOuterDial(DPoint center, double radius)
{
#if 0
	NewLayer("Reference");
	//DrawCenter(center, 10);
	SelectBrush(BRUSH_LINE20, COLOR_BLACK);
	DrawCircle(center, radius - 6);
	SelectBrush(BRUSH_LINE50, COLOR_BLACK);
	DrawCircle(center, radius - 2.5);
#endif
	double SlideRuleRadius = radius - 3.0;

	NewLayer("SlideRuleOut");
	double SlideRuleOuter = DrawSlideRuleOuter(center, SlideRuleRadius);

	NewLayer("ColorPlate");
	SelectBrush(BRUSH_FILL, COLOR_CUSTOM01);
	DrawCircle(center, SlideRuleOuter);

	NewLayer("SlideRuleIn");
	double SlideRuleInner = DrawSlideRuleInner(center, SlideRuleOuter);
	DrawSlideRuleStatNaut(center, SlideRuleOuter, 3.8);

	NewLayer("Hours");
	double TachyMeterRadius = DrawSlideRuleInnerHours(center, SlideRuleInner);

	NewLayer("Tachy");
	/*double TachyMeterRadius = */DrawTachyMeter2(center, SlideRuleInner);
#if 1
	NewLayer("OuterDial");
	SelectBrush(BRUSH_LINE10, COLOR_BLACK);
	DrawCircle(center, SlideRuleInner);
	DrawChronographGrad(center, SlideRuleInner - 3.0);
#endif
	NewLayer("InnerDial");
	double ChronographRadius = DrawChronographGrad(center, TachyMeterRadius - 3.0);

	return ChronographRadius;
}

void DrawInnerDial(DPoint center, double InnerRadius)
{
	double SubCircleRadius = InnerRadius / (1.0 + sqrt(2.0));
	//SubCircleRadius *= 0.98;
	SubCircleRadius *= 0.96;
	double r = InnerRadius - SubCircleRadius;

	DPoint SubSecondCenter = center + DPoint(0.0, r);
	DPoint SecondCenter = center + DPoint(-r, 0.0);
	DPoint MinuteCenter = center + DPoint(0.0, -r);
	DPoint DateCenter = center + DPoint(r, 0.0);

	NewLayer("SubSec");
	DrawSubSecondGrad(SubSecondCenter, SubCircleRadius);

	NewLayer("Sec");
	DrawSecondGrad(SecondCenter, SubCircleRadius);

	NewLayer("Min");
	double InnerMinuteRadius = DrawMinuteGrad(MinuteCenter, SubCircleRadius);
	DrawMinuteGradInner(MinuteCenter, InnerMinuteRadius);

	NewLayer("Date31");
	double InnerCalendRadius = DrawCalender(DateCenter, SubCircleRadius, 31);

	NewLayer("Date30");
	DrawCalender(DateCenter, SubCircleRadius, 30);

	NewLayer("Date29");
	DrawCalender(DateCenter, SubCircleRadius, 29);

	NewLayer("Date28");
	DrawCalender(DateCenter, SubCircleRadius, 28);

	NewLayer("Days");
	DrawCalenderInner(DateCenter, InnerCalendRadius);

	NewLayer("Calen");
	DrawYearCalenderBox(3.0 / 8, center, InnerRadius * 0.8475);
	DrawCalenderBox(DateCenter, SubCircleRadius * 2.0);

	NewLayer("Index5");
	DrawIndex(MinuteCenter, InnerMinuteRadius, GetRandomAngle(), INDEX_NORMAL, COLOR_RED);
	DrawIndex(DateCenter, InnerCalendRadius, GetRandomAngle(), INDEX_NORMAL, COLOR_RED);

	NewLayer("Index4");
	static double SubSecondIndexRatio = 0.93;
	static double SecondIndexRatio = 0.94;
	DrawIndex(SubSecondCenter, SubCircleRadius * SubSecondIndexRatio, GetRandomAngle(), INDEX_NORMAL, COLOR_RED);
	DrawIndex(SecondCenter, SubCircleRadius * SecondIndexRatio, GetRandomAngle(), INDEX_NORMAL, COLOR_BLACK);
	DrawIndex(MinuteCenter, SubCircleRadius * SecondIndexRatio, GetRandomAngle(), INDEX_NORMAL, COLOR_BLACK);
	DrawIndex(DateCenter, SubCircleRadius * SecondIndexRatio, GetRandomAngle(), INDEX_NORMAL, COLOR_BLACK);

	NewLayer("SubCenter");
	DrawSubIndexCenter(SubSecondCenter, SubCircleRadius, COLOR_RED);
	DrawSubIndexCenter(SecondCenter, SubCircleRadius, COLOR_BLACK);
	DrawSubIndexCenter(MinuteCenter, SubCircleRadius, COLOR_BLACK);
	DrawSubIndexCenter(DateCenter, SubCircleRadius, COLOR_BLACK);

	NewLayer("Index3");
	DrawIndex(center, InnerRadius + 17.0, GetRandomAngle(), INDEX_THIN, COLOR_RED);

	NewLayer("Index2");
	DrawIndex(center, InnerRadius, GetRandomAngle(), INDEX_SET_THICK, COLOR_BLACK);
	DrawIndex(center, InnerRadius * 0.65, GetRandomAngle(), INDEX_BOLD, COLOR_BLACK);

	NewLayer("Index1");
	DrawIndex(center, InnerRadius, GetRandomAngle(), INDEX_BOLD, COLOR_BLACK);

	NewLayer("Center");
	DrawIndexCenter(center, InnerRadius, COLOR_BLACK);
}

#define BUTTON_NUM 5
void DrawButton(DPoint top, DPoint size)
{
#if 0
	double d = 5;
	double t = 30;

	DPoint p1 = top + size + DPoint(-d, -d);
	DPoint p2 = top + DPoint(size.x, 0.0) + DPoint(-d, d);
	DPoint p3 = top + DPoint(0.0, size.y) + DPoint(d, -d);
	DPoint p4 = top + DPoint(d, d);

	SelectBrush(BRUSH_FILL, COLOR_BLACK);
	DrawTriangle(p1, p1 + DPoint(-t, -t), 1.0);
	DrawTriangle(p2, p2 + DPoint(-t, t), 1.0);
	//DrawTriangle(p3, p3 + DPoint(t, -t), 1.0);
	DrawTriangle(p4, p4 + DPoint(t, t), 1.0);
#endif

	double vspace = 2;
	double hspace = 5;
	DPoint sizeButton;

	static const char *pszLabels[] = {"MODE", "CALENDER", "TACHYMETRE", "SLIDE RULE", "COLOR", NULL};
	sizeButton.x = size.x / 18;
	sizeButton.y = (size.y - vspace * (BUTTON_NUM - 1)) / BUTTON_NUM;

	NewLayer("ButtonMask");
	SelectBrush(BRUSH_FILL, COLOR_WHITE);
	DrawBox(top + DPoint((hspace + sizeButton.x)/2, size.y/2), DPoint(hspace + sizeButton.x, size.y), 0.0);

	NewLayer("Button");
	for(int i = 0; i < BUTTON_NUM; i++){
		SelectBrush(BRUSH_FILL, COLOR_BLACK);
		DPoint center = top + DPoint(sizeButton.x/2, sizeButton.y/2 + (sizeButton.y + vspace) * i);
		DrawBox(center, sizeButton, 0.0);
		SelectBrush(BRUSH_TEXT, COLOR_WHITE);
		DrawText(pszLabels[i], center, MATH_PI/2.0, 14);
	}

	sizeButton.x = size.x / 6;
	sizeButton.y = size.y / 19;

	SelectBrush(BRUSH_FILL, COLOR_BLACK);
	DrawBox(top + size - sizeButton/2, sizeButton, 0.0);
	DrawBox(top + size - sizeButton/2 - DPoint(0, sizeButton.y + vspace), sizeButton, 0.0);
	DrawBox(top + DPoint(size.x - sizeButton.x/2, sizeButton.y/2), sizeButton, 0.0);
	SelectBrush(BRUSH_TEXT, COLOR_WHITE);
	DrawText("START/STOP", top + size - sizeButton/2, 0.0, 14);
	DrawText("RESET", top + size - sizeButton/2 - DPoint(0, sizeButton.y + vspace), 0.0, 14);
	DrawText("SETTING", top + DPoint(size.x - sizeButton.x/2, sizeButton.y/2), 0.0, 14);
}

// Illustrator's default screen size is (600, 800)
int main()
{
	DPoint center(300.0 , 400.0);
	double radius = 300.0;

	double InnerRadius = DrawOuterDial(center, radius);
	DrawInnerDial(center, InnerRadius);

	DrawButton(center - DPoint(300, 300), DPoint(600, 600));

	CreateDrawOrderFile(ORDER_FILE);

	return 0;
}
