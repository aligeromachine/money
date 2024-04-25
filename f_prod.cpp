//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_prod.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_prodv.h"
#include "f_trati.h"
#include "f_trativ.h"
#include "f_prodvid.h"
#include "f_prodvidv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_prod *Form_prod;
//---------------------------------------------------------------------------
__fastcall TForm_prod::TForm_prod(TComponent* Owner)
	: TForm(Owner)
{
}
inline void TForm_prod::Edit_Clear()
{
    this->pv_add();
	Edit_name->Text="";
	Button2->Enabled=0;
}
inline void TForm_prod::pv_add()
{
	this->n_prodvid->Clear();
	this->id_prodvid.clear();
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT kod_prod_vid,name_prod_vid FROM prod_vid ORDER BY name_prod_vid";
	dmod1->q->Open();
	while (!dmod1->q->Eof)
	{
		this->n_prodvid->Items->Add(dmod1->q->FieldByName("name_prod_vid")->AsAnsiString);
		this->id_prodvid.push_back(dmod1->q->FieldByName("kod_prod_vid")->AsInteger);
		dmod1->q->Next();
	}
}
void __fastcall TForm_prod::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(Form_trativ->f_trati_cl3)
	Form_trativ->f_trati_cl3=0;
	Action=caFree;
	Form_prod = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm_prod::n_prodvidChange(TObject *Sender)
{
	Button2->Enabled=1;
}
void __fastcall TForm_prod::Button1Click(TObject *Sender)
{
	int prod=0;
	AnsiString str1;

	if (n_prodvid->Text=="")
	{
		ShowMessage("Поле Тип продуктов не должно быть пустое!");
		n_prodvid->SetFocus();
		Abort();
	}
	if (Edit_name->Text=="")
	{
		ShowMessage("Поле Название не должно быть пустое!");
		Edit_name->SetFocus();
		Abort();
	}

	str1="SELECT count(1) as m FROM prod WHERE name_prod="+QuotedStr(Trim(Edit_name->Text));
	if(Form_trativ->f_prod)
	{
		str1+=" AND kod_prod<>"+dmod1->q_prod->FieldByName("kod_prod")->AsAnsiString;
	}

	dmod1->q->Close();
	dmod1->q->SQL->Text=str1;
	dmod1->q->Open();
	if(dmod1->q->FieldByName("m")->AsInteger != 0)
	{
		str1="SELECT kod_prod_vid_v FROM prod WHERE name_prod="+QuotedStr(Trim(Edit_name->Text));
		dmod1->ADOQ_del->Close();
		dmod1->ADOQ_del->SQL->Text = str1;
		dmod1->ADOQ_del->Open();
		str1 = "SELECT name_prod_vid FROM prod_vid WHERE kod_prod_vid = "+dmod1->ADOQ_del->FieldByName("kod_prod_vid_v")->AsAnsiString;
		dmod1->ADOQ_del->Close();
		dmod1->ADOQ_del->SQL->Text = str1;
		dmod1->ADOQ_del->Open();

		ShowMessage("Такая запись " +Trim(Edit_name->Text)+ " в типе продуктов <"+dmod1->ADOQ_del->FieldByName("name_prod_vid")->AsAnsiString+"> уже есть!");
		Abort();
	}

	if (Form_trativ->f_prod)
	{
		str1="UPDATE prod SET ";
		str1+="kod_prod_vid_v ="+IntToStr(id_prodvid[n_prodvid->ItemIndex])+",";
		str1+="name_prod ="+QuotedStr(Trim(Edit_name->Text));
		str1+=" WHERE kod_prod ="+dmod1->q_prod->FieldByName("kod_prod")->AsAnsiString;
		prod=dmod1->q_prod->FieldByName("kod_prod")->AsInteger;
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str1;
		dmod1->ADOQ_Work->ExecSQL();
	}
	else
	{
		str1="INSERT INTO prod (";
		str1+="kod_prod_vid_v, ";
		str1+="name_prod ";
		str1+=") VALUES (";
		str1+=IntToStr(id_prodvid[n_prodvid->ItemIndex])+",";
		str1+=QuotedStr(Trim(Edit_name->Text))+")";
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str1;
		dmod1->ADOQ_Work->ExecSQL();

		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT Max(kod_prod) AS kod FROM prod ";
		dmod1->q->Open();
		prod=dmod1->q->FieldByName("kod")->AsInteger;

		Edit_name->Text="";
		Button2->Enabled=0;

		n_prodvid->SetFocus();
	}

	if (Form_prodv)
	{
		Form_prodv->FormShow(Sender);
		dmod1->q_prod->Locate("kod_prod",prod,TLocateOptions()<<loPartialKey);
	}

	if (Form_trati)
	{
		Form_trati->n_prod_vidChange(Sender);
		Form_trati->n_prod->ItemIndex=find(Form_trati->id_prod.begin(),Form_trati->id_prod.end(),prod)-Form_trati->id_prod.begin();
		if(Form_trativ->f_trati_cl3)
		{
			Form_trativ->f_trati_cl3=0;
			Form_trati->Edit_cena->SetFocus();
			Close();
		}
	}

	if(Form_trativ->f_prod)
	{
		Form_trativ->FormShow(Sender);
		Close();
	}
}
void __fastcall TForm_prod::Button3Click(TObject *Sender)
{
	Form_prod->Close();
}
void __fastcall TForm_prod::FormShortCut(TWMKey &Msg, bool &Handled)
{
	switch (Msg.CharCode)
	{
		case 27: Close(); break;
		case 13: Button1->Click(); Msg.CharCode=0; break;
		default: break;
	}
}
void __fastcall TForm_prod::FormShow(TObject *Sender)
{
	Edit_Clear();
	if(Form_trativ->f_prod)
	{
		Caption="Изменение данных продукта";
		n_prodvid->ItemIndex=find(id_prodvid.begin(),id_prodvid.end(),dmod1->q_prod->FieldByName("kod_prod_vid")->AsInteger)-id_prodvid.begin();
		Edit_name->Text=dmod1->q_prod->FieldByName("name_prod")->AsAnsiString;
		Button2->Enabled=0;
	}
	else if(Form_trativ->f_trati_cl3)
	{
		n_prodvid->ItemIndex=n_prodvid->Items->IndexOf(Form_trati->n_prod_vid->Items->Strings[Form_trati->n_prod_vid->ItemIndex]);
        Edit_name->SetFocus();
	}
}
void __fastcall TForm_prod::BitBtn1Click(TObject *Sender)
{
    Form_trativ->f_prod_cl4=1;
	if (!Form_prodvid)
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

