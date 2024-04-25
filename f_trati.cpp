//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_trati.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_trativ.h"
#include "f_org.h"
#include "f_prodvid.h"
#include "f_orgv.h"
#include "f_prodvidv.h"
#include "f_prodv.h"
#include "f_prod.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_trati *Form_trati;
//---------------------------------------------------------------------------
__fastcall TForm_trati::TForm_trati(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_trati::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action=caFree;
	Form_trati = NULL;
}
//---------------------------------------------------------------------------
inline void TForm_trati::org_add()
{
    dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT * FROM org ORDER BY name_org";
	dmod1->q->Open();
	n_org->Clear();
	id_org.clear();
	while (!dmod1->q->Eof)
	{
		n_org->Items->Add(dmod1->q->FieldByName("name_org")->AsAnsiString+" "+dmod1->q->FieldByName("adress_org")->AsAnsiString);
		id_org.push_back(dmod1->q->FieldByName("kod_org")->AsInteger);
		dmod1->q->Next();
	}
}
inline void TForm_trati::pv_add()
{
	AnsiString str = "SELECT kod_prod_vid,name_prod_vid FROM prod_vid where kod_prod_vid in ";
	str += " (select id_prod_vid_v from org_sv where id_org_v = "+IntToStr(id_org[n_org->ItemIndex])+") ORDER BY name_prod_vid";
	n_prod->Clear();
	dmod1->q->Close();
	dmod1->q->SQL->Text=str;
	dmod1->q->Open();
	n_prod_vid->Clear();
	id_prodvid.clear();
	while (!dmod1->q->Eof)
	{
		n_prod_vid->Items->Add(dmod1->q->FieldByName("name_prod_vid")->AsAnsiString);
		id_prodvid.push_back(dmod1->q->FieldByName("kod_prod_vid")->AsInteger);
		dmod1->q->Next();
	}
}
inline void TForm_trati::pr_add()
{
    dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT * FROM prod WHERE kod_prod_vid_v = "+IntToStr(id_prodvid[n_prod_vid->ItemIndex])+" ORDER BY name_prod";
	dmod1->q->Open();
	n_prod->Clear();
	id_prod.clear();
	while(!dmod1->q->Eof)
	{
		n_prod->Items->Add(dmod1->q->FieldByName("name_prod")->AsAnsiString);
		id_prod.push_back(dmod1->q->FieldByName("kod_prod")->AsInteger);
		dmod1->q->Next();
	}
}
inline void TForm_trati::Edit_Clear()
{
	this->org_add();
	Edit_cena->Text="";
	Edit_kol_ed->Text="";
	DateTimePicker_trati->Date=Date();
	Edit_prim->Text="";
	Button2->Enabled=0;
	n_org->SetFocus();
}
void __fastcall TForm_trati::n_orgChange(TObject *Sender)
{
	if(n_org->ItemIndex!=-1)
	{
		Button2->Enabled=true;
		this->pv_add();
	}
}

