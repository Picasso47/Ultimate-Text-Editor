#include<iostream>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include "Lines.h"
#include "Document.h"
#include "TextEditor.h"
#include <vector>
#define right 77
#define left 75
#define up 72
#define down 80
#define bckspc 8
#define RED 4
#define WHITE 15
#define BLINK 1286
#define LIGHTGREY 7
#define enter 13
#define ctrl_p 16
#define ctrl_l 12
#define ctrl_u 21
#define ctrl_t 20
#define ctrl_w 23
#define ctrl_e 5
#define ctrl_r 18
#define ctrl_g 7
#define ctrl_y 25
#define ctrl_j 10
#define ctrl_o 15
#define ctrl_k 11
#define ctrl_l 12
#define ctrl_n 14
#define ctrl_q 17
#define ctrl_b 2
#define ctrl_x 24
#define ctrl_div 28
#define ctrl_sqrbktR 29
#define crtl_sqrbktL 27
#define ctrl_f1 0
#define ctrl_d 4
#define ctrl_s 19
#define ctrl_i 9
#define ctrl_z 26
#define ctrl_insrt 146
#define ctrl_num2  145
#define ctrl_dot 147
#define alt_ctrl_u 22
using namespace std;
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void setclr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
TextEditor::TextEditor()
{
	NODs = 1;
	CDoci = 0;
	Doc = new Document[1];
}
TextEditor::TextEditor(int& i)
{
	NODs = i;
	CDoci = 0;
	Doc = new Document[i];
}
 void TextEditor::MenunChoice(int& nudocs)
{
	 int num_docs = 0;
	cout << "<<<------------------------------TEXT EDITOR--------------------------->>><<<< \n";
	cout << "Enter number of documents you want to load/write : ";
		cin >> nudocs;
		nudocs += 1;
}
 void TextEditor::Docloadbyindx(int& i)
 {

 }
