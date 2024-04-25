//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_gl.h"
#include "f_dmod.h"
#include "f_org.h"
#include "f_orgv.h"
#include "f_prod.h"
#include "f_prodv.h"
#include "f_trati.h"
#include "f_trativ.h"
#include "f_prodvid.h"
#include "f_prodvidv.h"
#include "f_prih.h"
#include "f_prihv.h"
#include "f_prihvid.h"
#include "f_prihvidv.h"
#include "f_it.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_gl *Form_gl;
int flag_ovp;
AnsiString s1,s2,s3,data;
//---------------------------------------------------------------------------
__fastcall TForm_gl::TForm_gl(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_gl::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_gl->Action->Free();
}
//---------------------------------------------------------------------------
void __fastcall TForm_gl::Clear()
{
	TDateTime dat;
	dat=Date();
	DateTimePicker_n->Date=dat;
	DateTimePicker_k->Date=dat;
	ComboBox_mon->ItemIndex = -1;
	CheckListBox_org_add();
	CheckListBox_prodvid_add();
	CheckListBox_prod->Clear();
	not_org->Checked=false;
	not_prod_vid->Checked=false;
	not_prod->Checked=false;
}
void __fastcall TForm_gl::CheckListBox_org_add()
{
	CheckListBox_org->Clear();
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT * FROM org ORDER BY name_org ";
	dmod1->q->Open();
	myvector_o.clear();
	while (!dmod1->q->Eof)
	{
		CheckListBox_org->Items->Add(dmod1->q->FieldByName("name_org")->AsAnsiString+", "+dmod1->q->FieldByName("adress_org")->AsAnsiString);
		myvector_o.push_back(dmod1->q->FieldByName("kod_org")->AsInteger);
		dmod1->q->Next();
	}
}
void __fastcall TForm_gl::CheckListBox_prodvid_add()
{
	CheckListBox_prodvid->Clear();
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT kod_prod_vid,name_prod_vid FROM prod_vid ORDER BY name_prod_vid ";
	dmod1->q->Open();
	myvector_v.clear();
	while (!dmod1->q->Eof)
	{
		CheckListBox_prodvid->Items->Add(dmod1->q->FieldByName("name_prod_vid")->AsAnsiString);
		myvector_v.push_back(dmod1->q->FieldByName("kod_prod_vid")->AsInteger);
		dmod1->q->Next();
	}
}
void __fastcall TForm_gl::Mes()
{
	DATE date_zp;

	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT count(*) as m FROM prih_vid inner JOIN prih ON prih_vid.kod_prih_vid = prih.kod_prih_vid_v "
	"WHERE (prih_vid.name_prih_vid='Зарплата') AND Year(data_prih)="+IntToStr(YearOf(Today()))+" AND Month(data_prih)="+IntToStr(ComboBox_mon->ItemIndex+1);
	dmod1->q->Open();
	ComboBox_mon->ItemIndex = -1;
	if(dmod1->q->FieldByName("m")->AsInteger == 0)
	{
		ShowMessage("В этом месяце зарплаты не было!");
		DateTimePicker_n->Date=Date();
		DateTimePicker_k->Date=Date();
		Abort();
	}
	else
	{
		date_zp=dmod1->q->FieldByName("data_prih")->AsDateTime;
		DateTimePicker_n->Date=date_zp;
		DateTimePicker_k->Date=date_zp+30;
	}
}
//----------------------------------------------------------------------------
void __fastcall TForm_gl::itog()
{
	switch (flag_ovp)
	{
		case 0:
				dmod1->ADOQ_del->Close();
				dmod1->ADOQ_del->SQL->Text="SELECT Sum(cena_tr) AS [Sum-cena_tr] FROM trati WHERE "+data;
				dmod1->ADOQ_del->Open();

				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT data_tr, Count(trati.data_tr) AS [Count-data_tr] FROM trati WHERE "+data+" GROUP BY data_tr ORDER BY Count(trati.data_tr);";
				dmod1->q->Open();
		break;
		case 1:
				dmod1->ADOQ_del->Close();
				dmod1->ADOQ_del->SQL->Text="SELECT Sum(cena_tr) AS [Sum-cena_tr] FROM org RIGHT JOIN trati ON org.kod_org = trati.kod_org_tr WHERE "+s1+" AND "+data;
				dmod1->ADOQ_del->Open();

				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT data_tr, Count(trati.data_tr) AS [Count-data_tr] FROM org RIGHT JOIN trati ON org.kod_org = trati.kod_org_tr WHERE "+s1+" AND "+data+" GROUP BY data_tr ORDER BY Count(trati.data_tr);";
				dmod1->q->Open();
		break;
		case 2:
				dmod1->ADOQ_del->Close();
				dmod1->ADOQ_del->SQL->Text="SELECT Sum(cena_tr) AS [Sum-cena_tr] FROM trati LEFT JOIN (prod LEFT JOIN prod_vid ON prod.kod_prod_vid_v = prod_vid.kod_prod_vid) ON trati.kod_prod_tr = prod.kod_prod  WHERE "+s2+" AND "+data;
				dmod1->ADOQ_del->Open();

				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT data_tr, Count(trati.data_tr) AS [Count-data_tr] FROM trati LEFT JOIN (prod LEFT JOIN prod_vid ON prod.kod_prod_vid_v = prod_vid.kod_prod_vid) ON trati.kod_prod_tr = prod.kod_prod WHERE "+s2+" AND "+data+" GROUP BY data_tr ORDER BY Count(trati.data_tr);";
				dmod1->q->Open();
		break;
		case 3:
				dmod1->ADOQ_del->Close();
				dmod1->ADOQ_del->SQL->Text="SELECT Sum(cena_tr) AS [Sum-cena_tr] FROM prod_vid RIGHT JOIN (prod RIGHT JOIN (org RIGHT JOIN trati ON org.kod_org = trati.kod_org_tr) ON prod.kod_prod = trati.kod_prod_tr) ON prod_vid.kod_prod_vid = prod.kod_prod_vid_v WHERE "+s1+" AND "+s2+" AND "+data;
				dmod1->ADOQ_del->Open();

				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT data_tr, Count(trati.data_tr) AS [Count-data_tr] FROM prod_vid RIGHT JOIN (prod RIGHT JOIN (org RIGHT JOIN trati ON org.kod_org = trati.kod_org_tr) ON prod.kod_prod = trati.kod_prod_tr) ON prod_vid.kod_prod_vid = prod.kod_prod_vid_v WHERE "+s1+" AND "+s2+" AND "+data+" GROUP BY data_tr ORDER BY Count(trati.data_tr);";
				dmod1->q->Open();
		break;
		case 6:
				dmod1->ADOQ_del->Close();
				dmod1->ADOQ_del->SQL->Text="SELECT Sum(cena_tr) AS [Sum-cena_tr] FROM trati LEFT JOIN (prod LEFT JOIN prod_vid ON prod.kod_prod_vid_v = prod_vid.kod_prod_vid) ON trati.kod_prod_tr = prod.kod_prod WHERE "+s2+s3+" AND "+data;
				dmod1->ADOQ_del->Open();

				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT data_tr, Count(trati.data_tr) AS [Count-data_tr] FROM trati LEFT JOIN (prod LEFT JOIN prod_vid ON prod.kod_prod_vid_v = prod_vid.kod_prod_vid) ON trati.kod_prod_tr = prod.kod_prod WHERE "+s2+s3+" AND "+data+" GROUP BY data_tr ORDER BY Count(trati.data_tr);";
				dmod1->q->Open();
		break;
		case 7:
				dmod1->ADOQ_del->Close();
				dmod1->ADOQ_del->SQL->Text="SELECT Sum(cena_tr) AS [Sum-cena_tr] FROM prod_vid RIGHT JOIN (prod RIGHT JOIN (org RIGHT JOIN trati ON org.kod_org = trati.kod_org_tr) ON prod.kod_prod = trati.kod_prod_tr) ON prod_vid.kod_prod_vid = prod.kod_prod_vid_v WHERE "+s1+" AND "+s2+s3+" AND "+data;
				dmod1->ADOQ_del->Open();

				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT data_tr, Count(trati.data_tr) AS [Count-data_tr] FROM prod_vid RIGHT JOIN (prod RIGHT JOIN (org RIGHT JOIN trati ON org.kod_org = trati.kod_org_tr) ON prod.kod_prod = trati.kod_prod_tr) ON prod_vid.kod_prod_vid = prod.kod_prod_vid_v WHERE "+s1+" AND "+s2+s3+" AND "+data+" GROUP BY data_tr ORDER BY Count(trati.data_tr);";
				dmod1->q->Open();
		break;
		default: break;
	}
	Form_it->sum_tr->Caption=IntToStr(dmod1->ADOQ_del->FieldByName("Sum-cena_tr")->AsInteger)+" p";

	Form_it->sum_day->Caption=dmod1->q->RecordCount;
	Form_it->GroupBox4->Caption="Расчетный период с "+DateToStr(DateTimePicker_n->Date)+" по "+DateToStr(DateTimePicker_k->Date);
	Form_it->ShowModal();
}
void __fastcall TForm_gl::ApplicationEvents1Hint(TObject *Sender)
{
	StatusBar1->Panels->Items[0]->Text = " "+Application->Hint;
}
//---------------------------------------------------------------------------
void __fastcall TForm_gl::CheckListBox_orgClick(TObject *Sender)
{
	if (CheckListBox_org->ItemIndex!=-1)
	{
		if (!CheckListBox_org->Checked[CheckListBox_org->ItemIndex])
		{
			CheckListBox_org->Checked[CheckListBox_org->ItemIndex]=true;
			CheckListBox_org->Hint=CheckListBox_org->Items->Strings[CheckListBox_org->ItemIndex];
		}
		else
		{
			CheckListBox_org->Checked[CheckListBox_org->ItemIndex]=false;
			CheckListBox_org->Hint="";
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_gl::CheckListBox_prodvidClick(TObject *Sender)
{
	if (CheckListBox_prodvid->ItemIndex!=-1)
	{
		if (!CheckListBox_prodvid->Checked[CheckListBox_prodvid->ItemIndex])
		CheckListBox_prodvid->Checked[CheckListBox_prodvid->ItemIndex]=true;
		else
		CheckListBox_prodvid->Checked[CheckListBox_prodvid->ItemIndex]=false;
		CheckListBox_prod->Clear();
		myvector_p.clear();
		int nom=-1,nom_t;
		for (int k = 0; k < CheckListBox_prodvid->Items->Count; k++)
		{
			if (CheckListBox_prodvid->Checked[k])
			{
				dmod1->q->Close();
				dmod1->q->SQL->Text="SELECT * FROM prod WHERE kod_prod_vid_v = "+IntToStr(myvector_v[k])+" ORDER BY name_prod";
				dmod1->q->Open();
				dmod1->q->First();
				CheckListBox_prod->Items->Add(CheckListBox_prodvid->Items->Strings[k]);
				myvector_p.push_back(0);
				nom++; nom_t=nom;
				while (!dmod1->q->Eof)
				{
					CheckListBox_prod->Items->Add(dmod1->q->FieldByName("name_prod")->AsAnsiString);
					myvector_p.push_back(dmod1->q->FieldByName("kod_prod")->AsInteger);
					nom++;
					dmod1->q->Next();
				}
				CheckListBox_prod->Header[nom_t]=true;
			}
		}
	}
}
void __fastcall TForm_gl::CheckListBox_orgClickCheck(TObject *Sender)
{
	if (!CheckListBox_org->Checked[CheckListBox_org->ItemIndex])
	CheckListBox_org->Checked[CheckListBox_org->ItemIndex]=1;
	else
	CheckListBox_org->Checked[CheckListBox_org->ItemIndex]=0;
}
void __fastcall TForm_gl::CheckListBox_prodvidClickCheck(TObject *Sender)
{
	if (!CheckListBox_prodvid->Checked[CheckListBox_prodvid->ItemIndex])
	CheckListBox_prodvid->Checked[CheckListBox_prodvid->ItemIndex]=1;
	else
	CheckListBox_prodvid->Checked[CheckListBox_prodvid->ItemIndex]=0;
}
void __fastcall TForm_gl::CheckListBox_prodClick(TObject *Sender)
{
	if (CheckListBox_prod->ItemIndex!=-1)
	{
		if (!CheckListBox_prod->Checked[CheckListBox_prod->ItemIndex])
		CheckListBox_prod->Checked[CheckListBox_prod->ItemIndex]=1;
		else
		CheckListBox_prod->Checked[CheckListBox_prod->ItemIndex]=0;
    }
}
void __fastcall TForm_gl::CheckListBox_prodClickCheck(TObject *Sender)
{
    if (!CheckListBox_prod->Checked[CheckListBox_prod->ItemIndex])
	CheckListBox_prod->Checked[CheckListBox_prod->ItemIndex]=1;
	else
	CheckListBox_prod->Checked[CheckListBox_prod->ItemIndex]=0;
}
/////////
void __fastcall TForm_gl::FormShortCut(TWMKey &Msg, bool &Handled)
{
	if (Msg.CharCode==27)
	{
		Close();
	}
}
void __fastcall TForm_gl::FormShow(TObject *Sender)
{
	Clear();
}
void __fastcall TForm_gl::CheckListBox_orgMouseLeave(TObject *Sender)
{
	CheckListBox_org->Hint="";
}
//---------------------------------------------------------------------------
void __fastcall TForm_gl::Button1Click(TObject *Sender)
{
	DATE time1,time2;
	time1=DateTimePicker_n->Date;
	time2=DateTimePicker_k->Date;
    if(ComboBox_mon->Text!="")
	Mes();
	else
	if(time1>time2)
	{
		 ShowMessage("Начальная дата не может быть поже конечной");
		 Abort();
	}

	AnsiString s;
	flag_ovp=0;s1="";s2="";s3="";

	Word dayf,monf,yearf;
	DecodeDate(DateTimePicker_n->Date,yearf,monf,dayf);
	AnsiString dat_f=IntToStr(monf)+"/"+IntToStr(dayf)+"/"+IntToStr(yearf);
	Word dayl,monl,yearl;
	DecodeDate(DateTimePicker_k->Date,yearl,monl,dayl);
	AnsiString dat_l=IntToStr(monl)+"/"+IntToStr(dayl)+"/"+IntToStr(yearl);
	data=" ((trati.data_tr) Between #"+dat_f+"# And #"+dat_l+"# ) ";

	int flag1=0;
	int flag4=0;
	s="SELECT * FROM prod_vid inner JOIN (prod inner JOIN (org inner JOIN trati ON org.kod_org = trati.kod_org_tr) ON prod.kod_prod = trati.kod_prod_tr) ON prod_vid.kod_prod_vid = prod.kod_prod_vid_v WHERE ";
	for(int i = 0; i < CheckListBox_org->Items->Count; i++)
	{
		if(CheckListBox_org->Checked[i])
		{
			if(!flag1)
			{
				if(not_org->Checked)
				s1=" org.kod_org not in (";
				else
				s1=" org.kod_org in (";
				flag1=1;
			}
			if(flag4)
			s1+=","+IntToStr(myvector_o[i]);
			else
			{
				s1+=IntToStr(myvector_o[i]);
				flag4=1;
			}
		}
	}
	if(flag1)
	{
		s1+=")";
		s+=s1;
	}
	int flag2=0;
	int flag5=0;
	int flag6=0;
	for (int j = 0; j < CheckListBox_prodvid->Items->Count; j++)
	{
		if(CheckListBox_prodvid->Checked[j])
		{
			if(!flag2&&flag1)
			s+=" AND ";
			flag2=1;
			if(!flag5)
			{
				if(not_prod_vid->Checked)
				s2=" prod_vid.kod_prod_vid not in (";
				else
				s2=" prod_vid.kod_prod_vid in (";
				flag5=1;
			}
			if(flag6)
			s2+=","+IntToStr(myvector_v[j]);
			else
			{
				s2+=IntToStr(myvector_v[j]);
				flag6=1;
			}
		}
	}
	if(flag5)
	{
		s2+=")";
		s+=s2;
	}
	int flag3=0;
	int flag7=0;
	int flag8=0;
	for (int f = 0; f < CheckListBox_prod->Items->Count; f++)
	{
		if(CheckListBox_prod->Checked[f])
		{
			flag3=1;
			if(!flag7)
			{
				if(not_prod->Checked)
				s3=" AND prod.kod_prod not in (";
				else
				s3=" AND prod.kod_prod in (";
				flag7=1;
			}
			if(flag8)
			s3+=","+IntToStr(myvector_p[f]);
			else
			{
				s3+=IntToStr(myvector_p[f]);
				flag8=1;
			}
		}
	}
	if(flag7)
	{
		s3+=")";
		s+=s3;
	}

	if(flag1||flag2)
	s+=" AND ";
	s+=data+" ORDER BY data_tr,name_org,name_prod_vid,name_prod; ";
	dmod1->ADOQ_see->Close();
	dmod1->ADOQ_see->SQL->Text=s;
	dmod1->ADOQ_see->Open();
	dmod1->ADOQ_see->Last();
	dmod1->ADOQ_see->Prior();
	dmod1->ADOQ_see->Next();

	if(flag1)
	flag_ovp=1;
	if(flag2)
	flag_ovp=2;
	if(flag1&flag2)
	flag_ovp=3;
//	if (flag3)
//	flag_ovp=4;
//	if (flag1&flag3)
//	flag_ovp=5;
	if(flag2&flag3)
	flag_ovp=6;
	if(flag1&flag2&flag3)
	flag_ovp=7;
	itog();
}
//---------------------------------------------------------------------------
void __fastcall TForm_gl::Button2Click(TObject *Sender)
{
	Form_it->GroupBox4->Caption="ИТОГИ";
	for (int k = 0; k < CheckListBox_org->Items->Count; k++)
	{
		if (CheckListBox_org->Checked[k])
		CheckListBox_org->Checked[k]=false;
	}
	for (int k = 0; k < CheckListBox_prodvid->Items->Count; k++)
	{
		if (CheckListBox_prodvid->Checked[k])
		CheckListBox_prodvid->Checked[k]=false;
	}
	CheckListBox_prod->Clear();
	not_org->Checked=false;
	not_prod_vid->Checked=false;
	not_prod->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_gl::Button3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

