//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_dmod.h"
#include "f_gl.h"
#include "f_it.h"
#include "f_trativ.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_it *Form_it;
extern int flag_ovp;
extern AnsiString s1,s2,s3,data;
const AnsiString se[6] =
	{"SELECT org.name_org, Sum(trati.cena_tr) AS [Sum-cena_tr],Count(org.name_org) AS [Count-name_org] ",
	" SELECT prod_vid.name_prod_vid, Sum(trati.cena_tr) AS [Sum-cena_tr], Count(prod_vid.name_prod_vid) AS [Count-name_prod_vid] ",
	" SELECT prod.name_prod, Sum(trati.cena_tr) AS [Sum-cena_tr], Count(prod.name_prod) AS [Count-name_prod]",
	" SELECT Sum(trati.cena_tr) AS [Sum-cena_tr], Count(prod.name_prod) AS [Count-name_prod], trati.data_tr ",
	" SELECT Count(prod.name_prod) AS [Count-name_prod], Sum(trati.cena_tr) AS [Sum-cena_tr], prod.name_prod ",
	" SELECT prod.name_prod, trati.cena_tr, trati.data_tr, trati.kol_ed_tr, org.name_org "};

const AnsiString fr[5] =
	{" FROM org inner JOIN trati ON org.kod_org = trati.kod_org_tr ",
	" FROM prod_vid inner JOIN (prod inner JOIN (org inner JOIN trati ON org.kod_org = trati.kod_org_tr) ON prod.kod_prod = trati.kod_prod_tr) ON prod_vid.kod_prod_vid = prod.kod_prod_vid_v ",
	" FROM org inner JOIN trati ON org.kod_org = trati.kod_org_tr ",
	" FROM trati LEFT JOIN (prod LEFT JOIN prod_vid ON prod.kod_prod_vid_v = prod_vid.kod_prod_vid) ON trati.kod_prod_tr = prod.kod_prod ",
	" FROM prod inner JOIN (org inner JOIN trati ON org.kod_org = trati.kod_org_tr) ON prod.kod_prod = trati.kod_prod_tr "};

const AnsiString gr[6] =
	{" GROUP BY org.name_org ORDER BY Sum(trati.cena_tr) DESC; ",
	" GROUP BY prod_vid.name_prod_vid ORDER BY Sum(trati.cena_tr) DESC; ",
	" GROUP BY prod.name_prod ORDER BY Sum(trati.cena_tr) DESC; ",
	" GROUP BY trati.data_tr ORDER BY trati.data_tr; ",
	" GROUP BY prod.name_prod HAVING (((Count(*))>=5)) ORDER BY Sum(trati.cena_tr) DESC , Count(*) DESC; ",
	" ORDER BY trati.data_tr; "};

const AnsiString pr_tr[4] =
	{"SELECT Year(data_prih) AS m FROM [prih] GROUP BY Year(data_prih) ORDER BY Year(data_prih)",
	 "SELECT Sum(sum_prih) AS m, Month(data_prih) AS data FROM prih WHERE Year([data_prih]) LIKE :y GROUP BY Month(data_prih) ORDER BY Month(data_prih);",
	 "SELECT Year(data_tr) AS m FROM [trati] GROUP BY Year(data_tr) ORDER BY Year(data_tr)",
	 "SELECT Sum(cena_tr) AS m, Month(data_tr) AS data FROM trati WHERE Year([data_tr]) LIKE :y GROUP BY Month(data_tr) ORDER BY Month(data_tr);"};
