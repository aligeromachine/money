//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_prih.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_prihv.h"
#include "f_trativ.h"
#include "f_prihvid.h"
#include "f_prihvidv.h"
#include "f_visav.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_prih *Form_prih;
//---------------------------------------------------------------------------
__fastcall TForm_prih::TForm_prih(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
inline void TForm_prih::Edit_Clear()
{
	this->prih_add();
    this->visa_add();
	Edit_sum->Text="";
	TDateTime dat;
	dat=Date();
	DateTimePicker_prih->Date=dat;
	Edit_prim->Text="";
	Button2->Enabled=0;
}
inline void TForm_prih::prih_add()
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT kod_prih_vid,name_prih_vid FROM prih_vid ORDER BY name_prih_vid";
	dmod1->q->Open();
	this->n_prihvid->Clear();
	this->id_prihvid.clear();
	while(!dmod1->q->Eof)
	{
		this->n_prihvid->Items->Add(dmod1->q->FieldByName("name_prih_vid")->AsAnsiString);
		this->id_prihvid.push_back(dmod1->q->FieldByName("kod_prih_vid")->AsInteger);
		dmod1->q->Next();
	}
}
inline void TForm_prih::visa_add()
{
   	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT id_visa,visa_n FROM visa ORDER BY visa_n";
	dmod1->q->Open();
	this->visa->Clear();
	this->v_visa.clear();
	while(!dmod1->q->Eof)
	{
		this->visa->Items->Add(dmod1->q->FieldByName("visa_n")->AsAnsiString);
		this->v_visa.push_back(dmod1->q->FieldByName("id_visa")->AsInteger);
		dmod1->q->Next();
	}
}
void __fastcall TForm_prih::FormShow(TObject *Sender)
{
	Edit_Clear();
	if(Form_trativ->f_prih)
	{
		Caption="Изменение данных получки";
		n_prihvid->ItemIndex=find(id_prihvid.begin(),id_prihvid.end(),dmod1->q_prih->FieldByName("kod_prih_vid")->AsInteger)-id_prihvid.begin();
		Edit_sum->Text=IntToStr(sum=dmod1->q_prih->FieldByName("sum_prih")->AsInteger);
		DateTimePicker_prih->Date=a=dmod1->q_prih->FieldByName("data_prih")->AsDateTime;
		Edit_prim->Text=dmod1->q_prih->FieldByName("prim_prih")->AsAnsiString;
		Button2->Enabled=0;
		visa->Enabled=0;
	}
}
void __fastcall TForm_prih::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_prih = NULL;
	Action=caFree;
}
void __fastcall TForm_prih::n_prihvidChange(TObject *Sender)
{
	Button2->Enabled=1;
}
void __fastcall TForm_prih::Button3Click(TObject *Sender)
{
	Form_prih->Close();
}
void __fastcall TForm_prih::Edit_sumKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(!(Key >= '0' && Key <= '9')&&Key!=VK_BACK&&Key!='-')
	Key = 0x00;
}
void __fastcall TForm_prih::FormShortCut(TWMKey &Msg, bool &Handled)
{
	switch (Msg.CharCode)
	{
		case 27: Close(); break;
		case 13: Button1->Click(); Msg.CharCode=0;break;
		default: break;
	}
}
void __fastcall TForm_prih::BitBtn1Click(TObject *Sender)
{
	Form_trativ->f_prih_cl5=1;
	Form_trativ->f_prihvid=0;
	if (!Form_prihvid)
	{
		Application->CreateForm(__classid(TForm_prihvid), &Form_prihvid);
		Form_prihvid->Show();
	}
	else
	{
		if (IsIconic(Form_prihvid->Handle))
		Form_prihvid->WindowState = wsNormal;
		Form_prihvid->Show();
	}
}
void __fastcall TForm_prih::Button1Click(TObject *Sender)
{
	int prih=0;
	AnsiString s;

	if(MonthOf(DateTimePicker_prih->Date)!=12&&!(Form_trativ->f_prih&&MonthOf(DateTimePicker_prih->Date)==MonthOf(a)))
	{
		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT count(*) as m FROM prih_vid RIGHT JOIN prih ON prih_vid.kod_prih_vid = prih.kod_prih_vid_v "
		"WHERE (prih_vid.name_prih_vid='Зарплата') AND Year(data_prih)="+IntToStr(YearOf(DateTimePicker_prih->Date))+
		" AND Month(data_prih)="+IntToStr(MonthOf(DateTimePicker_prih->Date));
		dmod1->q->Open();
		if((dmod1->q->FieldByName("m")->AsInteger != 0)&&(n_prihvid->Text=="Зарплата"))
		{
			ShowMessage("В этом месяце уже была зарплата!");
			Abort();
		}
	}

	if(YearOf(DateTimePicker_prih->Date)>YearOf(Today()))
	{
		ShowMessage("Поле Дата должно быть не больше текущего года!");
		DateTimePicker_prih->SetFocus();
		Abort();
	}
	else if(YearOf(DateTimePicker_prih->Date)<YearOf(StrToDate("1.1.2012")))
	{
		ShowMessage("Поле Дата должно быть меньше 2012 г.!");
		DateTimePicker_prih->SetFocus();
		Abort();
	}
	if(n_prihvid->Text=="")
	{
		ShowMessage("Поле Название получки не должно быть пустое!");
		n_prihvid->SetFocus();
		Abort();
	}
	if(Edit_sum->Text=="")
	{
		ShowMessage("Поле Сумма получки не должно быть пустое!");
		Edit_sum->SetFocus();
		Abort();
	}

	if(Form_trativ->f_prih)
	{
		s="UPDATE prih SET ";
		s+="kod_prih_vid_v ="+IntToStr(id_prihvid[n_prihvid->ItemIndex])+",";
		s+="sum_prih ="+Edit_sum->Text+",";
		s+="data_prih ="+QuotedStr(DateTimePicker_prih->Date)+",";
		s+="prim_prih ="+QuotedStr(Trim(Edit_prim->Text));
		s+=" WHERE kod_prih ="+dmod1->q_prih->FieldByName("kod_prih")->AsAnsiString;
		prih=dmod1->q_prih->FieldByName("kod_prih")->AsInteger;

		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=s;
		dmod1->ADOQ_Work->ExecSQL();

		if(YearOf(DateTimePicker_prih->Date)==YearOf(Today())&&YearOf(a)==YearOf(Today())) //текущий
		{
			if(MonthOf(DateTimePicker_prih->Date)==MonthOf(a))
			{
				if(sum!=StrToInt(Edit_sum->Text))
				sum_ins1(MonthOf(a));
			}
			else
			sum_ins2(MonthOf(DateTimePicker_prih->Date),MonthOf(a));
		}
		else if(YearOf(DateTimePicker_prih->Date)!=YearOf(Today())&&YearOf(a)==YearOf(Today())) //из наст. в прошлое
		{
			sum_ins3(MonthOf(a));
			Form_trativ->s_prih=0;
		}
		else if(YearOf(DateTimePicker_prih->Date)==YearOf(Today())&&YearOf(a)!=YearOf(Today())) // из прошлого в наст.
		{
			sum_ins3(MonthOf(DateTimePicker_prih->Date));
			Form_trativ->s_prih=0;
		}
		else if(YearOf(DateTimePicker_prih->Date)!=YearOf(Today())&&YearOf(a)!=YearOf(Today())) //прошлое
		{
			if(sum!=StrToInt(Edit_sum->Text))
			{
				sum_ins4();
				Form_trativ->s_prih=0;
			}
		}
	}
	else
	{
		s="INSERT INTO prih (";
		s+="kod_prih_vid_v, ";
		s+="sum_prih, ";
		s+="data_prih, ";
		s+="prim_prih ";
		s+=") VALUES (";
		s+=IntToStr(id_prihvid[n_prihvid->ItemIndex])+",";
		s+=Edit_sum->Text+",";
		s+=QuotedStr(DateTimePicker_prih->DateTime)+",";
		s+=QuotedStr(Trim(Edit_prim->Text))+")";

		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=s;
		dmod1->ADOQ_Work->ExecSQL();

		if(visa->Enabled&&visa->Text!="")
		{
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text="UPDATE visa SET visa_s=visa_s+"+Edit_sum->Text+" WHERE id_visa="+IntToStr(v_visa[visa->ItemIndex]);
			dmod1->ADOQ_Work->ExecSQL();

        	if(fr_visav)
			{
				fr_visav->FormShow(Sender);
				dmod1->q_visa->Locate("id_visa",v_visa[visa->ItemIndex],TLocateOptions()<<loPartialKey);
			}
		}

		if(YearOf(DateTimePicker_prih->Date)==YearOf(Today()))
		sum_add1(MonthOf(DateTimePicker_prih->Date),StrToInt(Edit_sum->Text));
		else
		{
			sum_add2(StrToInt(Edit_sum->Text));
			Form_trativ->s_prih=0;
		}

		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT Max(kod_prih) AS kod FROM prih ";
		dmod1->q->Open();
		prih=dmod1->q->FieldByName("kod")->AsInteger;

		Edit_Clear();
		n_prihvid->SetFocus();
	}
	if(Form_prihv)
	{
		Form_prihv->FormShow(Sender);
		dmod1->q_prih->Locate("kod_prih",prih,TLocateOptions()<<loPartialKey);
	}

	Form_trativ->FormShow(Sender);

	if (Form_trativ->f_prih)
	Close();
}
//---------------------------------------------------------------------------
inline void TForm_prih::sum_add1(const int& mons1,const int& s)
{
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p=sum_p+"+IntToStr(s)+" WHERE sum_data="+IntToStr(mons1);
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_prih::sum_add2(const int& s)
{
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p=sum_p+"+IntToStr(s)+" WHERE id_sum=1;";
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_prih::sum_ins1(const int& mons1)
{
    dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih] WHERE Year(data_prih)="+IntToStr(YearOf(Today()))+" AND Month(data_prih)="+IntToStr(mons1);
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(mons1);
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_prih::sum_ins2(const int& mons1,const int& mons2)
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih] WHERE Year(data_prih)="+IntToStr(YearOf(Today()))+" AND Month(data_prih)="+IntToStr(mons1);
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(mons1);
	dmod1->ADOQ_del->ExecSQL();

	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih] WHERE Year(data_prih)="+IntToStr(YearOf(Today()))+" AND Month(data_prih)="+IntToStr(mons2);
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(mons2);
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_prih::sum_ins3(const int& mons1)
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih] WHERE Year(data_prih)<"+IntToStr(YearOf(Today()));
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE id_sum=1";
	dmod1->ADOQ_del->ExecSQL();

	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih] WHERE Year(data_prih)="+IntToStr(YearOf(Today()))+" AND Month(data_prih)="+IntToStr(mons1);
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(mons1);
	dmod1->ADOQ_del->ExecSQL();
}
inline void TForm_prih::sum_ins4()
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih] WHERE Year(data_prih)<"+IntToStr(YearOf(Today()));
	dmod1->q->Open();
	dmod1->ADOQ_del->Close();
	dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE id_sum=1";
	dmod1->ADOQ_del->ExecSQL();
}
//---------------------------------------------------------------------------

