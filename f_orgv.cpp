//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_orgv.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_org.h"
#include "f_trativ.h"
#include "f_trati.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_orgv *Form_orgv;
//---------------------------------------------------------------------------
__fastcall TForm_orgv::TForm_orgv(TComponent* Owner)
	: TForm(Owner)
{
}
void __fastcall TForm_orgv::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_orgv = NULL;
	Action=caFree;
}
void __fastcall TForm_orgv::ToolButton7Click(TObject *Sender)
{
	Close();
}
void __fastcall TForm_orgv::ToolButton2Click(TObject *Sender)
{
	Form_trativ->f_org=0;
	if(!Form_org)
	{
		Application->CreateForm(__classid(TForm_org), &Form_org);
		Form_org->ShowModal();
	}
	else
	{
		if (IsIconic(Form_org->Handle))
		Form_org->WindowState = wsNormal;
		Form_org->ShowModal();
	}
}
void __fastcall TForm_orgv::ToolButton4Click(TObject *Sender)
{
	if(ToolButton4->Enabled)
	{
		Form_trativ->f_org=1;
		if(!Form_org)
		{
			Application->CreateForm(__classid(TForm_org), &Form_org);
			Form_org->ShowModal();
		}
		else
		{
			if (IsIconic(Form_org->Handle))
			Form_org->WindowState = wsNormal;
			Form_org->ShowModal();
		}
	}
}
void __fastcall TForm_orgv::ToolButton5Click(TObject *Sender)
{
	if (ToolButton4->Enabled)
	if(MessageBoxA(0,"Вы действительно хотите удалить выбранную запись?","Подтверждение",MB_OKCANCEL)==IDOK)
	{
		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT count(*) as m FROM trati WHERE kod_org_tr = "+IntToStr(dmod1->q_org->FieldByName("kod_org")->AsInteger);
		dmod1->q->Open();
		if(dmod1->q->FieldByName("m")->AsInteger != 0) {
			ShowMessage("Нельзя удалить эту запись т.к. есть связанные записи в таблице Траты!");
		}
		else
		{
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text="DELETE FROM org WHERE kod_org = "+IntToStr(dmod1->q_org->FieldByName("kod_org")->AsInteger)+";";
			dmod1->ADOQ_Work->ExecSQL();
			Form_gl->CheckListBox_org_add();
			FormShow(Sender);
			if(Form_trati)
			{
				int kod_org = Form_trati->id_org[Form_trati->n_org->ItemIndex];
				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT * FROM org ORDER BY name_org";
				dmod1->q->Open();
				Form_trati->n_org->Clear();
				Form_trati->id_org.clear();
				while(!dmod1->q->Eof)
				{
					Form_trati->n_org->Items->Add(dmod1->q->FieldByName("name_org")->AsAnsiString+" "+dmod1->q->FieldByName("adress_org")->AsAnsiString);
					Form_trati->id_org.push_back(dmod1->q->FieldByName("kod_org")->AsInteger);
					dmod1->q->Next();
				}
				Form_trati->n_org->ItemIndex=find(Form_trati->id_org.begin(),Form_trati->id_org.end(),kod_org)-Form_trati->id_org.begin();
			}
		}
	}
}
void __fastcall TForm_orgv::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
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
void __fastcall TForm_orgv::Edit1Change(TObject *Sender)
{
	dmod1->q_org->Close();
	dmod1->q_org->Parameters->ParamByName("name_org")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_org->Open();
	if (dmod1->q_org->RecordCount)
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
void __fastcall TForm_orgv::FormShow(TObject *Sender)
{
	dmod1->q_org->Close();
	dmod1->q_org->Parameters->ParamByName("name_org")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_org->Open();
	if (dmod1->q_org->RecordCount)
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
void __fastcall TForm_orgv::DBGrid1DblClick(TObject *Sender)
{
	ToolButton4Click(Sender);
}
void __fastcall TForm_orgv::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
	if (State.Contains(gdSelected))
	{
		DBGrid1->Canvas->Brush->Color  = clWebLightCoral;
		DBGrid1->Canvas->Font->Color  = clBlack;
	}

	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
}
