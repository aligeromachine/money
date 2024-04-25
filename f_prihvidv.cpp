//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_prihvidv.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_prihvid.h"
#include "f_trativ.h"
#include "f_prih.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_prihvidv *Form_prihvidv;
//---------------------------------------------------------------------------
__fastcall TForm_prihvidv::TForm_prihvidv(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihvidv::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_prihvidv = NULL;
	Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihvidv::ToolButton7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihvidv::ToolButton2Click(TObject *Sender)
{
	Form_trativ->f_prihvid=0;
	if (!Form_prihvid)
	{
		Application->CreateForm(__classid(TForm_prihvid), &Form_prihvid);
		Form_prihvid->ShowModal();
	}
	else
	{
		if (IsIconic(Form_prihvid->Handle))
		Form_prihvid->WindowState = wsNormal;
		Form_prihvid->ShowModal();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihvidv::ToolButton4Click(TObject *Sender)
{
	if (ToolButton4->Enabled)
	{
		Form_trativ->f_prihvid=1;
		if (!Form_prihvid)
		{
			Application->CreateForm(__classid(TForm_prihvid), &Form_prihvid);
			Form_prihvid->ShowModal();
		}
		else
		{
			if (IsIconic(Form_prihvid->Handle))
			Form_prihvid->WindowState = wsNormal;
			Form_prihvid->ShowModal();
		}
    }
}
void __fastcall TForm_prihvidv::ToolButton5Click(TObject *Sender)
{
    if (ToolButton4->Enabled)
	if(MessageBoxA(0,"Вы действительно хотите удалить выбранную запись?","Подтверждение",MB_OKCANCEL)==IDOK)
	{
		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT count(*) as m FROM prih WHERE kod_prih_vid_v = "+IntToStr(dmod1->q_prihvid->FieldByName("kod_prih_vid")->AsInteger);
		dmod1->q->Open();
		if(dmod1->q->FieldByName("m")->AsInteger != 0) {
			ShowMessage("Нельзя удалить эту запись т.к. есть связанные записи в таблице Прибыль!");
		}
		else
		{
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text="DELETE FROM prih_vid WHERE kod_prih_vid = "+IntToStr(dmod1->q_prihvid->FieldByName("kod_prih_vid")->AsInteger)+";";
			dmod1->ADOQ_Work->ExecSQL();
			FormShow(Sender);
			if(Form_prih)
			{
				int prih = Form_prih->id_prihvid[Form_prih->n_prihvid->ItemIndex];
				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT * FROM prih_vid ORDER BY name_prih_vid";
				dmod1->q->Open();
				Form_prih->n_prihvid->Clear();
				Form_prih->id_prihvid.clear();
				while (!dmod1->q->Eof)
				{
					Form_prih->n_prihvid->Items->Add(dmod1->q->FieldByName("name_prih_vid")->AsAnsiString);
					Form_prih->id_prihvid.push_back(dmod1->q->FieldByName("kod_prih_vid")->AsInteger);
					dmod1->q->Next();
				}
				Form_prih->n_prihvid->ItemIndex=find(Form_prih->id_prihvid.begin(),Form_prih->id_prihvid.end(),prih)-Form_prih->id_prihvid.begin();
			}
		}
	}
}
void __fastcall TForm_prihvidv::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
void __fastcall TForm_prihvidv::FormShow(TObject *Sender)
{
	dmod1->q_prihvid->Close();
	dmod1->q_prihvid->Open();
	if (dmod1->q_prihvid->RecordCount)
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
void __fastcall TForm_prihvidv::DBGrid1DblClick(TObject *Sender)
{
	ToolButton4Click(Sender);
}
void __fastcall TForm_prihvidv::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
	if (State.Contains(gdSelected))
	{
		DBGrid1->Canvas->Brush->Color  = clWebLightCoral;
		DBGrid1->Canvas->Font->Color  = clBlack;
	}

	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
}
