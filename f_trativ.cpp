//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_trativ.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_trati.h"
#include "f_it.h"
#include "f_org.h"
#include "f_orgv.h"
#include "f_prih.h"
#include "f_prihv.h"
#include "f_prihvid.h"
#include "f_prihvidv.h"
#include "f_prod.h"
#include "f_prodv.h"
#include "f_prodvid.h"
#include "f_prodvidv.h"
#include "f_date.h"
#include "f_visa.h"
#include "f_visav.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_trativ *Form_trativ;
//---------------------------------------------------------------------------
__fastcall TForm_trativ::TForm_trativ(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::FormCreate(TObject *Sender)
{
	dn=Today();
	Word Hour,Min,Sec,MSec;
	DecodeTime(Time(), Hour, Min, Sec, MSec);
	int totom = 86400-3600*Hour-60*Min-Sec+1;
	Timer1->Interval=totom*1000;

	if(!dmod1->ADOConnection1->Connected)
	{
		AnsiString path = GetCurrentDir()+ "\\money.mdb" ;
		if (!FileExists(path))
		{
			ShowMessage("Не найден файл БД. Cоздайте новый файл\nс именеи <money.mdb>, поместив его в\nодну директорию с приложением и \nперезапустите приложение.");
			exit(1);
		}
		else
		{
			dmod1->ADOConnection1->ConnectionString =
			"Provider=Microsoft.Jet.OLEDB.4.0;"
			"User ID=Admin;"
			"Data Source="+path+";"
			"Mode=Share Deny None;"
			"Persist Security Info=False;"
			"Jet OLEDB:System database="";"
			"Jet OLEDB:Registry Path="";"
			"Jet OLEDB:Database Password=aligero;"
			"Jet OLEDB:Engine Type=5;"
			"Jet OLEDB:Database Locking Mode=1;"
			"Jet OLEDB:Global Partial Bulk Ops=2;"
			"Jet OLEDB:Global Bulk Transactions=1;"
			"Jet OLEDB:New Database Password="";"
			"Jet OLEDB:Create System Database=False;"
			"Jet OLEDB:Encrypt Database=False;"
			"Jet OLEDB:Don't Copy Locale on Compact=False;"
			"Jet OLEDB:Compact Without Replica Repair=False;"
			"Jet OLEDB:SFP=False;";
			dmod1->ADOConnection1->Connected = true;

			dmod1->q->Close();
			dmod1->q->SQL->Text="SELECT t_data FROM [data] WHERE id_data=1; ";
			dmod1->q->Open();
			if(YearOf(Today())==YearOf(dmod1->q->FieldByName("t_data")->AsDateTime))
			{
				if(Today()<dmod1->q->FieldByName("t_data")->AsDateTime)
				{
					if(MessageBoxA(0,AnsiString("Системное время ПК меньше времени последней авторизации!\nВы уверенны, что сейчас системное время "+Today().DateString()+" верно?\nЕсли ДА, то время последней авторизации станет текущим!").c_str(),"Подтверждение",MB_OKCANCEL)==IDOK)
					{
						dmod1->q->Close();
						dmod1->q->SQL->Text="UPDATE [data] SET t_data='"+Today().DateString()+"' WHERE id_data=1";
						dmod1->q->ExecSQL();
					}
					else
					exit(1);
				}
				else if(Today()>dmod1->q->FieldByName("t_data")->AsDateTime)
				{
					dmod1->q->Close();
					dmod1->q->SQL->Text="UPDATE [data] SET t_data='"+Today().DateString()+"' WHERE id_data=1";
					dmod1->q->ExecSQL();
				}
			}
			else if(YearOf(Today())>YearOf(dmod1->q->FieldByName("t_data")->AsDateTime))
			{
				if(MessageBoxA(0,AnsiString("Вы уверенны, что сейчас системное время "+Today().DateString()+" верно?\nОтменить изменения будет не возможно!").c_str(),"Подтверждение",MB_OKCANCEL)==IDOK)
				{
					dmod1->q->Close();
					dmod1->q->SQL->Text="UPDATE [data] SET t_data='"+Today().DateString()+"' WHERE id_data=1";
					dmod1->q->ExecSQL();
				}
				else
				exit(1);
            }
			else
			{
				ShowMessage("Год системного времени меньше\nгода последней авторизации!!!");
				exit(1);
            }
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::FormShow(TObject *Sender)
{
	Word day,mon,year;
	DecodeDate(Today(),year,mon,day);
	DATE dd1=Today(),dd2=Today(),dd3=Today();
	//***
	if(Form_date->RadioButton1->Checked)
	{
		dd1=StrToDate("1.1."+IntToStr(year));
		dd2=StrToDate("31.12."+IntToStr(year));
	}
	else if(Form_date->RadioButton2->Checked)
	{
		dd1=StrToDate("1."+IntToStr(mon)+"."+IntToStr(year));
		dd2=StrToDate(IntToStr(DayOf(EndOfAMonth(year,mon)))+"."+IntToStr(mon)+"."+IntToStr(year));
	}
	else if (Form_date->RadioButton3->Checked)
	{
		if(day<7&&mon==1)
		{
			dd1=StrToDate("1.1."+IntToStr(year));
			dd2=StrToDate(IntToStr(DayOf(EndOfTheWeek(Today())))+"."+IntToStr(mon)+"."+IntToStr(year));
		}
		else
		{
			while (DayOfWeek(dd1)!=2)
			dd1--;
			dd2=dd1+6;
		}
	}
	else if(Form_date->RadioButton4->Checked)
	{
		dd1=StrToDate("1.1.2012");
		dd2=StrToDate("31.12."+IntToStr(year));
	}

	int s1,s2,k;
	//приход
	if(!s_prih)
	{
		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT sum_data,sum_p FROM [sum] WHERE id_sum=1; ";
		dmod1->q->Open();
		if(dmod1->q->FieldByName("sum_data")->AsInteger==YearOf(Today()))
		s_prih=dmod1->q->FieldByName("sum_p")->AsInteger;
		else
		{
			//получка
			dmod1->q->Close();
			dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih]";
			dmod1->q->Open();
			s_prih=dmod1->q->FieldByName("m")->AsInteger;
			dmod1->q->Close();
			dmod1->q->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(s_prih)+" WHERE id_sum=1";
			dmod1->q->ExecSQL();
			//траты
			dmod1->q->Close();
			dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati]";
			dmod1->q->Open();
			s_trati=dmod1->q->FieldByName("m")->AsInteger;
			dmod1->q->Close();
			dmod1->q->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(s_trati)+" WHERE id_sum=1";
			dmod1->q->ExecSQL();
			//общее
			dmod1->q->Close();
			dmod1->q->SQL->Text="UPDATE [sum] SET sum_p=0,sum_t=0 WHERE id_sum<>1";
			dmod1->q->ExecSQL();

			dmod1->q->Close();
			dmod1->q->SQL->Text="UPDATE [sum] SET sum_data="+IntToStr(YearOf(Today()))+" WHERE id_sum=1";
			dmod1->q->ExecSQL();
		}
	}
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_p) AS m FROM [sum] WHERE id_sum<>1; ";
	dmod1->q->Open();
	sum_pr->Caption=dmod1->q->FieldByName("m")->AsAnsiString+" p";
	s1=dmod1->q->FieldByName("m")->AsInteger+s_prih;
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT sum_p AS m FROM [sum] WHERE sum_data="+IntToStr(MonthOf(Today()));
	dmod1->q->Open();
	sum_prm->Caption=dmod1->q->FieldByName("m")->AsAnsiString+" p";
	//расход
	if(!s_trati)
	{
		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT sum_t FROM [sum] WHERE id_sum=1; ";
		dmod1->q->Open();
		s_trati=dmod1->q->FieldByName("sum_t")->AsInteger;
	}
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_t) AS m FROM [sum] WHERE id_sum<>1; ";
	dmod1->q->Open();
	sum_tr->Caption=IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" p";
	s2=dmod1->q->FieldByName("m")->AsInteger+s_trati;
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT sum_t AS m FROM [sum] WHERE sum_data="+IntToStr(MonthOf(Today()));
	dmod1->q->Open();
	sum_trm->Caption=IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" p";
	//карточка
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(visa_s) AS m FROM [visa]";
	dmod1->q->Open();
	sum_kr->Caption=IntToStr(k=dmod1->q->FieldByName("m")->AsInteger)+" p";
	//кошелек
	sum_kh->Caption=IntToStr(s1-s2-k)+" p";
	//за неделю
	if(day<7&&mon==1)
	dd3=StrToDate("1.1."+IntToStr(year));
	else while(DayOfWeek(dd3)!=2)
	dd3--;

	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM trati WHERE (data_tr Between :p1 And :p2)";
	dmod1->q->Parameters->ParamByName("p1")->Value=DateToStr(dd3);
	dmod1->q->Parameters->ParamByName("p2")->Value=DateToStr(dd3+6);
	dmod1->q->Open();
	sum_trn->Caption=IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" p";

	dmod1->q->Close();
	dmod1->q->Parameters->ParamByName("p1")->Value=Today();
	dmod1->q->Parameters->ParamByName("p2")->Value=Today();
	dmod1->q->Open();
	sum_trd->Caption=IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" p";
	//таблица
	dmod1->q_trati->Close();
	dmod1->q_trati->Parameters->ParamByName("org")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_trati->Parameters->ParamByName("prod_vid")->Value=Trim(Edit2->Text)+"%";
	dmod1->q_trati->Parameters->ParamByName("prod")->Value=Trim(Edit3->Text)+"%";
	dmod1->q_trati->Parameters->ParamByName("par1")->Value=DateToStr(dd1);
	dmod1->q_trati->Parameters->ParamByName("par2")->Value=DateToStr(dd2);
	dmod1->q_trati->Open();
	if (dmod1->q_trati->RecordCount)
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
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::ToolButton5Click(TObject *Sender)
{
    if (ToolButton4->Enabled)
	if(MessageBoxA(0,"Вы действительно хотите удалить выбранную запись?","Подтверждение",MB_OKCANCEL)==IDOK)
	{
		DATE d=dmod1->q_trati->FieldByName("data_tr")->AsDateTime;
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text="DELETE FROM trati WHERE kod_pokup = "+IntToStr(dmod1->q_trati->FieldByName("kod_pokup")->AsInteger)+";";
		dmod1->ADOQ_Work->ExecSQL();

		if(YearOf(d)==YearOf(Today()))
		{
			dmod1->q->Close();
			dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati] WHERE Year(data_tr)="+IntToStr(YearOf(d))+" AND Month(data_tr)="+IntToStr(MonthOf(d));
			dmod1->q->Open();
			dmod1->ADOQ_del->Close();
			dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(MonthOf(d));
			dmod1->ADOQ_del->ExecSQL();
		}
		else
		{
			dmod1->q->Close();
			dmod1->q->SQL->Text="SELECT Sum(cena_tr) AS m FROM [trati] WHERE Year(data_tr)<"+IntToStr(YearOf(Today()));
			dmod1->q->Open();
			dmod1->ADOQ_del->Close();
			dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_t="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE id_sum=1;";
			dmod1->ADOQ_del->ExecSQL();

			Form_trativ->s_trati=0;
		}
		FormShow(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::Edit1Change(TObject *Sender)
{
	dmod1->q_trati->Close();
	dmod1->q_trati->Parameters->ParamByName("org")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_trati->Parameters->ParamByName("prod_vid")->Value=Trim(Edit2->Text)+"%";
	dmod1->q_trati->Parameters->ParamByName("prod")->Value=Trim(Edit3->Text)+"%";
	dmod1->q_trati->Open();
	if (dmod1->q_trati->RecordCount)
	{
		ToolButton4->Enabled=1;
		ToolButton5->Enabled=1;
	}
	else
	{
		ToolButton4->Enabled=0;
		ToolButton5->Enabled=0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
//		case '17'+'90': N1->Click(); break;
		case VK_ESCAPE:
			if(MessageBoxA(0,"Вы действительно хотите выйти?","Подтверждение",MB_OKCANCEL)==IDOK)
			Close();
		break;
		case VK_F11: 	ToolButton8->Click(); break;
		case VK_F12: 	ToolButton7->Click(); break;
		case VK_INSERT: ToolButton2->Click(); break;
		case VK_RETURN: ToolButton4->Click(); break;
		case VK_DELETE: ToolButton5->Click(); break;
		case VK_SPACE: {Edit1->Text="";Edit2->Text="";Edit3->Text="";} break;
		default: break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, TGridDrawState State)
{
	if(dmod1->q_trati->FieldByName("data_tr")->AsDateTime==Today())
	{
	   DBGrid1->Canvas->Brush->Color  = clWebLightgrey;
	   DBGrid1->Canvas->Font->Color  =  clBlack;
	   DBGrid1->Canvas->FillRect(Rect);
	   DBGrid1->Canvas->TextOut(Rect.left+3,Rect.Top,Column->Field->Text);
	}
	else if(State.Contains(gdSelected))
	{
		DBGrid1->Canvas->Brush->Color  = clWebLightCoral;
		DBGrid1->Canvas->Font->Color  =  clBlack;
	}
	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::DBGrid1DblClick(TObject *Sender)
{
	ToolButton4Click(Sender);
}

void __fastcall TForm_trativ::ToolButton2Click(TObject *Sender)
{
	f_trati=0;
	if (!Form_trati)
	{
		Application->CreateForm(__classid(TForm_trati), &Form_trati);
		Form_trati->Show();
	}
	else
	{
		if (IsIconic(Form_trati->Handle))
		Form_trati->WindowState = wsNormal;
		Form_trati->Show();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::ToolButton4Click(TObject *Sender)
{
	if (ToolButton4->Enabled)
	{
		f_trati=1;
		if (!Form_trati)
		{
			Application->CreateForm(__classid(TForm_trati), &Form_trati);
			Form_trati->Show();
		}
		else
		{
			if (IsIconic(Form_trati->Handle))
			Form_trati->WindowState = wsNormal;
			Form_trati->Show();
		}
	}
}
void __fastcall TForm_trativ::ToolButton7Click(TObject *Sender)
{
	Form_gl->Show();
}
void __fastcall TForm_trativ::N10Click(TObject *Sender)
{
	Close();
}
void __fastcall TForm_trativ::N12Click(TObject *Sender)
{
	if (!Form_prodv)
	{
		Application->CreateForm(__classid(TForm_prodv), &Form_prodv);
		Form_prodv->Show();
	}
	else
	{
		if (IsIconic(Form_prodv->Handle))
		Form_prodv->WindowState = wsNormal;
		Form_prodv->Show();
	}
}
void __fastcall TForm_trativ::N13Click(TObject *Sender)
{
	if (!Form_prodvidv)
	{
		Application->CreateForm(__classid(TForm_prodvidv), &Form_prodvidv);
		Form_prodvidv->Show();
	}
	else
	{
		if (IsIconic(Form_prodvidv->Handle))
		Form_prodvidv->WindowState = wsNormal;
		Form_prodvidv->Show();
	}
}
void __fastcall TForm_trativ::N11Click(TObject *Sender)
{
	if (!Form_orgv)
	{
		Application->CreateForm(__classid(TForm_orgv), &Form_orgv);
		Form_orgv->Show();
	}
	else
	{
		if (IsIconic(Form_orgv->Handle))
		Form_orgv->WindowState = wsNormal;
		Form_orgv->Show();
	}
}
void __fastcall TForm_trativ::N15Click(TObject *Sender)
{
	if (!Form_prihv)
	{
		Application->CreateForm(__classid(TForm_prihv), &Form_prihv);
		Form_prihv->Show();
	}
	else
	{
		if (IsIconic(Form_prihv->Handle))
		Form_prihv->WindowState = wsNormal;
		Form_prihv->Show();
	}
}
void __fastcall TForm_trativ::N16Click(TObject *Sender)
{
	if (!Form_prihvidv)
	{
		Application->CreateForm(__classid(TForm_prihvidv), &Form_prihvidv);
		Form_prihvidv->Show();
	}
	else
	{
		if (IsIconic(Form_prihvidv->Handle))
		Form_prihvidv->WindowState = wsNormal;
		Form_prihvidv->Show();
	}
}
void __fastcall TForm_trativ::N18Click(TObject *Sender)
{
	if(!fr_visav)
	{
		Application->CreateForm(__classid(Tfr_visav), &fr_visav);
		fr_visav->Show();
	}
	else
	{
		if(IsIconic(fr_visav->Handle))
		fr_visav->WindowState = wsNormal;
		fr_visav->Show();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::N1Click(TObject *Sender)
{
	WinExec("Calc.exe", SW_RESTORE);
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::ASC1Click(TObject *Sender)
{
	dmod1->q_trati->Sort="data_tr ASC";
}
void __fastcall TForm_trativ::DESC1Click(TObject *Sender)
{
	dmod1->q_trati->Sort="data_tr DESC";
}
void __fastcall TForm_trativ::ASC2Click(TObject *Sender)
{
	dmod1->q_trati->Sort="name_org ASC";
}
void __fastcall TForm_trativ::DESC2Click(TObject *Sender)
{
	dmod1->q_trati->Sort="name_org DESC";
}
void __fastcall TForm_trativ::ASC3Click(TObject *Sender)
{
	dmod1->q_trati->Sort="name_prod_vid ASC";
}
void __fastcall TForm_trativ::DESC3Click(TObject *Sender)
{
	dmod1->q_trati->Sort="name_prod_vid DESC";
}
void __fastcall TForm_trativ::N14Click(TObject *Sender)
{
	dmod1->q_trati->Sort="name_prod ASC";
}
void __fastcall TForm_trativ::N17Click(TObject *Sender)
{
	dmod1->q_trati->Sort="name_prod DESC";
}
void __fastcall TForm_trativ::ASC4Click(TObject *Sender)
{
	dmod1->q_trati->Sort="cena_tr ASC";
}
void __fastcall TForm_trativ::DESC4Click(TObject *Sender)
{
	dmod1->q_trati->Sort="cena_tr DESC";
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::ToolButton8Click(TObject *Sender)
{
	Form_date->ShowModal();
}
void __fastcall TForm_trativ::ToolButton11Click(TObject *Sender)
{
	Close();
}
void __fastcall TForm_trativ::N3Click(TObject *Sender)
{
	Form_it->excel_exp();
}
void __fastcall TForm_trativ::N4Click(TObject *Sender)
{
	Form_it->pr_tr0(2);
}
void __fastcall TForm_trativ::N5Click(TObject *Sender)
{
	Form_it->pr_tr0(3);
}
void __fastcall TForm_trativ::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_trativ = NULL;
	Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TForm_trativ::Timer1Timer(TObject *Sender)
{
	if(YearOf(dn)!=YearOf(Today()))
	{
		if(MessageBoxA(0,AnsiString("Вы уверенны, что сейчас системное время "+Today().DateString()+" верно?\nОтменить изменения будет не возможно!").c_str(),"Подтверждение",MB_OKCANCEL)!=IDOK)
		exit(1);

		s_prih=0;
		s_trati=0;
	}
	dn=Today();
	dmod1->q->Close();
	dmod1->q->SQL->Text="UPDATE [data] SET t_data='"+Today().DateString()+"' WHERE id_data=1";
	dmod1->q->ExecSQL();

	FormShow(Sender);

	Timer1->Interval= 24 * 60 * 60 * 1000;
}
//---------------------------------------------------------------------------