//---------------------------------------------------------------------------
__fastcall TForm_it::TForm_it(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::FormShortCut(TWMKey &Msg, bool &Handled)
{
	if (Msg.CharCode==27)
	{
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::N1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::N2Click(TObject *Sender)
{
	dmod1->ADOQ_see->Sort="name_org ASC";
	dmod1->ADOQ_sea->Sort="name_org ASC";
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::N3Click(TObject *Sender)
{
	dmod1->ADOQ_see->Sort="name_prod_vid ASC";
	dmod1->ADOQ_sea->Sort="name_prod_vid ASC";
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::N4Click(TObject *Sender)
{
	dmod1->ADOQ_see->Sort="name_prod ASC";
	dmod1->ADOQ_sea->Sort="name_prod ASC";
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::N5Click(TObject *Sender)
{
	dmod1->ADOQ_see->Sort="cena_tr ASC";
	dmod1->ADOQ_sea->Sort="cena_tr ASC";
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::N6Click(TObject *Sender)
{
	dmod1->ADOQ_see->Sort="data_tr ASC";
	dmod1->ADOQ_sea->Sort="data_tr ASC";
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::N7Click(TObject *Sender)
{
	WinExec("Calc.exe", SW_RESTORE);
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::FormShow(TObject *Sender)
{
	if (!dmod1->ADOQ_see->RecordCount)
	C1->Enabled=false;
	else
	C1->Enabled=true;

	dmod1->ADOQ_sea->Close();
	dmod1->ADOQ_sea->SQL->Text = dmod1->ADOQ_see->SQL->Text;
	dmod1->ADOQ_sea->Open();
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::EXCEL1Click(TObject *Sender)
{
	if(dmod1->ADOQ_see->RecordCount)
	{
		ProgressBar1->Visible=true;
		ProgressBar1->Position=5;
		try
		{
			vVarApp=CreateOleObject("Excel.Application");
			ProgressBar1->Position=25;
		}
		catch(...)
		{
			MessageBoxA(0,"Ошибка при открытии сервера Excel","Ошибка",MB_OK);
			Abort();
		}
		start();  ProgressBar1->Position=75;
		qwery_org();     ProgressBar1->Position=80;
		qwery_prodvid(); ProgressBar1->Position=85;
		qwery_prod();    ProgressBar1->Position=90;
		qwery_dt();      ProgressBar1->Position=100;
		vVarApp.OlePropertySet("Visible",true);

		vVarCell.Clear();
		vVarCell = Unassigned;
		vVarCell = NULL;

		vVarSheet.Clear();
		vVarSheet = Unassigned;
		vVarSheet = NULL;

		vVarApp.Clear();
		vVarApp = Unassigned;
		vVarApp = NULL;

		ProgressBar1->Position=0;
		ProgressBar1->Visible=false;
	}
    else
	ShowMessage("В этом диапазоне покупок нет.");
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::start()
{
	int i,j;
	AnsiString str;
	vVarApp.OlePropertySet("SheetsInNewWorkbook",5);
	vVarApp.OlePropertyGet("Workbooks").OleProcedure("Add");
	vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
	vVarSheet=vVarSheets.OlePropertyGet("Item",1);
	vVarSheet.OlePropertySet("Name",WideString("Учет денег"));
	dmod1->ADOQ_sea->First();
	for (i = 1; i <= 8; i++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",1,i);
		switch (i)
		{
			case 1: str="№ П/П";		break;
			case 2: str="Дата";vVarCell.OlePropertySet("ColumnWidth",20);			break;
			case 3: str="Компания";vVarCell.OlePropertySet("ColumnWidth",25);		break;
			case 4: str="Тип продукта";vVarCell.OlePropertySet("ColumnWidth",25);	break;
			case 5: str="Продукт";vVarCell.OlePropertySet("ColumnWidth",25);	 	break;
			case 6: str="Цена";		  	break;
			case 7: str="Кол.Ед.";vVarCell.OlePropertySet("ColumnWidth",25);		break;
			case 8: str="Примечание";vVarCell.OlePropertySet("ColumnWidth",25);		break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
	}
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:H1"));
	vVarCell.OlePropertySet("RowHeight",25);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

	Variant A(OPENARRAY(int,(0,dmod1->ADOQ_sea->RecordCount,0,7)),varVariant);

	for (i = 1; i <= dmod1->ADOQ_sea->RecordCount; i++)
	{
		for (j = 1; j <= 8; j++)
		{
			switch (j)
			{
				case 1: str=IntToStr(i);break;
				case 2: str=FormatDateTime("dddddd",dmod1->ADOQ_sea->FieldByName("data_tr")->AsDateTime);str=strtok(str.c_str(),"/");break;
				case 3: str=dmod1->ADOQ_sea->FieldByName("name_org")->AsAnsiString;			break;
				case 4: str=dmod1->ADOQ_sea->FieldByName("name_prod_vid")->AsAnsiString;		break;
				case 5: str=dmod1->ADOQ_sea->FieldByName("name_prod")->AsAnsiString;			break;
				case 6: str=dmod1->ADOQ_sea->FieldByName("cena_tr")->AsAnsiString;	break;
				case 7: str=dmod1->ADOQ_sea->FieldByName("kol_ed_tr")->AsAnsiString;			break;
				case 8: str=dmod1->ADOQ_sea->FieldByName("prim_tr")->AsAnsiString;				break;
				default:break;
			}
			A.PutElement(str,i-1,j-1);
		}
		dmod1->ADOQ_sea->Next();
	}

	WideString CellA,CellB;
	CellA="A1:H"+IntToStr(1+dmod1->ADOQ_sea->RecordCount);
	CellB="A2:H"+IntToStr(1+dmod1->ADOQ_sea->RecordCount);
	Variant MR = vVarApp.OlePropertyGet("Range",WideString(CellB));
	MR.OlePropertySet("Value",A);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertySet("HorizontalAlignment",-4131);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Italic",true);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A:A"));
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:H1"));
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);
	//vVarApp.OlePropertyGet("ActiveWindow").OlePropertySet("SplitColumn",0);
	//vVarApp.OlePropertyGet("ActiveWindow").OlePropertySet("SplitRow",1);
	//vVarApp.OlePropertyGet("ActiveWindow").OlePropertySet("FreezePanes", true);
}
inline void TForm_it::qwery_org()
{
	switch (flag_ovp)
	{
		case 0: s=se[0]+fr[2]+" WHERE "+data+gr[0]; break;
		case 1: s=se[0]+fr[0]+" WHERE "+s1+" AND "+data+gr[0]; break;
		case 2: s=se[0]+fr[1]+" WHERE "+s2+" AND "+data+gr[0]; break;
		case 3: s=se[0]+fr[1]+" WHERE "+s1+" AND "+s2+" AND "+data+gr[0]; break;
		case 6: s=se[0]+fr[1]+" WHERE "+s2+s3+" AND "+data+gr[0]; break;
		case 7: s=se[0]+fr[1]+" WHERE "+s1+" AND "+s2+s3+" AND "+data+gr[0]; break;
		default: break;
	}
	dmod1->q->Close();
	dmod1->q->SQL->Text=s;
	graf_org();
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::graf_org()
{
	AnsiString str;
	int g,k;
	vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
	vVarSheet=vVarSheets.OlePropertyGet("Item",2);
	vVarSheet.OlePropertySet("Name",WideString("Компании"));
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:D1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",27);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("RowHeight",25);
	vVarCell.OlePropertySet("Value",WideString("Итоги покупок c "+DateToStr(Form_gl->DateTimePicker_n->Date)+" по "+DateToStr(Form_gl->DateTimePicker_k->Date)));
	for (k = 1; k <= 4; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		switch (k)
		{
			case 1: str="№ П/П";break;
			case 2: str="Название компании";vVarCell.OlePropertySet("ColumnWidth",35);break;
			case 3: str="Рублей";vVarCell.OlePropertySet("ColumnWidth",15);break;
			case 4: str="Кол.пок.";break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
	}
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A2:D2"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

	dmod1->q->Close();
	dmod1->q->Open();
	dmod1->q->First();

	Variant A(OPENARRAY(int,(0,dmod1->q->RecordCount,0,4)),varVariant);

	for (g = 1; g <= dmod1->q->RecordCount; g++)
	{
		for (k = 1; k <= 4; k++)
		{
			switch (k)
			{
				case 1: str=IntToStr(g);break;
				case 2: str=dmod1->q->FieldByName("name_org")->AsAnsiString;break;
				case 3: str=dmod1->q->FieldByName("Sum-cena_tr")->AsAnsiString;break;
				case 4: str=dmod1->q->FieldByName("Count-name_org")->AsAnsiString;break;
				default:break;
			}
			A.PutElement(str,g-1,k-1);
		}
		dmod1->q->Next();
	}

	WideString CellA;
	CellA = "A3:D"+IntToStr(2+dmod1->q->RecordCount);
	Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
	MR.OlePropertySet("Value",A);

	CellA="A"+IntToStr(3+dmod1->q->RecordCount)+":B"+IntToStr(3+dmod1->q->RecordCount);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertySet("Value",WideString("ВСЕГО:"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	for (k = 3; k <= 4; k++)
	{
		switch (k)
		{
			case 3: str=sum_tr->Caption;break;
			case 4: str=IntToStr(dmod1->ADOQ_sea->RecordCount);break;
			default:break;
		}
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",3+dmod1->q->RecordCount,k);
		vVarCell.OlePropertySet("Value",WideString(str));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	}

	CellA="A1:D"+IntToStr(3+dmod1->q->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Italic",true);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("B:C"));
	vVarCell.OlePropertySet("HorizontalAlignment",-4131);
}
//---------------------------------------------------------------------------

inline void TForm_it::qwery_prodvid()
{
	switch (flag_ovp)
	{
		case 0: s=se[1]+fr[3]+" WHERE "+data+gr[1]; break;
		case 1: s=se[1]+fr[1]+" WHERE "+s1+" AND "+data+gr[1]; break;
		case 2: s=se[1]+fr[3]+" WHERE "+s2+" AND "+data+gr[1]; break;
		case 3: s=se[1]+fr[1]+" WHERE "+s1+" AND "+s2+" AND "+data+gr[1]; break;
		case 6: s=se[1]+fr[3]+" WHERE "+s2+s3+" AND "+data+gr[1]; break;
		case 7: s=se[1]+fr[1]+" WHERE "+s1+" AND "+s2+s3+" AND "+data+gr[1]; break;
		default: break;
	}
	dmod1->q->Close();
	dmod1->q->SQL->Text=s;
	graf_prodvid();
}
//---------------------------------------------------------------------------

void __fastcall TForm_it::graf_prodvid()
{
	AnsiString str;
	int g,k;
	vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
	vVarSheet=vVarSheets.OlePropertyGet("Item",3);
	vVarSheet.OlePropertySet("Name",WideString("Вид продуктов"));
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:D1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",45);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("RowHeight",25);
	vVarCell.OlePropertySet("Value",WideString("Итоги покупок c "+DateToStr(Form_gl->DateTimePicker_n->Date)+" по "+DateToStr(Form_gl->DateTimePicker_k->Date)));
	for (k = 1; k <= 4; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		switch (k)
		{
			case 1: str="№ П/П";break;
			case 2: str="Вид продуктов";vVarCell.OlePropertySet("ColumnWidth",35);break;
			case 3: str="Рублей";vVarCell.OlePropertySet("ColumnWidth",15);break;
			case 4: str="Кол.пок.";break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
	}
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A2:D2"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

	dmod1->q->Close();
	dmod1->q->Open();
	dmod1->q->First();

	Variant A(OPENARRAY(int,(0,dmod1->q->RecordCount,0,4)),varVariant);

	for (g = 1; g <= dmod1->q->RecordCount; g++)
	{
		for (k = 1; k <= 4; k++)
		{
			switch (k)
			{
				case 1: str=IntToStr(g);break;
				case 2: str=dmod1->q->FieldByName("name_prod_vid")->AsAnsiString;break;
				case 3: str=dmod1->q->FieldByName("Sum-cena_tr")->AsAnsiString;break;
				case 4: str=dmod1->q->FieldByName("Count-name_prod_vid")->AsAnsiString;break;
				default:break;
			}
			A.PutElement(str,g-1,k-1);
		}
		dmod1->q->Next();
	}

	WideString CellA;
	CellA = "A3:D"+IntToStr(2+dmod1->q->RecordCount);
	Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
	MR.OlePropertySet("Value",A);

	CellA="A"+IntToStr(3+dmod1->q->RecordCount)+":B"+IntToStr(3+dmod1->q->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertySet("Value",WideString("ВСЕГО:"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	for (k = 3; k <= 4; k++)
	{
		switch (k)
		{
			case 3: str=sum_tr->Caption;break;
			case 4: str=IntToStr(dmod1->ADOQ_sea->RecordCount);break;
			default:break;
		}
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",3+dmod1->q->RecordCount,k);
		vVarCell.OlePropertySet("Value",WideString(str));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	}

	CellA="A1:D"+IntToStr(3+dmod1->q->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Italic",true);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("B:C"));
	vVarCell.OlePropertySet("HorizontalAlignment",-4131);
}
//---------------------------------------------------------------------------
inline void TForm_it::qwery_prod()
{
	switch (flag_ovp)
	{
		case 0: s=se[2]+fr[3]+" WHERE "+data+gr[2]; break;
		case 1: s=se[2]+fr[4]+" WHERE "+s1+" AND "+data+gr[2]; break;
		case 2: s=se[2]+fr[3]+" WHERE "+s2+" AND "+data+gr[2]; break;
		case 3: s=se[2]+fr[1]+" WHERE "+s1+" AND "+s2+" AND "+data+gr[2]; break;
		case 6: s=se[2]+fr[3]+" WHERE "+s2+s3+" AND "+data+gr[2]; break;
		case 7: s=se[2]+fr[1]+" WHERE "+s1+" AND "+s2+s3+" AND "+data+gr[2]; break;
		default: break;
	}
	dmod1->q->Close();
	dmod1->q->SQL->Text=s;
	graf_prod();
}
//---------------------------------------------------------------------------

void __fastcall TForm_it::graf_prod()
{
	AnsiString str;
	int g,k;
	vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
	vVarSheet=vVarSheets.OlePropertyGet("Item",4);
	vVarSheet.OlePropertySet("Name",WideString("Продукты"));
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:D1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",37);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("RowHeight",25);
	vVarCell.OlePropertySet("Value",WideString("Итоги покупок c "+DateToStr(Form_gl->DateTimePicker_n->Date)+" по "+DateToStr(Form_gl->DateTimePicker_k->Date)));
	for (k = 1; k <= 4; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		switch (k)
		{
			case 1: str="№ П/П";break;
			case 2: str="Продукт";vVarCell.OlePropertySet("ColumnWidth",35);break;
			case 3: str="Рублей";vVarCell.OlePropertySet("ColumnWidth",15);break;
			case 4: str="Кол.пок.";break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
	}
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A2:D2"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

	dmod1->q->Close();
	dmod1->q->Open();
	dmod1->q->First();

	Variant A(OPENARRAY(int,(0,dmod1->q->RecordCount,0,4)),varVariant);

	for (g = 1; g <= dmod1->q->RecordCount; g++)
	{
		for (k = 1; k <= 4; k++)
		{
			switch (k)
			{
				case 1: str=IntToStr(g);break;
				case 2: str=dmod1->q->FieldByName("name_prod")->AsAnsiString;break;
				case 3: str=dmod1->q->FieldByName("Sum-cena_tr")->AsAnsiString;break;
				case 4: str=dmod1->q->FieldByName("Count-name_prod")->AsAnsiString;break;
				default:break;
			}
			A.PutElement(str,g-1,k-1);
		}
		dmod1->q->Next();
	}
	WideString CellA;
	CellA = "A3:D"+IntToStr(2+dmod1->q->RecordCount);
	Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
	MR.OlePropertySet("Value",A);

	CellA="A"+IntToStr(3+dmod1->q->RecordCount)+":B"+IntToStr(3+dmod1->q->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertySet("Value",WideString("ВСЕГО:"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	for (k = 3; k <= 4; k++)
	{
		switch (k)
		{
			case 3: str=sum_tr->Caption;break;
			case 4: str=IntToStr(dmod1->ADOQ_sea->RecordCount);break;
			default:break;
		}
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",3+dmod1->q->RecordCount,k);
		vVarCell.OlePropertySet("Value",WideString(str));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	}
	CellA="A1:D"+IntToStr(3+dmod1->q->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Italic",true);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("B:C"));
	vVarCell.OlePropertySet("HorizontalAlignment",-4131);
}
//---------------------------------------------------------------------------
inline void TForm_it::qwery_dt()
{
	switch (flag_ovp)
	{
		case 0: s=se[3]+fr[3]+" WHERE "+data+gr[3]; break;
		case 1: s=se[3]+fr[4]+" WHERE "+s1+" AND "+data+gr[3]; break;
		case 2: s=se[3]+fr[3]+" WHERE "+s2+" AND "+data+gr[3]; break;
		case 3: s=se[3]+fr[1]+" WHERE "+s1+" AND "+s2+" AND "+data+gr[3]; break;
		case 6: s=se[3]+fr[3]+" WHERE "+s2+s3+" AND "+data+gr[3]; break;
		case 7: s=se[3]+fr[1]+" WHERE "+s1+" AND "+s2+s3+" AND "+data+gr[3]; break;
		default: break;
	}
	dmod1->q->Close();
	dmod1->q->SQL->Text=s;
	graf_dt();
}
//---------------------------------------------------------------------------

void __fastcall TForm_it::graf_dt()
{
	AnsiString str;
	int g,k;
	vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
	vVarSheet=vVarSheets.OlePropertyGet("Item",5);
	vVarSheet.OlePropertySet("Name",WideString("По дате"));
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:D1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",40);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("RowHeight",25);
	vVarCell.OlePropertySet("Value",WideString("Итоги покупок c "+DateToStr(Form_gl->DateTimePicker_n->Date)+" по "+DateToStr(Form_gl->DateTimePicker_k->Date)));
	for (k = 1; k <= 4; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		switch (k)
		{
			case 1: str="№ П/П";break;
			case 2: str="Дата покупок";vVarCell.OlePropertySet("ColumnWidth",30);break;
			case 3: str="Рублей";vVarCell.OlePropertySet("ColumnWidth",20);break;
			case 4: str="Кол.пок.";break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
	}
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A2:D2"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

	dmod1->q->Close();
	dmod1->q->Open();
	dmod1->q->First();

	Variant A(OPENARRAY(int,(0,dmod1->q->RecordCount,0,4)),varVariant);

	for (g = 1; g <= dmod1->q->RecordCount; g++)
	{
		for (k = 1; k <= 4; k++)
		{
			switch (k)
			{
				case 1: str=IntToStr(g);break;
				case 2: str=FormatDateTime("dddddd",dmod1->q->FieldByName("data_tr")->AsDateTime);str=strtok(str.c_str(),"/");break;
				case 3: str=dmod1->q->FieldByName("Sum-cena_tr")->AsAnsiString;break;
				case 4: str=dmod1->q->FieldByName("Count-name_prod")->AsAnsiString;break;
				default:break;
			}
			A.PutElement(str,g-1,k-1);
		}
		dmod1->q->Next();
	}
	WideString CellA;
	CellA = "A3:D"+IntToStr(2+dmod1->q->RecordCount);
	Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
	MR.OlePropertySet("Value",A);

	CellA="A"+IntToStr(3+dmod1->q->RecordCount)+":B"+IntToStr(3+dmod1->q->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertySet("Value",WideString("ВСЕГО:"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	for (k = 3; k <= 4; k++)
	{
		switch (k)
		{
			case 3: str=sum_tr->Caption;break;
			case 4: str=IntToStr(dmod1->ADOQ_sea->RecordCount);break;
			default:break;
		}
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",3+dmod1->q->RecordCount,k);
		vVarCell.OlePropertySet("Value",WideString(str));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	}
	CellA="A1:D"+IntToStr(3+dmod1->q->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Italic",true);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	try
	{
		CellA="B3:C"+IntToStr(2+dmod1->q->RecordCount);
		Variant Chart = vVarApp.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Charts").OleFunction("Add");
		Chart.OlePropertySet("ChartType",51);
		Chart.OleProcedure("SetSourceData",vVarSheet.OlePropertyGet("Range",WideString(CellA)),2);
		Chart.OlePropertyGet("SeriesCollection",1).OlePropertySet("Name",WideString("Сумма"));
		Chart.OlePropertyGet("ChartTitle").OlePropertySet("Text",WideString("Дни"));
		Chart.OleProcedure("Location",2,vVarSheet.OlePropertyGet("Name"));
//		vVarSheet = vVarApp.OlePropertyGet("ActiveSheet");
//		vVarSheet.OleProcedure("Activate");
//		Variant ChartObj = vVarSheet.OlePropertyGet("ChartObjects",0);
//      ChartObj.OlePropertySet("Left",120);
	}
	catch(...)
	{
		MessageBoxA(0,"Ваша версия MS Excel не позволяет строить графики командами Builder C++","Ошибка", MB_OK);
		return;
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm_it::EXCEL2Click(TObject *Sender)
{
	switch (flag_ovp)
	{
		case 0: s=se[4]+fr[3]+" WHERE "+data+gr[4]; break;
		case 1: s=se[4]+fr[4]+" WHERE "+s1+" AND "+data+gr[4]; break;
		case 2: s=se[4]+fr[3]+" WHERE "+s2+" AND "+data+gr[4]; break;
		case 3: s=se[4]+fr[1]+" WHERE "+s1+" AND "+s2+" AND "+data+gr[4]; break;
		case 6: s=se[4]+fr[3]+" WHERE "+s2+s3+" AND "+data+gr[4]; break;
		case 7: s=se[4]+fr[1]+" WHERE "+s1+" AND "+s2+s3+" AND "+data+gr[4]; break;
		default: break;
	}
	dmod1->ADOQ_en->Close();
	dmod1->ADOQ_en->SQL->Text=s;
	dmod1->ADOQ_en->Open();
	if (dmod1->ADOQ_en->RecordCount)
	{
		ProgressBar1->Visible=true;
		ProgressBar1->Position+=5;
		try
		{
			vVarApp=CreateOleObject("Excel.Application");
		}
		catch(...)
		{
			MessageBoxA(0,"Ошибка при открытии сервера Excel","Ошибка",MB_OK);
			Abort();
		}

		list = dmod1->ADOQ_en->RecordCount;
		if (list>10)
		list=10;
		vVarApp.OlePropertySet("SheetsInNewWorkbook",list+1);
		vVarApp.OlePropertyGet("Workbooks").OleProcedure("Add");
		ProgressBar1->Position+=15;
		graf_en();
		vVarApp.OlePropertySet("Visible",true);

		vVarCell.Clear();
		vVarCell = Unassigned;
		vVarCell = NULL;

		vVarSheet.Clear();
		vVarSheet = Unassigned;
		vVarSheet = NULL;

		vVarApp.Clear();
		vVarApp = Unassigned;
		vVarApp = NULL;
		ProgressBar1->Position=0;
		ProgressBar1->Visible=false;
	}
	else
	ShowMessage("В этом диапазоне нет популярных продуктов");
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::graf_en()
{
	AnsiString str;
	int g,k;
	vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
	vVarSheet=vVarSheets.OlePropertyGet("Item",1);
	vVarSheet.OlePropertySet("Name",WideString("Динамика"));
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:D1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",40);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("Value",WideString("Динамика цен самых популярных продуктов с "+DateToStr(Form_gl->DateTimePicker_n->Date)+" по "+DateToStr(Form_gl->DateTimePicker_k->Date)));
	vVarCell.OlePropertySet("WrapText",true);
	vVarCell.OlePropertySet("RowHeight",40);
	vVarCell.OlePropertySet("MergeCells",true);

	for (k = 1; k <= 4; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		switch (k)
		{
			case 1: str="№ П/П";break;
			case 2: str="Продукт";vVarCell.OlePropertySet("ColumnWidth",35);break;
			case 3: str="Сумма";vVarCell.OlePropertySet("ColumnWidth",15);break;
			case 4: str="Кол.пок.";break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
	}
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A2:D2"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

	dmod1->ADOQ_en->Close();
	dmod1->ADOQ_en->Open();
	dmod1->ADOQ_en->First();

	Variant A(OPENARRAY(int,(0,dmod1->ADOQ_en->RecordCount,0,4)),varVariant);

	int ss=0; int cc=0;
	for (g = 1; g <= dmod1->ADOQ_en->RecordCount; g++)
	{
		for (k = 1; k <= 4; k++)
		{
			switch (k)
			{
				case 1: str=IntToStr(g);break;
				case 2: str=dmod1->ADOQ_en->FieldByName("name_prod")->AsAnsiString;break;
				case 3: str=dmod1->ADOQ_en->FieldByName("Sum-cena_tr")->AsAnsiString; ss+=dmod1->ADOQ_en->FieldByName("Sum-cena_tr")->AsInteger; break;
				case 4: str=dmod1->ADOQ_en->FieldByName("Count-name_prod")->AsAnsiString; cc+=dmod1->ADOQ_en->FieldByName("Count-name_prod")->AsInteger; break;
				default:break;
			}
			A.PutElement(str,g-1,k-1);
		}
		dmod1->ADOQ_en->Next();
	}
	WideString CellA;
	CellA = "A3:D"+IntToStr(2+dmod1->ADOQ_en->RecordCount);
	Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
	MR.OlePropertySet("Value",A);

	CellA="A"+IntToStr(3+dmod1->ADOQ_en->RecordCount)+":B"+IntToStr(3+dmod1->ADOQ_en->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertySet("Value",WideString("ВСЕГО:"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	for (k = 3; k <= 4; k++)
	{
		switch (k)
		{
			case 3: str=IntToStr(ss);break;
			case 4: str=IntToStr(cc);break;
			default:break;
		}
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",3+dmod1->ADOQ_en->RecordCount,k);
		vVarCell.OlePropertySet("Value",WideString(str));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	}
	CellA="A1:D"+IntToStr(3+dmod1->ADOQ_en->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Italic",true);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("B:C"));
	vVarCell.OlePropertySet("HorizontalAlignment",-4131);
	ProgressBar1->Position+=30;

	dmod1->ADOQ_en->First();
	for (i_inf = 1; i_inf <= 10; i_inf++)
	{
		ProgressBar1->Position+=Int(50/list);
        switch (flag_ovp)
		{
			case 0: s=se[5]+fr[1]+" WHERE "+data+" AND (prod.name_prod = "+QuotedStr(dmod1->ADOQ_en->FieldByName("name_prod")->AsAnsiString)+") "+gr[5]; break;
			case 1: s=se[5]+fr[4]+" WHERE "+s1+" AND (prod.name_prod = "+QuotedStr(dmod1->ADOQ_en->FieldByName("name_prod")->AsAnsiString)+") "+" AND "+data+gr[5]; break;
			case 2: s=se[5]+fr[1]+" WHERE "+s2+" AND (prod.name_prod = "+QuotedStr(dmod1->ADOQ_en->FieldByName("name_prod")->AsAnsiString)+") "+" AND "+data+gr[5]; break;
			case 3: s=se[5]+fr[1]+" WHERE "+s1+" AND "+s2+" AND (prod.name_prod = "+QuotedStr(dmod1->ADOQ_en->FieldByName("name_prod")->AsAnsiString)+") "+" AND "+data+gr[5]; break;
			case 6: s=se[5]+fr[1]+" WHERE "+s2+s3+" AND (prod.name_prod = "+QuotedStr(dmod1->ADOQ_en->FieldByName("name_prod")->AsAnsiString)+") "+" AND "+data+gr[5]; break;
			case 7: s=se[5]+fr[1]+" WHERE "+s1+" AND "+s2+s3+" AND (prod.name_prod = "+QuotedStr(dmod1->ADOQ_en->FieldByName("name_prod")->AsAnsiString)+") "+" AND "+data+gr[5]; break;
			default: break;
		}
		dmod1->ADOQ_inf->Close();
		dmod1->ADOQ_inf->SQL->Text=s;
		if(!dmod1->ADOQ_en->Eof)
		graf_inf(dmod1->ADOQ_en->FieldByName("name_prod")->AsAnsiString);
		dmod1->ADOQ_en->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_it::graf_inf(const AnsiString& inf_prod)
{
	AnsiString str;
	int g,k;
	vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
	vVarSheet=vVarSheets.OlePropertyGet("Item",i_inf+1);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:E1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",24);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",12);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("RowHeight",45);
	vVarCell.OlePropertySet("Value",WideString("Статистика покупок продукта "+inf_prod+" c "+DateToStr(Form_gl->DateTimePicker_n->Date)+" по "+DateToStr(Form_gl->DateTimePicker_k->Date)));
	vVarCell.OlePropertySet("WrapText",true);
	for (k = 1; k <= 5; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		switch (k)
		{
			case 1: str="№ П/П";break;
			case 2: str="Дата покупки";vVarCell.OlePropertySet("ColumnWidth",30);break;
			case 3: str="Рублей";vVarCell.OlePropertySet("ColumnWidth",10);break;
			case 4: str="Кол/Ед";vVarCell.OlePropertySet("ColumnWidth",15);break;
			case 5: str="Магазин";vVarCell.OlePropertySet("ColumnWidth",25);break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
	}
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A2:E2"));
	vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

	dmod1->ADOQ_inf->Close();
	dmod1->ADOQ_inf->Open();
	dmod1->ADOQ_inf->First();

	Variant A(OPENARRAY(int,(0,dmod1->ADOQ_inf->RecordCount,0,5)),varVariant);

	for (g = 1; g <= dmod1->ADOQ_inf->RecordCount; g++)
	{
		for (k = 1; k <= 5; k++)
		{
			switch (k)
			{
				case 1: str=IntToStr(g);break;
				case 2: str=FormatDateTime("dddddd",dmod1->ADOQ_inf->FieldByName("data_tr")->AsDateTime);str=strtok(str.c_str(),"/");break;
				case 3: str=dmod1->ADOQ_inf->FieldByName("cena_tr")->AsAnsiString;break;
				case 4: str=dmod1->ADOQ_inf->FieldByName("kol_ed_tr")->AsAnsiString;break;
				case 5: str=dmod1->ADOQ_inf->FieldByName("name_org")->AsAnsiString;break;
				default:break;
			}
			A.PutElement(str,g-1,k-1);
		}
		dmod1->ADOQ_inf->Next();
	}
	WideString CellA;
	CellA = "A3:E"+IntToStr(2+dmod1->ADOQ_inf->RecordCount);
	Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
	MR.OlePropertySet("Value",A);

	CellA="A1:E"+IntToStr(2+dmod1->ADOQ_inf->RecordCount);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Italic",true);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	ProgressBar1->Position+=1;
	try
	{
		CellA="B3:C"+IntToStr(2+dmod1->ADOQ_inf->RecordCount);
		Variant Chart = vVarApp.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Charts").OleFunction("Add");
		Chart.OlePropertySet("ChartType",51);
		Chart.OleProcedure("SetSourceData",vVarSheet.OlePropertyGet("Range",WideString(CellA)),2);
		Chart.OlePropertyGet("SeriesCollection",1).OlePropertySet("Name",WideString("Сумма"));
		Chart.OlePropertyGet("ChartTitle").OlePropertySet("Text",WideString("Дни"));
		Chart.OleProcedure("Location",2,vVarSheet.OlePropertyGet("Name"));
	}
	catch(...)
	{
		MessageBoxA(0,"Ваша версия MS Excel не позволяет строить графики командами Builder C++","Ошибка", MB_OK);
		return;
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm_it::excel_exp()
{
	Word dayl,monl,yearl;
	DecodeDate(Date(),yearl,monl,dayl);
	AnsiString dat_l="#"+IntToStr(monl)+"/"+IntToStr(dayl)+"/"+IntToStr(yearl)+"#";

	s=se[2]+fr[3]+" WHERE (trati.data_tr="+dat_l+")"+gr[2];
	dmod1->q->Close();
	dmod1->q->SQL->Text=s;
	dmod1->q->Open();

	if(dmod1->q->RecordCount)
	{
		try
		{
			vVarApp=CreateOleObject("Excel.Application");
		}
		catch(...)
		{
			MessageBoxA(0,"Ошибка при открытии сервера Excel","Ошибка",MB_OK);
			Abort();
		}

		AnsiString str;
		int g,k,m=0;
		vVarApp.OlePropertySet("SheetsInNewWorkbook",1);
		vVarApp.OlePropertyGet("Workbooks").OleProcedure("Add");
		vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
		vVarSheet=vVarSheets.OlePropertyGet("Item",1);

		vVarSheet.OlePropertySet("Name",WideString("Продукты"));
		vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:E1"));
		vVarCell.OleProcedure("Merge");
		vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
		vVarCell.OlePropertyGet("Interior").OlePropertySet("Color",clLime);
		vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
		vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
		vVarCell.OlePropertySet("RowHeight",25);
		vVarCell.OlePropertySet("Value",WideString("Итоги покупок за сегодня"));
		for (k = 1; k <= 5; k++)
		{
			vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
			switch (k)
			{
				case 1: str="№ П/П";break;
				case 2: str="Продукт";vVarCell.OlePropertySet("ColumnWidth",35);break;
				case 3: str="Рублей";break;
				case 4: str="Кол.пок.";break;
				case 5: str="Магазин";vVarCell.OlePropertySet("ColumnWidth",25);break;
				default:break;
			}
			vVarCell.OlePropertySet("Value",WideString(str));
		}
		vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A2:E2"));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

		dmod1->q->First();

		Variant A(OPENARRAY(int,(0,dmod1->q->RecordCount,0,5)),varVariant);

		for (g = 1; g <= dmod1->q->RecordCount; g++)
		{
			for (k = 1; k <= 5; k++)
			{
				s="SELECT name_org "+fr[1]+" WHERE (trati.data_tr="+dat_l+")"+"AND (prod.name_prod = "+QuotedStr(dmod1->q->FieldByName("name_prod")->AsAnsiString)+")"+" GROUP BY name_org ";
				dmod1->ADOQ_del->Close();
				dmod1->ADOQ_del->SQL->Text=s;
				dmod1->ADOQ_del->Open();

				switch (k)
				{
					case 1: str=IntToStr(g);break;
					case 2: str=dmod1->q->FieldByName("name_prod")->AsAnsiString;break;
					case 3: str=dmod1->q->FieldByName("Sum-cena_tr")->AsAnsiString;break;
					case 4: str=dmod1->q->FieldByName("Count-name_prod")->AsAnsiString; m+=dmod1->q->FieldByName("Count-name_prod")->AsInteger;break;
					case 5: str=(dmod1->ADOQ_del->RecordCount>1)?dmod1->ADOQ_del->FieldByName("name_org")->AsAnsiString+"...":dmod1->ADOQ_del->FieldByName("name_org")->AsAnsiString;break;
					default:break;
				}
				A.PutElement(str,g-1,k-1);
			}
			dmod1->q->Next();
		}
		WideString CellA;
		CellA = "A3:E"+IntToStr(2+dmod1->q->RecordCount);
		Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
		MR.OlePropertySet("Value",A);

		CellA="A"+IntToStr(3+dmod1->q->RecordCount)+":B"+IntToStr(3+dmod1->q->RecordCount);
		vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
		vVarCell.OleProcedure("Merge");
		vVarCell.OlePropertySet("Value",WideString("ВСЕГО:"));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
		for (k = 3; k <= 5; k++)
		{
			switch (k)
			{
				case 3: str=Form_trativ->sum_trd->Caption;break;
				case 4: str=IntToStr(m);break;
				case 5: str="";break;
				default:
				break;
			}
			vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",3+dmod1->q->RecordCount,k);
			vVarCell.OlePropertySet("Value",WideString(str));
			vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
		}
		CellA="A1:E"+IntToStr(3+dmod1->q->RecordCount);
		vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
		vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
		vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
		vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
		vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
		vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
		vVarCell.OlePropertyGet("Font").OlePropertySet("Italic",true);
		vVarCell.OlePropertySet("VerticalAlignment",-4108);
		vVarCell.OlePropertySet("HorizontalAlignment",-4108);

		vVarCell=vVarSheet.OlePropertyGet("Range",WideString("B:C"));
		vVarCell.OlePropertySet("HorizontalAlignment",-4131);
		vVarApp.OlePropertySet("Visible",true);

		vVarCell.Clear();
		vVarCell = Unassigned;
		vVarCell = NULL;

		vVarSheet.Clear();
		vVarSheet = Unassigned;
		vVarSheet = NULL;

		vVarApp.Clear();
		vVarApp = Unassigned;
		vVarApp = NULL;
		vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:A1"));
		vVarCell.OleProcedure("Select");
	}
	else
	ShowMessage("Сегодня не было покупок!");
}
//---------------------------------------------------------------------------
//*************************расчет денег**************************************
void __fastcall TForm_it::pr_tr0(const int& m)
{
	dmod1->q->Close();
	dmod1->q->SQL->Text=pr_tr[0];
	dmod1->q->Open();

	std::list<int> lkgod;
	while(!dmod1->q->Eof)
	{
		lkgod.push_back(dmod1->q->FieldByName("m")->AsInteger);
		dmod1->q->Next();
	}

	dmod1->q->Close();
	dmod1->q->SQL->Text=pr_tr[2];
	dmod1->q->Open();

	std::list<int> lkgod_tr;
	while(!dmod1->q->Eof)
	{
		lkgod_tr.push_back(dmod1->q->FieldByName("m")->AsInteger);
		dmod1->q->Next();
	}

	lkgod.merge(lkgod_tr);
	lkgod.unique();

	dmod1->q->Close();
	dmod1->q->SQL->Text=pr_tr[1];
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text=pr_tr[3];

    std::list<int>::iterator pkgod;
	pkgod=lkgod.begin();
	while(pkgod!=lkgod.end())
	{
		dmod1->q->Close();
		dmod1->q->Parameters->ParamByName("y")->Value=IntToStr(*pkgod);
		dmod1->q->Open();

		dmod1->ADOQ_del->Close();
		dmod1->ADOQ_del->Parameters->ParamByName("y")->Value=IntToStr(*pkgod);
		dmod1->ADOQ_del->Open();

		int kol_mes=0;
		int mes=1;
		while(mes<13)
		{
			if(mes==dmod1->q->FieldByName("data")->AsInteger&&mes==dmod1->ADOQ_del->FieldByName("data")->AsInteger)
			{
				stat* st = new stat(*pkgod,mes,dmod1->q->FieldByName("m")->AsInteger,dmod1->ADOQ_del->FieldByName("m")->AsInteger);
				vstat.push_back(st);
				dmod1->q->Next();
				dmod1->ADOQ_del->Next();
				++kol_mes;
			}
			else if(mes==dmod1->q->FieldByName("data")->AsInteger&&mes!=dmod1->ADOQ_del->FieldByName("data")->AsInteger)
			{
				stat* st = new stat(*pkgod,mes,Int(dmod1->q->FieldByName("m")->AsInteger),0);
				vstat.push_back(st);
				dmod1->q->Next();
				++kol_mes;
			}
			else if(mes!=dmod1->q->FieldByName("data")->AsInteger&&mes==dmod1->ADOQ_del->FieldByName("data")->AsInteger)
			{
				stat* st = new stat(*pkgod,mes,0,dmod1->ADOQ_del->FieldByName("m")->AsInteger);
				vstat.push_back(st);
				dmod1->ADOQ_del->Next();
				++kol_mes;
			}
			++mes;
		}
		++pkgod;
	}

	if(vstat.empty())
	ShowMessage("Нет данных!");
	else if(m==1)
	pr_tr1();
	else if(m==2)
	pr_tr2();
	else
	pr_tr3();
}
void __fastcall TForm_it::pr_tr1()
{
	AnsiString str;
	const char* mes[]={"Январь","Ферваль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
    try
	{
		vVarApp = CreateOleObject("Excel.Application");

		vVarApp.OlePropertySet("SheetsInNewWorkbook",1);
		vVarApp.OlePropertyGet("Workbooks").OleProcedure("Add");
		vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
		vVarSheet=vVarSheets.OlePropertyGet("Item",1);
	}
	catch(...)
	{
		MessageBoxA(0,"Ошибка при запуске Microsoft Excel!","Ошибка", MB_OK);
		Abort();
	}

	vVarSheet.OlePropertySet("Name",WideString("Деньги"));
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:B1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("TintAndShade",0.599993896298105);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("RowHeight",25);
	vVarCell.OlePropertySet("Value",WideString("Итоговая ведомость дохода"));
	for (int k = 1; k <= 2; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		switch (k)
		{
			case 1: str="Месяц";vVarCell.OlePropertySet("ColumnWidth",20);break;
			case 2: str="Доход";vVarCell.OlePropertySet("ColumnWidth",20);break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	}

	int god=0;
	int step=3;
	int m1=0;
	pstat=vstat.begin();
	while(pstat!=vstat.end())
	{
		if(god!=(*pstat)->get_god())
		{
			god=(*pstat)->get_god();

			vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A"+IntToStr(step))+":B"+IntToStr(step));
			vVarCell.OleProcedure("Merge");
			vVarCell.OlePropertyGet("Font").OlePropertySet("Bold",1);
			vVarCell.OlePropertyGet("Font").OlePropertySet("Size",13);
			vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
			vVarCell.OlePropertySet("RowHeight",18);
			vVarCell.OlePropertySet("Value",WideString("За "+IntToStr(god)+" год"));
			step++;
		}

		Variant A(OPENARRAY(int,(0,1,0,2)),varVariant);

		for (int k = 1; k <= 2; k++)
		{
			switch (k)
			{
				case 1: str=mes[(*pstat)->get_mes()-1];break;
				case 2: str=IntToStr((*pstat)->get_zp());m1+=(*pstat)->get_zp();break;
				default:break;
			}
			A.PutElement(str,0,k-1);
		}
        WideString CellA;
		CellA = "A"+IntToStr(step)+":B"+IntToStr(step);
		Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
		MR.OlePropertySet("Value",A);
		step++;
		
		delete 	*pstat++;
		if(pstat==vstat.end()||god!=(*pstat)->get_god())
		{
			Variant A(OPENARRAY(int,(0,1,0,2)),varVariant);

			for (int k = 1; k <= 2; k++)
			{
				switch (k)
				{
					case 1: str="Итого:";break;
					case 2: str=IntToStr(m1);break;
					default:break;
				}
				A.PutElement(str,0,k-1);
			}m1=0;

			WideString CellA;
			CellA = "A"+IntToStr(step)+":B"+IntToStr(step);
			Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
			MR.OlePropertySet("Value",A);

			vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A"+IntToStr(step)+":B"+IntToStr(step)));
			vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

			++step;
		}
	}

	vstat.clear();

	WideString CellA;
	CellA="A1:B"+IntToStr(--step);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:B2"));
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:A1"));
	vVarCell.OleProcedure("Select");

	vVarApp.OlePropertySet("Visible",1);

	vVarCell.Clear();
	vVarCell = Unassigned;
	vVarCell = NULL;

	vVarSheet.Clear();
	vVarSheet = Unassigned;
	vVarSheet = NULL;

	vVarApp.Clear();
	vVarApp = Unassigned;
	vVarApp = NULL;
}
void __fastcall TForm_it::pr_tr2()
{
	AnsiString str;
	const char* mes[]={"Январь","Ферваль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
    try
	{
		vVarApp = CreateOleObject("Excel.Application");

		vVarApp.OlePropertySet("SheetsInNewWorkbook",1);
		vVarApp.OlePropertyGet("Workbooks").OleProcedure("Add");
		vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
		vVarSheet=vVarSheets.OlePropertyGet("Item",1);
	}
	catch(...)
	{
		MessageBoxA(0,"Ошибка при запуске Microsoft Excel!","Ошибка",MB_OK);
		Abort();
	}

	vVarSheet.OlePropertySet("Name",WideString("Деньги"));
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:B1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("TintAndShade",0.599993896298105);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("RowHeight",25);
	vVarCell.OlePropertySet("Value",WideString("Итоговая ведомость трат"));
	for (int k = 1; k <= 2; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		switch (k)
		{
			case 1: str="Месяц";vVarCell.OlePropertySet("ColumnWidth",20);break;
			case 2: str="Траты";vVarCell.OlePropertySet("ColumnWidth",20);break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	}

	int god=0;
	int step=3;
	int m1=0;
	pstat=vstat.begin();
	while(pstat!=vstat.end())
	{
		if(god!=(*pstat)->get_god())
		{
			god=(*pstat)->get_god();

			vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A"+IntToStr(step))+":B"+IntToStr(step));
			vVarCell.OleProcedure("Merge");
			vVarCell.OlePropertyGet("Font").OlePropertySet("Bold",1);
			vVarCell.OlePropertyGet("Font").OlePropertySet("Size",13);
			vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
			vVarCell.OlePropertySet("RowHeight",18);
			vVarCell.OlePropertySet("Value",WideString("За "+IntToStr(god)+" год"));
			step++;
		}

		Variant A(OPENARRAY(int,(0,1,0,2)),varVariant);

		for (int k = 1; k <= 2; k++)
		{
			switch (k)
			{
				case 1: str=mes[(*pstat)->get_mes()-1];break;
				case 2: str=IntToStr((*pstat)->get_tr());m1+=(*pstat)->get_tr();break;
				default:break;
			}
			A.PutElement(str,0,k-1);
		}
        WideString CellA;
		CellA = "A"+IntToStr(step)+":B"+IntToStr(step);
		Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
		MR.OlePropertySet("Value",A);
		++step;

		delete 	*pstat++;
		if(pstat==vstat.end()||god!=(*pstat)->get_god())
		{
			Variant A(OPENARRAY(int,(0,1,0,2)),varVariant);

			for (int k = 1; k <= 2; k++)
			{
				switch (k)
				{
					case 1: str="Итого:";break;
					case 2: str=IntToStr(m1);break;
					default:break;
				}
				A.PutElement(str,0,k-1);
			}m1=0;

			WideString CellA;
			CellA = "A"+IntToStr(step)+":B"+IntToStr(step);
			Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
			MR.OlePropertySet("Value",A);

			vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A"+IntToStr(step)+":B"+IntToStr(step)));
			vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

			++step;
		}
	}

	vstat.clear();

	WideString CellA;
	CellA="A1:B"+IntToStr(--step);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:B2"));
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:A1"));
	vVarCell.OleProcedure("Select");

	vVarApp.OlePropertySet("Visible",1);

	vVarCell.Clear();
	vVarCell = Unassigned;
	vVarCell = NULL;

	vVarSheet.Clear();
	vVarSheet = Unassigned;
	vVarSheet = NULL;

	vVarApp.Clear();
	vVarApp = Unassigned;
	vVarApp = NULL;
}
void __fastcall TForm_it::pr_tr3()
{
	AnsiString str;
	const char* mes[]={"Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
    try
	{
		vVarApp = CreateOleObject("Excel.Application");

		vVarApp.OlePropertySet("SheetsInNewWorkbook",1);
		vVarApp.OlePropertyGet("Workbooks").OleProcedure("Add");
		vVarSheets=vVarApp.OlePropertyGet("Workbooks").OlePropertyGet("Item",1).OlePropertyGet("Worksheets");
		vVarSheet=vVarSheets.OlePropertyGet("Item",1);
	}
	catch(...)
	{
		MessageBoxA(0,"Ошибка при запуске Microsoft Excel!","Ошибка",MB_OK);
		Abort();
	}

	vVarSheet.OlePropertySet("Name",WideString("Деньги"));
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:E1"));
	vVarCell.OleProcedure("Merge");
	vVarCell.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	vVarCell.OlePropertyGet("Interior").OlePropertySet("TintAndShade",0.599993896298105);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Size",14);
	vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
	vVarCell.OlePropertySet("RowHeight",25);
	vVarCell.OlePropertySet("Value",WideString("Итоговая ведомость "));
	for (int k = 1; k <= 5; k++)
	{
		vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",2,k);
		vVarCell.OlePropertySet("ColumnWidth",15);
		switch (k)
		{
			case 1: str="Месяц";break;
			case 2: str="Доход";break;
			case 3: str="Траты";break;
			case 4: str="Остаток";break;
			case 5: str="Капитализация";break;
			default:break;
		}
		vVarCell.OlePropertySet("Value",WideString(str));
		vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);
	}

	int god=0;
	int step=3;
	int m1,m2,m3,m4;
	m1=m2=m3=m4=0;
	pstat=vstat.begin();
	while(pstat!=vstat.end())
	{
		if(god!=(*pstat)->get_god())
		{
			god=(*pstat)->get_god();

			vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A"+IntToStr(step))+":E"+IntToStr(step));
			vVarCell.OleProcedure("Merge");
			vVarCell.OlePropertyGet("Font").OlePropertySet("Bold",1);
			vVarCell.OlePropertyGet("Font").OlePropertySet("Size",13);
			vVarCell.OlePropertyGet("Font").OlePropertySet("Name",WideString("Verdana"));
			vVarCell.OlePropertySet("RowHeight",18);
			vVarCell.OlePropertySet("Value",WideString("За "+IntToStr(god)+" год"));
			step++;
		}

		Variant A(OPENARRAY(int,(0,1,0,5)),varVariant);

		for (int k = 1; k <= 5; k++)
		{
			switch (k)
			{
				case 1: str=mes[(*pstat)->get_mes()-1];
				break;

				case 2: str=IntToStr((*pstat)->get_zp());
						m1+=(*pstat)->get_zp();
				break;

				case 3: str=IntToStr((*pstat)->get_tr());
						m2+=(*pstat)->get_tr();
				break;

				case 4: str=IntToStr((*pstat)->get_zp()-(*pstat)->get_tr());
						m3+=(*pstat)->get_zp()-(*pstat)->get_tr();
				break;

				case 5: m4+=(*pstat)->get_zp()-(*pstat)->get_tr();
						str=IntToStr(m4);
				break;

				default:break;
			}
			A.PutElement(str,0,k-1);
		}
		WideString CellA;
		CellA = "A"+IntToStr(step)+":E"+IntToStr(step);
		Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
		MR.OlePropertySet("Value",A);
		++step;

		delete 	*pstat++;
		if(pstat==vstat.end()||god!=(*pstat)->get_god())
		{
			Variant A(OPENARRAY(int,(0,1,0,5)),varVariant);

			for (int k = 1; k <= 5; k++)
			{
				switch (k)
				{
					case 1: str="Итого:";break;
					case 2: str=IntToStr(m1);break;
					case 3: str=IntToStr(m2);break;
					case 4: str=IntToStr(m3);break;
					case 5: str=IntToStr(m4);break;
					default:break;
				}
				A.PutElement(str,0,k-1);
			}
			m1=m2=m3=0;

			WideString CellA;
			CellA = "A"+IntToStr(step)+":E"+IntToStr(step);
			Variant MR = vVarSheet.OlePropertyGet("Range",WideString(CellA));
			MR.OlePropertySet("Value",A);

			vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A"+IntToStr(step)+":E"+IntToStr(step)));
			vVarCell.OlePropertyGet("Interior").OlePropertySet("ColorIndex",15);

			++step;
		}
	}

	vstat.clear();

	WideString CellA;
	CellA="A1:E"+IntToStr(--step);
	vVarCell=vVarSheet.OlePropertyGet("Range",WideString(CellA));
	vVarCell.OlePropertyGet("Borders").OlePropertySet("LineStyle",1);
	vVarCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",-4138);
	vVarCell.OlePropertySet("VerticalAlignment",-4108);
	vVarCell.OlePropertySet("HorizontalAlignment",-4108);

	vVarCell=vVarSheet.OlePropertyGet("Range",WideString("A1:A1"));
	vVarCell.OleProcedure("Select");

	vVarApp.OlePropertySet("Visible",1);

	vVarCell.Clear();
	vVarCell = Unassigned;
	vVarCell = NULL;

	vVarSheet.Clear();
	vVarSheet = Unassigned;
	vVarSheet = NULL;

	vVarApp.Clear();
	vVarApp = Unassigned;
	vVarApp = NULL;

//	vVarCell=vVarSheet.OlePropertyGet("Cells").OlePropertyGet("Item",29,1);
//	vVarCell.OlePropertySet("Formula",WideString("=СУММ(B4:B10)")) ;
}
