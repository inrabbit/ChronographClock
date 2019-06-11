#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "DrawApi.h"
#include "Archive.h"

// Global Variables
Archive g_Archive;

// Implementation

void CreateDrawOrderFile(const char *pFileName)
{
	if(!g_Archive.WriteToFile(pFileName)){
		cerr << "Cannot create " << pFileName << endl;
		exit(1);
	}

}

void DrawLine(DPoint p1, DPoint p2)
{
	g_Archive.WriteChar(ORDER_LINE);
	g_Archive.WriteDouble(p1.x);
	g_Archive.WriteDouble(p1.y);
	g_Archive.WriteDouble(p2.x);
	g_Archive.WriteDouble(p2.y);
}

void DrawPolygon(DPoint *pPoints, int nPoints)
{
	g_Archive.WriteChar(ORDER_POLYGON);
	g_Archive.WriteInteger(nPoints);

	for(int i = 0; i < nPoints; i++){
		g_Archive.WriteDouble(pPoints[i].x);
		g_Archive.WriteDouble(pPoints[i].y);
	}
}

void DrawCircle(DPoint center, double radius)
{
	g_Archive.WriteChar(ORDER_CIRCLE);
	g_Archive.WriteDouble(center.x);
	g_Archive.WriteDouble(center.y);
	g_Archive.WriteDouble(radius);
}

void DrawText(const char *pText, DPoint p, double angle, double size)
{
	g_Archive.WriteChar(ORDER_TEXT);
	g_Archive.WriteText(pText);
	g_Archive.WriteDouble(p.x);
	g_Archive.WriteDouble(p.y);
	g_Archive.WriteDouble(angle);
	g_Archive.WriteDouble(size);
}

void NewLayer(const char *pLayerName)
{
#if 1
	string text = string(" ") + pLayerName;
	pLayerName = text.c_str();
#endif
#if 1
	g_Archive.WriteChar(ORDER_NEWLAYER);
	g_Archive.WriteText(pLayerName);
#endif
}

void DrawTriangle(DPoint top, DPoint bottom, double tangent)
{
	DPoint delta = bottom - top;
	double angle = delta.Angle();
	double d = delta.Length();
	double r = sqrt(d * d * (1.0 + tangent * tangent));
	double theta = atan(tangent);
	DPoint p[3];
	p[0] = top;
	p[1] = top.ToDouble() + DPoint().Polar(r, angle + theta);
	p[2] = top.ToDouble() + DPoint().Polar(r, angle - theta);
	DrawPolygon(p, 3);
}

void DrawBox(DPoint center, DPoint size, double angle)
{
	DPoint h = size / 2.0;
	DPoint p[4];
	p[0] = h;
	p[1] = DPoint(h.x, -h.y);
	p[2] = DPoint(-h.x, -h.y);
	p[3] = DPoint(-h.x, h.y);
	for(int i = 0; i < 4; i++){
		p[i].Rotate(angle);
		p[i] = p[i] + center;
	}
	DrawPolygon(p, 4);
}

void DeselectArtOnCurrentLayer()
{
	g_Archive.WriteChar(ORDER_DESELECTCURLAYER);
}

void SetLineWidth(double width)
{
	g_Archive.WriteChar(ORDER_CUR_LINEWIDTH);
	g_Archive.WriteDouble(width);
}

void SetIsPathFill(bool IsFillPath, bool IsStrokePath)
{
	g_Archive.WriteChar(ORDER_CUR_IS_PATHFILL);
	g_Archive.WriteChar((char)IsFillPath);
	g_Archive.WriteChar((char)IsStrokePath);
}

void SetFillColor(Color color)
{
	switch(color.type){
	case Color::cmyk:
		g_Archive.WriteChar(ORDER_CUR_FILL_COLOR_FOUR);
		g_Archive.WriteFloat(color.cyan);
		g_Archive.WriteFloat(color.magenta);
		g_Archive.WriteFloat(color.yellow);
		g_Archive.WriteFloat(color.black);
		break;
	case Color::rgb:
		g_Archive.WriteChar(ORDER_CUR_FILL_COLOR_RGB);
		g_Archive.WriteFloat(color.red);
		g_Archive.WriteFloat(color.green);
		g_Archive.WriteFloat(color.blue);
		break;
	}
}

void SetStrokeColor(Color color)
{
	switch(color.type){
	case Color::cmyk:
		g_Archive.WriteChar(ORDER_CUR_STRK_COLOR_FOUR);
		g_Archive.WriteFloat(color.cyan);
		g_Archive.WriteFloat(color.magenta);
		g_Archive.WriteFloat(color.yellow);
		g_Archive.WriteFloat(color.black);
		break;
	case Color::rgb:
		g_Archive.WriteChar(ORDER_CUR_STRK_COLOR_RGB);
		g_Archive.WriteFloat(color.red);
		g_Archive.WriteFloat(color.green);
		g_Archive.WriteFloat(color.blue);
		break;
	}
}

void SetLayer(const char *pLayerName)
{
	g_Archive.WriteChar(ORDER_SETLAYER);
	g_Archive.WriteText(pLayerName);
}

void SetLayerEditable(const char *pLayerName, bool IsEditable)
{
	g_Archive.WriteChar(ORDER_SETLAYEREDITABLE);
	g_Archive.WriteText(pLayerName);
	g_Archive.WriteChar((char)IsEditable);
}