void TextEditor:: Run()
{
	int cri = 0, cci = 0; int s; int i = 0; int num_of_docs = 0; char opt; string a;
	MenunChoice(num_of_docs);
	NODs = num_of_docs;
	TextEditor T(num_of_docs);
	int indx = 0;
	cout << "Do you want to load(l) documents or to write(w),index "<< num_of_docs-1 << " is for merging documents by default :";
	cin >> opt;
	switch (opt)
	{
	case 'l':
		for (int i = 0; i < num_of_docs - 1; i++)
		{
			cout << "Enter the file name";
			cin >> a;
			T.Doc[i].load(a);
		}
		system("cls");
		cout << "Enter the index of loaded document,by default only zero index is available to work on :";
		cin >> indx;
		break;
	case 'w':
		cout << "Enter the index of document to b written on :";
		do 
		{
			cin >> indx;
		} while (indx<0 || indx>num_of_docs-1);
		break;
	default:
		break;
	}
	system("cls");
	T.Doc[indx].PrintDocument();
	while (true)
	{
		gotoRowCol(cri, cci);
		if (_kbhit())
		{
			s = _getch();
			if (s == 224)
			{
				s = _getch();
				switch (s)
				{
				case right:
					cci++;
					if (T.Doc[indx].Ls[cri].givelent() < cci)
						cci--;
					break;
				case left:
					cci--;
					break;
				case up:
					if ( cci== T.Doc[indx].Ls[cri].givelent() || cci >= T.Doc[indx].Ls[cri-1].givelent())
						cci= T.Doc[indx].Ls[cri-1].givelent();
					cri--;
					break;
				case down:
					if (cci == T.Doc[indx].Ls[cri].givelent() || cci >= T.Doc[indx].Ls[cri - 1].givelent())
						cci = T.Doc[indx].Ls[cri + 1].givelent();
					cri++;
					if (T.Doc[indx].NOLs < cri +1)
						cri--;
					break;
				}
				continue;
			}
			if (s == bckspc && cci == 0 && cri != 0)
			{
				T.Doc[indx].BackSpace_LineRemover(cri, cci);
				int temp = cci;
				gotoRowCol(cri, 0);
				T.Doc[indx].PrintDocument();
				cri--;
				cci = temp;
			}
			if (s == bckspc && cci != 0)
			{
				T.Doc[indx].Ls[cri].CharRemoverAt_i(cci);
				gotoRowCol(cri, 0);
				T.Doc[indx].Ls[cri].PrintLine(0);
				cci -= 1;
				gotoRowCol(cri, cci);
			}
			if (s!= alt_ctrl_u &&s!=ctrl_dot &&s!= ctrl_num2 && s!=ctrl_b && s!= ctrl_z && s!= ctrl_i && s!=ctrl_s && s!=ctrl_d &&s!= ctrl_f1 && s!= crtl_sqrbktL && s != enter && s!=ctrl_div && s!= ctrl_sqrbktR && s != 24 && s != 14 && s != 12 && s != 11 && s != 15 && s != 10 && s != 25 && s != 7 && s != bckspc && s != 224 && s != 21 && s != 12 && s != 17 && s != 16 && s != 20 && s != 23 && s != 5 && s != 18)
			{
				T.Doc[indx].Ls[cri].insertCharAt_i(cci, s);
				if (T.Doc[indx].Ls[cri].sizelimit())
				{
					T.Doc[indx].Enter_AddNewLine(cri, 80);
					T.Doc[indx].PrintDocument();
					cri++;
					cci = 0;
				}
				else
				{
					gotoRowCol(cri, cci);
					T.Doc[indx].Ls[cri].PrintLine(cci);
					cci++;
				}
			}
			if (s == ctrl_u)
			{
				T.Doc[indx].Ls[cri].ToUpper(0, cci);
				gotoRowCol(cri, 0);
				T.Doc[indx].Ls[cri].PrintLine(0);
			}
			if (s == ctrl_l)
			{
				T.Doc[indx].Ls[cri].ToLower(0, cci);
				gotoRowCol(cri, 0);
				T.Doc[indx].Ls[cri].PrintLine(0);
			}
			if (s == ctrl_q)
			{
				string a;
				gotoRowCol(0, 100);
				cin >> a;
				T.Doc[indx].FindCaseSens(a);
			}
			if (s == ctrl_sqrbktR)
			{
				string a;
				gotoRowCol(0, 100);
				cin >> a;
				T.Doc[indx].FindInCaseSens(a);
			}
			if (s == crtl_sqrbktL)
			{
				int len = 0;
				len= T.Doc[indx].SmallestWordLen();
					gotoRowCol(0, 100);
					cout << len;
			}
			if (s == ctrl_f1)
			{
				int len = 0;
				len = T.Doc[indx].LargestWordLength();
				gotoRowCol(0, 100);
				cout << len;
			}
			if (s == ctrl_x)
			{
				//double avg_len = 0;
				//avg_len = T.Doc[indx].AvgWordLen();
				//gotoRowCol(0, 100);
				//cout << avg_len;
				T.Doc[indx].wordgame();
				system("pause");
				system("cls");
				T.Doc[indx].PrintDocument();
			}
			if (s == ctrl_i)
			{
				int spcl_cntr = 0;
				spcl_cntr = T.Doc[indx].SpecialCharCount();
				gotoRowCol(0, 100);
				cout << spcl_cntr;
			}
			if (s == ctrl_d)
			{
				int wrdcnt = 0;
				wrdcnt = T.Doc[indx].WordCount();
				gotoRowCol(0, 100);
				cout << wrdcnt;
			}
			if (s == ctrl_z)
			{
				int sen_cnt = 0;
				sen_cnt = T.Doc[indx].SentencesCount();
				//sen_cnt = T.Doc[indx].paragraphcount();
				gotoRowCol(0, 100);
				cout << sen_cnt;
			}
			if (s == ctrl_p)
			{
				string a, b;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(0, 100);
				cin >> b;
				T.Doc[indx].Prefix(a,b);
			}
			if (s == ctrl_t)
			{
				string a, b;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(0, 100);
				cin >> b;
				T.Doc[indx].PostFix(a, b);
			}
			if (s == ctrl_w)
			{
				string a, b;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(0, 100);
				cin >> b;
				T.Doc[indx].FindAndReplaceFirst(a,b);
			}
			if (s == ctrl_e)
			{
				string a, b;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(0, 100);
				cin >> b;
				T.Doc[indx].FindAndReplaceAll(a,b);
			}
			if (s == ctrl_r)
			{
				string a;
				gotoRowCol(0, 90);
				cin >> a;
				int pos = T.Doc[indx].Ls[cri].FindNextOnly(a, cci);
				if (pos != NULL)
				{
					gotoRowCol(cri, pos);
					setclr(RED);
					cout << a;
				}
				setclr(LIGHTGREY);
			}
			if (s == ctrl_g)
			{
				string a;
				gotoRowCol(0, 90);
				cin >> a;
				int pos = T.Doc[indx].Ls[cri].FindPrevOnly(a, cci);
				if (pos != NULL)
				{
					gotoRowCol(cri, pos);
					setclr(RED);
					cout << a;
				}
				setclr(LIGHTGREY);
			}
			if (s == ctrl_y)
			{
				int size = 0;
				string a;
				gotoRowCol(0, 100);
				cin >> a;
				gotoRowCol(cri, 0);
				int* ptr = T.Doc[indx].Ls[cri].FindNextAll(a, cci, size);
				for (int i = 0; i < size; i++)
				{
					gotoRowCol(cri, ptr[i]);
					setclr(RED);
					cout << a;
				}
				setclr(LIGHTGREY);
			}
			if (s == ctrl_j)
			{
				int size = 0;
				string a;
				gotoRowCol(0, 100);
				cin >> a;
				gotoRowCol(cri, 0);
				int* ptr = T.Doc[indx].Ls[cri].FindPrevAll(a, cci, size);
				for (int i = 0; i < size; i++)
				{
					gotoRowCol(cri, ptr[i]);
					setclr(RED);
					cout << a;
				}
				setclr(LIGHTGREY);
			}
			if (s == ctrl_o)
			{
				int pos = 0;
				string a, b;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(0, 100);
				cin >> b;
				T.Doc[indx].FindReplaceNext(a,b,cri,cci);
			}
			if (s == ctrl_k)
			{
				int pos = 0;
				string a, b;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(0, 100);
				cin >> b;
				T.Doc[indx].FindReplacePrev(a, b, cri, cci);
			}
			if (s == ctrl_b)
			{
				int pos = 0;
				string a, b;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(0, 100);
				cin >> b;
				T.Doc[indx].FindReplaceAllNext(a,b,cri,cci);
			}
			if (s == ctrl_n)
			{
				int pos = 0;
				string a, b;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(0, 100);
				cin >> b;
				T.Doc[indx].FindReplaceAllPrev(a,b,cri,cci);
			}
			if (s == ctrl_s )
			{
				char s;
				string a;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(1, 90);
				cout << "L for load ,S for update";
				gotoRowCol(2, 90);
				cin >> s;
				if (s == 'l')
					T.Doc[indx].LoadEncodedFile(a);
				if (s == 's')
					T.Doc[indx].SaveasEncodedFile(a);
			}
			if (s == enter)
			{
				T.Doc[indx].Enter_AddNewLine(cri,cci);
				T.Doc[indx].PrintDocument();
				cci = 0;
				cri++;
			}
			if (s == ctrl_div)
			{
				T.Doc[indx].PrintDocument();
			}
			if (s == ctrl_num2)
			{
				string a;
				gotoRowCol(0, 90);
				getline(cin, a);
				T.Doc[indx].FindingSentence(a);
			}
			if (s == ctrl_dot)
			{
				char s;
				string a;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(1, 90);
				cout << "L for load ,S for update";
				gotoRowCol(2, 90);
				cin >> s;
				if(s=='l')
					T.Doc[indx].load(a);
				if (s == 's')
					T.Doc[indx].SimpleUpdater(a);
			}
			if (s == alt_ctrl_u)
			{
				string a;
				string b;
				char z;
				gotoRowCol(0, 90);
				cin >> a;
				gotoRowCol(1, 90);
				cin >> b;
				gotoRowCol(2, 90);
				Document *tDS;
				MergeDocuments(a, b, tDS);
				T.Doc[NODs] = *tDS;
				gotoRowCol(2, 90);
				cout << "(y) to stay on merged document";
				gotoRowCol(3, 90);
				cin >> z;
				switch (z)
				{
				case'y':
				case'Y':
					indx = NODs;
					system("cls");
					T.Doc[NODs].PrintDocument();
					break;
				default:
					break;
				}
				gotoRowCol(2, 90);

			}

		}
	}
} 
void TextEditor::MergeDocuments(string Fname1, string Fname2,Document* & ptr)
{
	int TNODS = 2;
	TextEditor tempT(TNODS);
	tempT.Doc[0].load(Fname1);
	tempT.Doc[1].load(Fname2);
	int tnols = tempT.Doc[0].NOLs + tempT.Doc[1].NOLs;
	//Document *Res = new Document(tnols);
	
	Document* Res = new Document(tnols);
	//m is main loop for 2 docs
	//x is the number of line
	//i is the count of words on line
	int resline = 0;
	for (int m = 0; m < 2;m++)
	{
		for (int x = 0;x<tempT.Doc[m].NOLs; x++)//till number of lines
		{
			for (int i = 0;i<tempT.Doc[m].Ls[x].Size-1; i++)//till end of line
			{
				Res->Ls[resline].insertCharAt_i(i, tempT.Doc[m].Ls[x].Cs[i]);
			}
			resline++;
		}
	}
	/*if (m == 1 && i == tempT.Doc[m].Ls[x].Size - 2)
	{
		Res->Ls[tempT.Doc[m].Ls[x].Size].insertCharAt_i(tempT.Doc[m].Ls[x].Size, '\0');
	}*/
	//Res.PrintDocument();
	ptr = Res;
}
TextEditor::~TextEditor()
{
	NODs = 0;
	CDoci = 0;
	delete[] Doc ;
}