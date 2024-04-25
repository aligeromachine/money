//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_visa.h"
#include "f_dmod.h"
#include "f_trativ.h"
#include "f_visav.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfr_visa *fr_visa;
//---------------------------------------------------------------------------
__fastcall Tfr_visa::Tfr_visa(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visa::FormClose(TObject *Sender, TCloseAction &Action)
{
	fr_visa = NULL;
	Action=caFree;
}
//---------------------------------------------------------------------------
inline void Tfr_visa::Edit_Clear()
{
	visa_n->Text="";
	visa_nom->Text="";
	visa_s->Text="";
	Button2->Enabled=0;
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visa::visa_nChange(TObject *Sender)
{
	Button2->Enabled=1;
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visa::Button1Click(TObject *Sender)
{
	AnsiString s;
	int visa=0;

	if(visa_n->Text=="")
	{
		ShowMessage("Поле Наименование Карты не должно быть пустое!");
		visa_n->SetFocus();
		Abort();
	}
	if(visa_nom->Text=="")
	{
		ShowMessage("Поле № Карты не должно быть пустое!");
		visa_nom->SetFocus();
		Abort();
	}
	if(visa_s->Text=="")
	{
		ShowMessage("Поле Сумма не должно быть пустое!");
		visa_s->SetFocus();
		Abort();
	}

	s="SELECT count(*) as m FROM visa WHERE visa_n="+QuotedStr(Trim(visa_n->Text))+" AND visa_nom="+QuotedStr(Trim(visa_nom->Text));
	if(Form_trativ->f_visa)
	s+=" AND id_visa<>"+dmod1->q_visa->FieldByName("id_visa")->AsAnsiString;
	dmod1->q->Close();
	dmod1->q->SQL->Text=s;
	dmod1->q->Open();
	if(dmod1->q->FieldByName("m")->AsInteger != 0)
	{
		ShowMessage("Такая запись уже есть!");
		Abort();
	}

	if(Form_trativ->f_visa)
	{
		s="UPDATE visa SET ";
		s+="visa_n = '"+Trim(visa_n->Text)+"',";
		s+="visa_nom = '"+Trim(visa_nom->Text)+"',";
		s+="visa_s ="+visa_s->Text;
		s+=" WHERE id_visa ="+dmod1->q_visa->FieldByName("id_visa")->AsAnsiString;
		visa=dmod1->q_visa->FieldByName("id_visa")->AsInteger;
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=s;
		dmod1->ADOQ_Work->ExecSQL();
	}
	else
	{
		s="INSERT INTO visa (visa_n,visa_nom,visa_s) VALUES (";
		s+=QuotedStr(Trim(visa_n->Text))+",";
		s+=QuotedStr(Trim(visa_nom->Text))+",";
		s+=visa_s->Text+")";
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=s;
		dmod1->ADOQ_Work->ExecSQL();

		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT Max(id_visa) AS m FROM visa ";
		dmod1->q->Open();
		visa=dmod1->q->FieldByName("m")->AsInteger;

		Edit_Clear();
		visa_n->SetFocus();
	}

	if(fr_visav)
	{
		fr_visav->FormShow(Sender);
		dmod1->q_visa->Locate("id_visa",visa,TLocateOptions()<<loPartialKey);
	}

    Form_trativ->FormShow(Sender);

	if(Form_trativ->f_visa)
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visa::FormShow(TObject *Sender)
{
	if(Form_trativ->f_visa)
	{
		Caption="Изменение данных карты";
		visa_n->Text	=dmod1->q_visa->FieldByName("visa_n")->AsAnsiString;
		visa_nom->Text	=dmod1->q_visa->FieldByName("visa_nom")->AsAnsiString;
		visa_s->Text	=dmod1->q_visa->FieldByName("visa_s")->AsAnsiString;
		Button2->Enabled=0;
	}
	else
	Edit_Clear();
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visa::Button3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visa::visa_nKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(!(Key >= '0' && Key <= '9')&&Key!=VK_BACK)
	Key = 0x00;
}
//---------------------------------------------------------------------------
void __fastcall Tfr_visa::FormShortCut(TWMKey &Msg, bool &Handled)
{
	switch (Msg.CharCode)
	{
		case 27: Close(); break;
		case 13: Button1->Click(); Msg.CharCode=0;break;
		default: break;
	}
}
//---------------------------------------------------------------------------
