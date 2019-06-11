#ifndef DEF_ARCHIVE
#define DEF_ARCHIVE

#include <iostream>
#include <strstream>
#include <string>
using namespace std;

#pragma warning (disable: 4786)

#define ORDER_LINE 1
#define ORDER_POLYGON 2
#define ORDER_CIRCLE 3
#define ORDER_TEXT 4
#define ORDER_NEWLAYER 5
#define ORDER_DESELECTCURLAYER 6
#define ORDER_SETLAYER 7
#define ORDER_SETLAYEREDITABLE 8
#define ORDER_LINEWIDTH 9
#define ORDER_CUR_LINEWIDTH 10
#define ORDER_CUR_IS_PATHFILL 11
#define ORDER_CUR_FILL_COLOR_FOUR 12
#define ORDER_CUR_FILL_COLOR_RGB 13
#define ORDER_CUR_STRK_COLOR_FOUR 14
#define ORDER_CUR_STRK_COLOR_RGB 15

#define STREAM_SIZE (1024 * 100)

class Archive
{
public:
	strstream m_strstr;
public:
	Archive() {}
	bool WriteToFile(const char *pFileName);
	bool ReadFromFile(const char *pFileName);
	bool AppendFrom(Archive *pArchive);
	void Suicide(){ delete this; }

	void WriteText(string Text);
	string ReadText();

	void WriteDouble(double Val);
	double ReadDouble();

	void WriteFloat(float Val);
	float ReadFloat();

	void WriteChar(char Val);
	char ReadChar();

	void WriteInteger(int val);
	int ReadInteger();
};

#endif
