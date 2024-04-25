//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_prodv.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_prod.h"
#include "f_trativ.h"
#include "f_trati.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_prodv *Form_prodv;
//---------------------------------------------------------------------------
__fastcall TForm_prodv::TForm_prodv(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::ToolButton2Click(TObject *Sender)
{
	Form_trativ->f_prod=0;
	if (!Form_prod)
	{
		Application->CreateForm(__classid(TForm_prod), &Form_prod);
		Form_prod->ShowModal();
	}
	else
	{
		if (IsIconic(Form_prod->Handle))
		Form_prod->WindowState = wsNormal;
		Form_prod->ShowModal();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::ToolButton4Click(TObject *Sender)
{
	if (ToolButton4->Enabled)
	{
		Form_trativ->f_prod=1;
		if (!Form_prod)
		{
			Application->CreateForm(__classid(TForm_prod), &Form_prod);
			Form_prod->ShowModal();
		}
		else
		{
			if (IsIconic(Form_prod->Handle))
			Form_prod->WindowState = wsNormal;
			Form_prod->ShowModal();
		}
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::ToolButton5Click(TObject *Sender)
{
    if (ToolButton4->Enabled)
	if(MessageBoxA(0,"Вы действительно хотите удалить выбранную запись?","Подтверждение",MB_OKCANCEL)==IDOK)
	{
		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT count(*) as m FROM trati WHERE kod_prod_tr = "+IntToStr(dmod1->q_prod->FieldByName("kod_prod")->AsInteger);
		dmod1->q->Open();
		if(dmod1->q->FieldByName("m")->AsInteger != 0) {
			ShowMessage("Нельзя удалить эту запись т.к. есть связанные записи в таблице Траты!");
		}
		else
		{
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text="DELETE FROM prod WHERE kod_prod = "+IntToStr(dmod1->q_prod->FieldByName("kod_prod")->AsInteger)+";";
			dmod1->ADOQ_Work->ExecSQL();
			FormShow(Sender);
			if(Form_trati)
			{
				int n_prod=Form_trati->id_prod[Form_trati->n_prod->ItemIndex];
				Form_trati->n_prod_vidChange(Sender);
				Form_trati->n_prod->ItemIndex=find(Form_trati->id_prod.begin(),Form_trati->id_prod.end(),n_prod)-Form_trati->id_prod.begin();
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::ToolButton7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_prodv = NULL;
	Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::Edit1Change(TObject *Sender)
{
	dmod1->q_prod->Close();
	dmod1->q_prod->Parameters->ParamByName("prod_vid")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_prod->Parameters->ParamByName("prod")->Value=Trim(Edit2->Text)+"%";
	dmod1->q_prod->Open();
	if (dmod1->q_prod->RecordCount)
	{
		ToolButton4->Enabled=true;
		ToolButton5->Enabled=true;
	}
	else
	{
		ToolButton4->Enabled=false;
		ToolButton5->Enabled=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
switch (Key)
	{
		case VK_ESCAPE: Close(); break;
		case VK_INSERT: ToolButton2->Click(); break;
		case VK_RETURN: ToolButton4->Click(); break;
		case VK_DELETE: ToolButton5->Click(); break;
		case VK_SPACE: {Edit1->Text="";Edit2->Text="";} break;
		default: break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::FormShow(TObject *Sender)
{
	dmod1->q_prod->Close();
	dmod1->q_prod->Parameters->ParamByName("prod_vid")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_prod->Parameters->ParamByName("prod")->Value=Trim(Edit2->Text)+"%";
	dmod1->q_prod->Open();
	if (dmod1->q_prod->RecordCount)
	{
		ToolButton4->Enabled=true;
		ToolButton5->Enabled=true;
	}
	else
	{
		ToolButton4->Enabled=false;
		ToolButton5->Enabled=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::DBGrid1DblClick(TObject *Sender)
{
	ToolButton4Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodv::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
	if (State.Contains(gdSelected))
	{
		DBGrid1->Canvas->Brush->Color  = clWebLightCoral;
		DBGrid1->Canvas->Font->Color  = clBlack;
	}

	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
}
//---------------------------------------------------------------------------

