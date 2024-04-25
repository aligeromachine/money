//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_date.h"
#include "f_trativ.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_date *Form_date;
//---------------------------------------------------------------------------
__fastcall TForm_date::TForm_date(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_date::RadioButton1Click(TObject *Sender)
{
	Close();
	AnsiString str1,str2,str3;
	str1=Form_trativ->Edit1->Text;
	str2=Form_trativ->Edit2->Text;
	str3=Form_trativ->Edit3->Text;
	Form_trativ->FormShow(Sender);
	Form_trativ->Edit1->Text=str1;
	Form_trativ->Edit2->Text=str2;
	Form_trativ->Edit3->Text=str3;
	Form_trativ->Edit1Change(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm_date::FormShortCut(TWMKey &Msg, bool &Handled)
{
	if (Msg.CharCode == VK_ESCAPE)
	Close();
}
//---------------------------------------------------------------------------

