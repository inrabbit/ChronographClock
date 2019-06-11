#include "Brush.h"
#include "DrawApi.h"
#include <map>

void DefineColor(std::map<int, Color>& mapColor)
{
	mapColor[COLOR_BLACK] = Color(0, 0, 0);
	mapColor[COLOR_WHITE] = Color(1, 1, 1);
	mapColor[COLOR_RED] = Color(1, 0, 0);
	mapColor[COLOR_CUSTOM01] = Color(0.0235, 0.0353, 0.1059, 0.0);
}

void SelectBrush(int BrushType, int BrushColor)
{
	switch(BrushType){
	case BRUSH_LINE02:
		SetIsPathFill(false, true);
		SetLineWidth(0.25);
		break;
	case BRUSH_LINE10:
		SetIsPathFill(false, true);
		SetLineWidth(1.0);
		break;
	case BRUSH_LINE15:
		SetIsPathFill(false, true);
		SetLineWidth(1.5);
		break;
	case BRUSH_LINE20:
		SetIsPathFill(false, true);
		SetLineWidth(2.0);
		break;
	case BRUSH_LINE30:
		SetIsPathFill(false, true);
		SetLineWidth(3.0);
		break;
	case BRUSH_LINE40:
		SetIsPathFill(false, true);
		SetLineWidth(4.0);
		break;
	case BRUSH_LINE50:
		SetIsPathFill(false, true);
		SetLineWidth(5.0);
		break;
	case BRUSH_LINE60:
		SetIsPathFill(false, true);
		SetLineWidth(6.0);
		break;
	case BRUSH_LINE70:
		SetIsPathFill(false, true);
		SetLineWidth(7.0);
		break;
	case BRUSH_LINE80:
		SetIsPathFill(false, true);
		SetLineWidth(8.0);
		break;
	case BRUSH_TEXT:
	case BRUSH_FILL:
		SetIsPathFill(true, false);
		SetLineWidth(0.0);
		break;
	}

	std::map<int, Color> mapColor;
	DefineColor(mapColor);

	SetFillColor(mapColor[BrushColor]);
	SetStrokeColor(mapColor[BrushColor]);
}

void SelectBrush(int BrushType, int ColorStroke, int ColorFill)
{
	switch(BrushType){
	case BRUSH_FILL_WITHLINE10:
		SetIsPathFill(true, true);
		SetLineWidth(1.0);
		break;
	case BRUSH_FILL_WITHLINE15:
		SetIsPathFill(true, true);
		SetLineWidth(1.5);
		break;
	case BRUSH_FILL_WITHLINE20:
		SetIsPathFill(true, true);
		SetLineWidth(2.0);
		break;
	}

	std::map<int, Color> mapColor;
	DefineColor(mapColor);

	SetFillColor(mapColor[ColorFill]);
	SetStrokeColor(mapColor[ColorStroke]);
}
