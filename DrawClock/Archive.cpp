#include <fstream>
#include "Archive.h"

#define MAX_ARCHIVE_STRING_SIZE 256

bool Archive::WriteToFile(const char *pFileName)
{
	ofstream ofstr;
	ofstr.open(pFileName, ios::binary);
	if(!ofstr) return false;
	ofstr.write(m_strstr.str(), m_strstr.pcount());
	ofstr.close();
	return true;
}

bool Archive::ReadFromFile(const char *pFileName)
{
	ifstream ifstr;
	ifstr.open(pFileName, ios::binary);
	if(!ifstr) return false;
	ifstr.seekg(0, ios::end);
	int length = ifstr.tellg();
	ifstr.seekg(0, ios::beg);

	char *pBuffer = new char[length];
	ifstr.read(pBuffer, length);
	m_strstr.write(pBuffer, length);

	ifstr.close();
	delete[] pBuffer;
	return true;
}

bool Archive::AppendFrom(Archive *pArchive)
{
	m_strstr.write(pArchive->m_strstr.str(), pArchive->m_strstr.pcount());
	return true;
}

void Archive::WriteText(string Text)
{
	size_t size = Text.length();
	m_strstr.write((const char *)&size, sizeof(size));
	m_strstr.write(Text.c_str(), size);
}

string Archive::ReadText()
{
	size_t size;
	m_strstr.read((char *)&size, sizeof(size));
	if(size > MAX_ARCHIVE_STRING_SIZE) return string("");
	char szTemp[MAX_ARCHIVE_STRING_SIZE];
	m_strstr.read(szTemp, size);
	szTemp[size] = '\0';
	return string(szTemp);
}

void Archive::WriteDouble(double Val)
{
	m_strstr.write((const char *)&Val, sizeof(Val));
}

double Archive::ReadDouble()
{
	double Val;
	m_strstr.read((char *)&Val, sizeof(Val));
	return Val;
}

void Archive::WriteFloat(float Val)
{
	m_strstr.write((const char *)&Val, sizeof(Val));
}

float Archive::ReadFloat()
{
	float Val;
	m_strstr.read((char *)&Val, sizeof(Val));
	return Val;
}

void Archive::WriteChar(char Val)
{
	m_strstr.write((const char *)&Val, sizeof(Val));
}

char Archive::ReadChar()
{
	char Val;
	m_strstr.read((char *)&Val, sizeof(Val));
	return Val;
}

void Archive::WriteInteger(int Val)
{
	m_strstr.write((const char *)&Val, sizeof(Val));
}

int Archive::ReadInteger()
{
	int Val;
	m_strstr.read((char *)&Val, sizeof(Val));
	return Val;
}
