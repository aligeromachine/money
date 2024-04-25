//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_prihvid.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_prihvidv.h"
#include "f_trativ.h"
#include "f_prih.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_prihvid *Form_prihvid;
//---------------------------------------------------------------------------
__fastcall TForm_prihvid::TForm_prihvid(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihvid::Button3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihvid::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_prihvid = NULL;
	Action=caFree;
}
//---------------------------------------------------------------------------
inline void TForm_prihvid::Edit_Clear()
{
	Edit_name->Text="";
	Button2->Enabled=0;
}
void __fastcall TForm_prihvid::Edit_nameChange(TObject *Sender)
{
	 Button2->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihvid::Button1Click(TObject *Sender)
{
	int prih=0;
	AnsiString str1;

	if (Edit_name->Text=="")
	{
		ShowMessage("Поле Название не должно быть пустое!");
		Edit_name->SetFocus();
		Abort();
	}

	str1="SELECT count(*) as m FROM prih_vid WHERE name_prih_vid="+QuotedStr(Trim(Edit_name->Text));
	if(Form_trativ->f_prihvid)
	str1+=" AND kod_prih_vid<>"+dmod1->q_prihvid->FieldByName("kod_prih_vid")->AsAnsiString;
	dmod1->q->Close();
	dmod1->q->SQL->Text=str1;
	dmod1->q->Open();
	if(dmod1->q->FieldByName("m")->AsInteger != 0)
	{
		ShowMessage("Это название уже было!");
		Abort();
	}

	if(Form_trativ->f_prihvid)
	{
		str1="UPDATE prih_vid SET ";
		str1+="name_prih_vid ="+QuotedStr(Trim(Edit_name->Text));
		str1+=" WHERE kod_prih_vid ="+dmod1->q_prihvid->FieldByName("kod_prih_vid")->AsAnsiString;
		prih=dmod1->q_prihvid->FieldByName("kod_prih_vid")->AsInteger;

		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str1;
		dmod1->ADOQ_Work->ExecSQL();
	}
	else
	{
		str1="INSERT INTO prih_vid (";
		str1+="name_prih_vid";
		str1+=") VALUES (";
		str1+=QuotedStr(Trim(Edit_name->Text))+")";

		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str1;
		dmod1->ADOQ_Work->ExecSQL();

		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT Max(kod_prih_vid) AS kod FROM prih_vid ";
		dmod1->q->Open();
		prih=dmod1->q->FieldByName("kod")->AsInteger;
		Edit_Clear();
		Edit_name->SetFocus();
	}

	if (Form_prihvidv)
	{
		Form_prihvidv->FormShow(Sender);
		dmod1->q_prihvid->Locate("kod_prih_vid",prih,TLocateOptions()<<loPartialKey);
	}

	if(Form_prih)
	{
		Form_prih->prih_add();
		Form_prih->n_prihvid->ItemIndex=find(Form_prih->id_prihvid.begin(),Form_prih->id_prihvid.end(),prih)-Form_prih->id_prihvid.begin();
		if(Form_trativ->f_prih_cl5)
		{
			Form_trativ->f_prih_cl5=0;
			Form_prih->Edit_sum->SetFocus();
			Close();
		}
	}

	if(Form_trativ->f_prihvid)
	Close();
}
void __fastcall TForm_prihvid::FormShortCut(TWMKey &Msg, bool &Handled)
{
	switch(Msg.CharCode)
	{
		case 27: Close(); break;
		case 13: Button1->Click(); Msg.CharCode=0; break;
		default: break;
	}
}
void __fastcall TForm_prihvid::FormShow(TObject *Sender)
{
	if(Form_trativ->f_prihvid)
	{
		Caption="Изменение данных типа получки";
		Edit_name->Text=dmod1->q_prihvid->FieldByName("name_prih_vid")->AsAnsiString;
		Button2->Enabled=0;
	}
	else
	Edit_Clear();
}