void __fastcall TForm_trati::n_prod_vidChange(TObject *Sender)
{
	if(n_prod_vid->ItemIndex!=-1)
	{
		Button2->Enabled=1;
        this->pr_add();
	}
}
void __fastcall TForm_trati::Edit_cenaChange(TObject *Sender)
{
	Button2->Enabled=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm_trati::n_prodChange(TObject *Sender)
{
	Button2->Enabled=1;
}
void __fastcall TForm_trati::Button3Click(TObject *Sender)
{
	Form_trati->Close();
}
void __fastcall TForm_trati::FormShortCut(TWMKey &Msg, bool &Handled)
{
	switch (Msg.CharCode)
	{
		case 27: Close(); break;
		case 13: Button1->Click(); Msg.CharCode=0; break;
		default: break;
	}
}
void __fastcall TForm_trati::BitBtn1Click(TObject *Sender)
{
	Form_trativ->f_trati_cl1=1;
	Form_trativ->f_org=0;
	if (!Form_org)
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
void __fastcall TForm_trati::BitBtn2Click(TObject *Sender)
{
 	Form_trativ->f_trati_cl2=1;
	Form_trativ->f_prodvid=0;
	if (!Form_prodvid)
	{
		Application->CreateForm(__classid(TForm_prodvid), &Form_prodvid);
		Form_prodvid->ShowModal();
	}
	else
	{
		if (IsIconic(Form_prodvidv->Handle))
		Form_prodvidv->WindowState = wsNormal;
		Form_prodvidv->ShowModal();
	}
}
void __fastcall TForm_trati::BitBtn3Click(TObject *Sender)
{
	Form_trativ->f_trati_cl3=1;
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
void __fastcall TForm_trati::Edit_cenaKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(!(Key >= '0' && Key <= '9')&&Key!=VK_BACK)
	Key = 0x00;
}
void __fastcall TForm_trati::FormShow(TObject *Sender)
{
	Edit_Clear();
	if(Form_trativ->f_trati)
	{
		this->Caption="Изменение данных покупки";
		this->n_org->ItemIndex=find(id_org.begin(),id_org.end(),dmod1->q_trati->FieldByName("kod_org")->AsInteger)-id_org.begin();
		this->n_orgChange(Sender);
		this->n_prod_vid->ItemIndex=find(id_prodvid.begin(),id_prodvid.end(),dmod1->q_trati->FieldByName("kod_prod_vid")->AsInteger)-id_prodvid.begin();
		this->n_prod_vidChange(Sender);
		this->n_prod->ItemIndex=find(id_prod.begin(),id_prod.end(),dmod1->q_trati->FieldByName("kod_prod")->AsInteger)-id_prod.begin();

		Edit_cena->Text=IntToStr(sum=dmod1->q_trati->FieldByName("cena_tr")->AsInteger);
		Edit_kol_ed->Text=dmod1->q_trati->FieldByName("kol_ed_tr")->AsAnsiString;
		DateTimePicker_trati->Date=a=dmod1->q_trati->FieldByName("data_tr")->AsDateTime;
		Edit_prim->Text=dmod1->q_trati->FieldByName("prim_tr")->AsAnsiString;
		Button2->Enabled=0;
	}
}
void __fastcall TForm_trati::Button1Click(TObject *Sender)
{
	AnsiString str;
	int trati=0;

	if(YearOf(DateTimePicker_trati->Date)>YearOf(Today()))
	{
		ShowMessage("Поле Дата должно быть не больше текущего года!");
		DateTimePicker_trati->SetFocus();
		Abort();
	}
	else if(YearOf(DateTimePicker_trati->Date)<YearOf(StrToDate("1.1.2012")))
	{
		ShowMessage("Поле Дата должно быть меньше 2012 г.!");
		DateTimePicker_trati->SetFocus();
		Abort();
	}
	if (n_org->Text=="")
	{
		ShowMessage("Поле Компании не должно быть пустое!");
		n_org->SetFocus();
		Abort();
	}
	if(n_prod_vid->Text=="")
	{
		ShowMessage("Поле Вид продуктов не должно быть пустое!");
		n_prod_vid->SetFocus();
		Abort();
	}
	else if(n_prod->Text=="")
	{
		ShowMessage("Поле Продукты не должно быть пустое!");
		n_prod->SetFocus();
		Abort();
	}
	if(Edit_cena->Text=="")
	{
		ShowMessage("Поле Цена не должно быть пустое!");
		Edit_cena->SetFocus();
		Abort();
	}

	if (Form_trativ->f_trati)
	{
		str="UPDATE trati SET ";
		str+="kod_org_tr ="+IntToStr(id_org[n_org->ItemIndex])+",";
		str+="kod_prod_tr ="+IntToStr(id_prod[n_prod->ItemIndex])+",";
		str+="cena_tr ="+Edit_cena->Text+",";
		str+="kol_ed_tr ="+QuotedStr(Trim(Edit_kol_ed->Text))+",";
		str+="data_tr ="+QuotedStr(DateTimePicker_trati->Date)+",";
		str+="prim_tr ="+QuotedStr(Trim(Edit_prim->Text));
		str+=" WHERE kod_pokup ="+IntToStr(dmod1->q_trati->FieldByName("kod_pokup")->AsInteger);
		trati=dmod1->q_trati->FieldByName("kod_pokup")->AsInteger;

		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str;
		dmod1->ADOQ_Work->ExecSQL();

		if(YearOf(DateTimePicker_trati->Date)==YearOf(Today())&&YearOf(a)==YearOf(Today())) //текущий
		{
			if(MonthOf(DateTimePicker_trati->Date)==MonthOf(a))
			{
				if(sum!=StrToInt(Edit_cena->Text))
				sum_ins1(MonthOf(a));
			}
			else
			sum_ins2(MonthOf(DateTimePicker_trati->Date),MonthOf(a));
		}
		else if(YearOf(DateTimePicker_trati->Date)!=YearOf(Today())&&YearOf(a)==YearOf(Today())) //из наст. в прошлое
		{
			sum_ins3(MonthOf(a)); 
			Form_trativ->s_trati=0;
		}
		else if(YearOf(DateTimePicker_trati->Date)==YearOf(Today())&&YearOf(a)!=YearOf(Today())) // из прошлого в наст. 
		{
			sum_ins3(MonthOf(DateTimePicker_trati->Date)); 
			Form_trativ->s_trati=0;
		}
		else if(YearOf(DateTimePicker_trati->Date)!=YearOf(Today())&&YearOf(a)!=YearOf(Today())) //прошлое
		{
			if(sum!=StrToInt(Edit_cena->Text))
			{
				sum_ins4();
				Form_trativ->s_trati=0;
			}
		}
	}
	else
	{
		str="INSERT INTO trati (";
		str+="kod_org_tr,";
		str+="kod_prod_tr,";
		str+="cena_tr,";
		str+="kol_ed_tr,";
		str+="data_tr,";
		str+="prim_tr";
		str+=") VALUES (";
		str+=IntToStr(id_org[n_org->ItemIndex])+",";
		str+=IntToStr(id_prod[n_prod->ItemIndex])+",";
		str+=Edit_cena->Text+",";
		str+=QuotedStr(Trim(Edit_kol_ed->Text))+",";
		str+=QuotedStr(DateTimePicker_trati->Date)+",";
		str+=QuotedStr(Trim(Edit_prim->Text))+")";

		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str;
		dmod1->ADOQ_Work->ExecSQL();

		if(YearOf(DateTimePicker_trati->Date)==YearOf(Today()))
		sum_add1(MonthOf(DateTimePicker_trati->Date),StrToInt(Edit_cena->Text));
		else
		{
			sum_add2(StrToInt(Edit_cena->Text));
			Form_trativ->s_trati=0;
		}
		
		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT Max(kod_pokup) AS kod FROM trati ";
		dmod1->q->Open();
		trati=dmod1->q->FieldByName("kod")->AsInteger;

		Edit_cena->Text="";
		Edit_kol_ed->Text="";
		DateTimePicker_trati->Date=Date();
		Edit_prim->Text="";
		Button2->Enabled=0;
		n_prod_vid->ItemIndex=-1;
		n_prod->Clear();
		id_prod.clear();

		n_org->SetFocus();
	}

	Form_trativ->FormShow(Sender);

	if (trati)
	dmod1->q_trati->Locate("kod_pokup",trati,TLocateOptions()<<loPartialKey);

	if (Form_trativ->f_trati)
	Close();
}
inline void TForm_trati::sum_add1(const int& mons1,const int& s)
{
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t=sum_t+"+IntToStr(s)+" WHERE sum_data="+IntToStr(mons1);
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_trati::sum_add2(const int& s)
{
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t=sum_t+"+IntToStr(s)+" WHERE id_sum=1;";
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_trati::sum_ins1(const int& mons1)
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati] WHERE Year(data_tr)="+IntToStr(YearOf(Today()))+" AND Month(data_tr)="+IntToStr(mons1);
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(mons1);
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_trati::sum_ins2(const int& mons1,const int& mons2)
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati] WHERE Year(data_tr)="+IntToStr(YearOf(Today()))+" AND Month(data_tr)="+IntToStr(mons1);
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(mons1);
	dmod1->ADOQ_del->ExecSQL();

	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati] WHERE Year(data_tr)="+IntToStr(YearOf(Today()))+" AND Month(data_tr)="+IntToStr(mons2);
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(mons2);
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_trati::sum_ins3(const int& mons1)
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati] WHERE Year(data_tr)<"+IntToStr(YearOf(Today()));
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE id_sum=1";
	dmod1->ADOQ_del->ExecSQL();

	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati] WHERE Year(data_tr)="+IntToStr(YearOf(Today()))+" AND Month(data_tr)="+IntToStr(mons1);
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(mons1);
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_trati::sum_ins4()
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati] WHERE Year(data_tr)<"+IntToStr(YearOf(Today()));
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE id_sum=1";
	dmod1->ADOQ_del->ExecSQL();
}
//---------------------------------------------------------------------------

