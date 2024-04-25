//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_visav.h"
#include "f_gl.h"
#include "f_trativ.h"
#include "f_visa.h"
#include "f_dmod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfr_visav *fr_visav;
//---------------------------------------------------------------------------
__fastcall Tfr_visav::Tfr_visav(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::FormClose(TObject *Sender, TCloseAction &Action)
{
	fr_visav = NULL;
	Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::ToolButton7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::ToolButton2Click(TObject *Sender)
{
	Form_trativ->f_visa=0;
	Application->CreateForm(__classid(Tfr_visa), &fr_visa);
	fr_visa->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::ToolButton4Click(TObject *Sender)
{
	if(ToolButton4->Enabled)
	{
		Form_trativ->f_visa=1;
		Application->CreateForm(__classid(Tfr_visa), &fr_visa);
		fr_visa->ShowModal();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::ToolButton5Click(TObject *Sender)
{
	if (ToolButton4->Enabled)
	if(MessageBoxA(0,"Вы действительно хотите удалить выбранную запись?","Подтверждение",MB_OKCANCEL)==IDOK)
	{
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text="DELETE FROM visa WHERE id_visa = "+IntToStr(dmod1->q_visa->FieldByName("id_visa")->AsInteger)+";";
		dmod1->ADOQ_Work->ExecSQL();
		FormShow(Sender);
		Form_trativ->FormShow(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	switch (Key)
	{
		case VK_ESCAPE: Close(); break;
		case VK_INSERT: ToolButton2->Click(); break;
		case VK_RETURN: ToolButton4->Click(); break;
		case VK_DELETE: ToolButton5->Click(); break;
		default: break;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::DBGrid1DblClick(TObject *Sender)
{
	ToolButton4Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::FormShow(TObject *Sender)
{
	dmod1->q_visa->Close();
	dmod1->q_visa->Open();
	if(dmod1->q_visa->RecordCount)
	{
		ToolButton4->Enabled=1;
		ToolButton5->Enabled=1;
	}
	else
	{
		ToolButton4->Enabled=0;
		ToolButton5->Enabled=0;
	}
	p1->Caption=IntToStr(dmod1->q_visa->RecordCount)+" шт.";
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(visa_s) AS m FROM [visa]";
	dmod1->q->Open();
	p2->Caption=IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" p";
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visav::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
	if(State.Contains(gdSelected))
	{
		DBGrid1->Canvas->Brush->Color  = clWebLightCoral;
		DBGrid1->Canvas->Font->Color  = clBlack;
	}

	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
}
//---------------------------------------------------------------------------
