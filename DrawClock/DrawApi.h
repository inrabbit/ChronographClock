#ifndef DEF_DRAWAPI
#define DEF_DRAWAPI

#include <cmath>

#define MATH_PI 3.1415926535

class Color
{
public:
	enum { rgb, cmyk } type;
	float red, green, blue;
	float cyan, magenta, yellow, black;
public:
	Color() {}
	Color(float Cyan, float Magenta, float Yellow, float Black) :
		cyan(Cyan), magenta(Magenta), yellow(Yellow), black(Black) { type = cmyk; }
	Color(float Red, float Green, float Blue) :
		red(Red), green(Green), blue(Blue) { type = rgb; }
	void SetColor(float Cyan, float Magenta, float Yellow, float Black){
		type = cmyk, cyan = Cyan, magenta = Magenta, yellow = Yellow, black = Black; }
	void SetColor(float Red, float Green, float Blue){
		type = rgb, red = Red, green = Green, blue = Blue; }
};

template<class T> class Point
{
public:
	T x, y;
public:
	Point() {}
	Point(T _x, T _y) : x(_x), y(_y) {}
	Point<T> Polar(T r, T theta){
		x = r * cos(theta);
		y = r * sin(theta);
		return *this;
	}
	Point<T> operator+(Point<T> p){
		return Point<T>(x + p.x, y + p.y);
	}
	Point<T> operator-(Point<T> p){
		return Point<T>(x - p.x, y - p.y);
	}
	Point<T> operator*(T r){
		return Point<T>(x * r, y * r);
	}
	Point<T> operator/(T r){
		return Point<T>(x / r, y / r);
	}
	Point<T> Rotate(T angle){
		Polar(Length(), Angle() + angle);
		return *this;
	}
	Point<double> ToDouble(){
		return Point<double>((double)x, (double)y);
	}
	Point<float> ToFloat(){
		return Point<float>((float)x, (float)y);
	}
	T Length(){ return (T)sqrt(x * x + y * y); }
	T Angle(){ return (x < 0) ? (T)(atan(y / x) + MATH_PI) : (T)atan(y / x); }
};

typedef Point<double> DPoint;
typedef Point<float> FPoint;

void CreateDrawOrderFile(const char *pFileName);

void DrawLine(DPoint p1, DPoint p2);
void DrawPolygon(DPoint *pPoints, int nPoints);
void DrawCircle(DPoint center, double radius);
void DrawText(const char *pText, DPoint p, double angle, double size);
void NewLayer(const char *pLayerName);
void DrawTriangle(DPoint top, DPoint bottom, double tangent);
void DrawBox(DPoint center, DPoint size, double angle);
void DeselectArtOnCurrentLayer();
void SetLineWidth(double width);
void SetIsPathFill(bool IsFillPath, bool IsStrokePath);
void SetFillColor(Color color);
void SetStrokeColor(Color color);
void SetLayer(const char *pLayerName);
void SetLayerEditable(const char *pLayerName, bool IsEditable);

#endif
