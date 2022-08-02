#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include "Lines.h"
#include "Document.h"
#include "TextEditor.h"
using namespace std;
class TextEditor
{
	friend class Document;
	friend class Lines;
	int CRow = 0, CCol = 0, NODs, CDoci;
	Document* Doc;
public:
	TextEditor();
	TextEditor(int&);
	void Docloadbyindx(int&);
	static void MenunChoice(int& nudocs);
	void Run();
	void MergeDocuments(string Fname1, string Fname2,Document*&);
	~TextEditor();
};

