//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_prodvid.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_prodvidv.h"
#include "f_trati.h"
#include "f_trativ.h"
#include "f_prod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_prodvid *Form_prodvid;
//---------------------------------------------------------------------------
__fastcall TForm_prodvid::TForm_prodvid(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_prodvid::Button3Click(TObject *Sender)
{
	Close();
}
void __fastcall TForm_prodvid::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_prodvid = NULL;
	Action=caFree;
}
inline void TForm_prodvid::Edit_Clear()
{
	Edit_name->Text="";
	Button2->Enabled=0;
}
void __fastcall TForm_prodvid::Edit_nameChange(TObject *Sender)
{
	Button2->Enabled=1;
}
void __fastcall TForm_prodvid::Button1Click(TObject *Sender)
{
	int prod_vid=0;
	AnsiString str1;

	if (Edit_name->Text=="")
	{
		ShowMessage("Поле Название не должно быть пустое!");
        Edit_name->SetFocus();
		Abort();
	}

	str1="SELECT count(*) as m FROM prod_vid WHERE name_prod_vid="+QuotedStr(Trim(Edit_name->Text));
	if(Form_trativ->f_prodvid)
	str1+=" AND kod_prod_vid<>"+dmod1->q_prodvid->FieldByName("kod_prod_vid")->AsAnsiString;
	dmod1->q->Close();
	dmod1->q->SQL->Text=str1;
	dmod1->q->Open();
	if(dmod1->q->FieldByName("m")->AsInteger != 0)
	{
		ShowMessage("Это название уже было!");
		Abort();
	}

	if(Form_trativ->f_prodvid)
	{
		str1="UPDATE prod_vid SET ";
		str1+="name_prod_vid ="+QuotedStr(Trim(Edit_name->Text));
		str1+=" WHERE kod_prod_vid ="+dmod1->q_prodvid->FieldByName("kod_prod_vid")->AsAnsiString;
		prod_vid=dmod1->q_prodvid->FieldByName("kod_prod_vid")->AsInteger;
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str1;
		dmod1->ADOQ_Work->ExecSQL();
	}
	else
	{
		str1="INSERT INTO prod_vid (";
		str1+="name_prod_vid ";
		str1+=") VALUES (";
		str1+= "'" + Edit_name->Text.Trim() + "')";
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str1;
		dmod1->ADOQ_Work->ExecSQL();

		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT Max(kod_prod_vid) AS kod FROM prod_vid ";
		dmod1->q->Open();
		prod_vid=dmod1->q->FieldByName("kod")->AsInteger;

		Edit_Clear();
		Edit_name->SetFocus();
	}

	if (Form_prodvidv)
	{
		Form_prodvidv->FormShow(Sender);
		dmod1->q_prodvid->Locate("kod_prod_vid",prod_vid,TLocateOptions()<<loPartialKey);
	}

	Form_gl->CheckListBox_prodvid_add();

	if(Form_prod)
	{
		Form_prod->pv_add();
		Form_prod->n_prodvid->ItemIndex=find(Form_prod->id_prodvid.begin(),Form_prod->id_prodvid.end(),prod_vid)-Form_prod->id_prodvid.begin();
		if(Form_trativ->f_prod_cl4)
		{
			Form_trativ->f_prod_cl4=0;
			Form_prod->Edit_name->SetFocus();
			Close();
		}
	}

	if(Form_trati)
	{
		if ((Form_trati->n_org->ItemIndex!=-1)) {
			AnsiString str = "insert into org_sv (id_org_v,id_prod_vid_v) values ";
			str += "(" + AnsiString(Form_trati->id_org[Form_trati->n_org->ItemIndex]) + "," + AnsiString(prod_vid) + ")";
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text=str;
			dmod1->ADOQ_Work->ExecSQL();
		}

		int kod_p3=(Form_trati->n_prod->ItemIndex!=-1)? Form_trati->id_prod[Form_trati->n_prod->ItemIndex]:0;
		Form_trati->pv_add();
		Form_trati->n_prod_vid->ItemIndex=find(Form_trati->id_prodvid.begin(),Form_trati->id_prodvid.end(),prod_vid)-Form_trati->id_prodvid.begin();
		Form_trati->n_prod_vidChange(Sender);

		if(kod_p3)
		Form_trati->n_prod->ItemIndex=find(Form_trati->id_prod.begin(),Form_trati->id_prod.end(),kod_p3)-Form_trati->id_prod.begin();

		if(Form_trativ->f_trati_cl2)
		{
			Form_trativ->f_trati_cl2=0;
			Form_trati->n_prod->SetFocus();
			Close();
		}
	}

	if(Form_trativ->f_prodvid)
	{
		Form_trativ->FormShow(Sender);
		Close();
	}
}
void __fastcall TForm_prodvid::FormShortCut(TWMKey &Msg, bool &Handled)
{
	switch (Msg.CharCode)
	{
		case 27: Close(); break;
		case 13: Button1->Click(); Msg.CharCode=0; break;
		default: break;
	}
}
void __fastcall TForm_prodvid::FormShow(TObject *Sender)
{
	if (Form_trativ->f_prodvid)
	{
		Caption="Изменение данных типа продукта";
		Edit_name->Text=dmod1->q_prodvid->FieldByName("name_prod_vid")->AsAnsiString;
		Button2->Enabled=0;
	}
	else
	Edit_Clear();
}

