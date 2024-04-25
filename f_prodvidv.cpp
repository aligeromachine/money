//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_prodvidv.h"
#include "f_dmod.h"
#include "f_prodvid.h"
#include "f_gl.h"
#include "f_trativ.h"
#include "f_trati.h"
#include "f_prod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_prodvidv *Form_prodvidv;
//---------------------------------------------------------------------------
__fastcall TForm_prodvidv::TForm_prodvidv(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodvidv::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_prodvidv = NULL;
	Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodvidv::ToolButton7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodvidv::ToolButton2Click(TObject *Sender)
{
	Form_trativ->f_prodvid=0;
	if(!Form_prodvid)
	{
		Application->CreateForm(__classid(TForm_prodvid), &Form_prodvid);
		Form_prodvid->ShowModal();
	}
	else
	{
		if (IsIconic(Form_prodvid->Handle))
		Form_prodvid->WindowState = wsNormal;
		Form_prodvid->ShowModal();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodvidv::ToolButton4Click(TObject *Sender)
{
	if (ToolButton4->Enabled)
	{
		Form_trativ->f_prodvid=1;
		if(!Form_prodvid)
		{
			Application->CreateForm(__classid(TForm_prodvid), &Form_prodvid);
			Form_prodvid->ShowModal();
		}
		else
		{
			if (IsIconic(Form_prodvid->Handle))
			Form_prodvid->WindowState = wsNormal;
			Form_prodvid->ShowModal();
		}
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodvidv::ToolButton5Click(TObject *Sender)
{
    if (ToolButton4->Enabled)
	if(MessageBoxA(0,"Вы действительно хотите удалить выбранную запись?","Подтверждение",MB_OKCANCEL)==IDOK)
	{
		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT count(*) as m FROM prod WHERE kod_prod_vid_v="+IntToStr(dmod1->q_prodvid->FieldByName("kod_prod_vid")->AsInteger);
		dmod1->q->Open();
		if(dmod1->q->FieldByName("m")->AsInteger != 0) {
			ShowMessage("Нельзя удалить эту запись т.к. есть связанные записи в таблице Продукция!");
		}
		else
		{
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text="DELETE FROM prod_vid WHERE kod_prod_vid = "+IntToStr(dmod1->q_prodvid->FieldByName("kod_prod_vid")->AsInteger)+";";
			dmod1->ADOQ_Work->ExecSQL();
			FormShow(Sender);

			Form_gl->CheckListBox_prodvid_add();

			if(Form_trati)
			{
				int kod_v = Form_trati->id_prodvid[Form_trati->n_prod_vid->ItemIndex];
				int kod_p = Form_trati->id_prod[Form_trati->n_prod->ItemIndex];
				Form_trati->n_prod->Clear();
				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT kod_prod_vid,name_prod_vid FROM prod_vid ORDER BY name_prod_vid";
				dmod1->q->Open();
				Form_trati->n_prod_vid->Clear();
				Form_trati->id_prodvid.clear();
				while (!dmod1->q->Eof)
				{
					Form_trati->n_prod_vid->Items->Add(dmod1->q->FieldByName("name_prod_vid")->AsAnsiString);
					Form_trati->id_prodvid.push_back(dmod1->q->FieldByName("kod_prod_vid")->AsInteger);
					dmod1->q->Next();
				}
				Form_trati->n_prod_vid->ItemIndex=find(Form_trati->id_prodvid.begin(),Form_trati->id_prodvid.end(),kod_v)-Form_trati->id_prodvid.begin();
				Form_trati->n_prod_vidChange(Sender);
				Form_trati->n_prod->ItemIndex=find(Form_trati->id_prod.begin(),Form_trati->id_prod.end(),kod_p)-Form_trati->id_prod.begin();
			}

			if(Form_prod)
			{
				int kod_v4 = Form_prod->id_prodvid[Form_prod->n_prodvid->ItemIndex];
				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT kod_prod_vid,name_prod_vid FROM prod_vid ORDER BY name_prod_vid";
				dmod1->q->Open();
				Form_prod->n_prodvid->Clear();
				Form_prod->id_prodvid.clear();
				while (!dmod1->q->Eof)
				{
					Form_prod->n_prodvid->Items->Add(dmod1->q->FieldByName("name_prod_vid")->AsAnsiString);
					Form_prod->id_prodvid.push_back(dmod1->q->FieldByName("kod_prod_vid")->AsInteger);
					dmod1->q->Next();
				}
				Form_prod->n_prodvid->ItemIndex=find(Form_prod->id_prodvid.begin(),Form_prod->id_prodvid.end(),kod_v4)-Form_prod->id_prodvid.begin();
			}
		}
	}
}
void __fastcall TForm_prodvidv::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
		case VK_ESCAPE: Close(); break;
		case VK_INSERT: ToolButton2->Click(); break;
		case VK_RETURN: ToolButton4->Click(); break;
		case VK_DELETE: ToolButton5->Click(); break;
		case VK_SPACE:  Edit1->Text=""; break;
		default: break;
	}
}
void __fastcall TForm_prodvidv::Edit1Change(TObject *Sender)
{
	dmod1->q_prodvid->Close();
	dmod1->q_prodvid->Parameters->ParamByName("name_prod_vid")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_prodvid->Open();
	if (dmod1->q_prodvid->RecordCount)
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
void __fastcall TForm_prodvidv::FormShow(TObject *Sender)
{
	dmod1->q_prodvid->Close();
	dmod1->q_prodvid->Parameters->ParamByName("name_prod_vid")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_prodvid->Open();
	if (dmod1->q_prodvid->RecordCount)
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
void __fastcall TForm_prodvidv::DBGrid1DblClick(TObject *Sender)
{
	ToolButton4Click(Sender);
}
void __fastcall TForm_prodvidv::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
	if (State.Contains(gdSelected))
	{
		DBGrid1->Canvas->Brush->Color  = clWebLightCoral;
		DBGrid1->Canvas->Font->Color  = clBlack;
	}

	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
}
