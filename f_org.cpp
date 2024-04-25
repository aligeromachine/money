//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_org.h"
#include "f_dmod.h"
#include "f_orgv.h"
#include "f_gl.h"
#include "f_trati.h"
#include "f_trativ.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_org *Form_org;
org_sv *org_old;
//---------------------------------------------------------------------------
__fastcall TForm_org::TForm_org(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_org::Button3Click(TObject *Sender)
{
	Close();
}
void __fastcall TForm_org::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete org_old;
	Form_org = NULL;
	Action=caFree;
}
inline void TForm_org::Edit_Clear()
{
	Edit_name->Text="";
	Edit_adress->Text="";
	Button2->Enabled=0;

	this->sv->Clear();
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT kod_prod_vid,name_prod_vid FROM prod_vid ORDER BY name_prod_vid";
	dmod1->q->Open();
	this->vect_sv.clear();
	while (!dmod1->q->Eof)
	{
		this->sv->Items->Add(dmod1->q->FieldByName("name_prod_vid")->AsAnsiString);
		this->vect_sv.push_back(dmod1->q->FieldByName("kod_prod_vid")->AsInteger);
		dmod1->q->Next();
	}
}
void __fastcall TForm_org::Edit_nameChange(TObject *Sender)
{
	Button2->Enabled=1;
}
void __fastcall TForm_org::Button1Click(TObject *Sender)
{
	AnsiString str1;
	int org=0;
	bool fl1=false;

	if(Edit_name->Text=="")
	{
		ShowMessage("Поле Наименование не должно быть пустое!");
		Edit_name->SetFocus();
		return;
	}
	if(Edit_adress->Text=="")
	{
		ShowMessage("Поле Адрес не должно быть пустое!");
		Edit_adress->SetFocus();
		return;
	}
	for(int i=0; i<this->sv->Count; i++)
	{
		if(this->sv->Checked[i])
			fl1=1;
	}
	if(!fl1)
	{
		ShowMessage("Связь с типом продуктов не должна быть пустая!");
		return;
	}

	str1="SELECT count(*) as m FROM org WHERE name_org= '"+Edit_name->Text.Trim()+"' AND adress_org='"+Edit_adress->Text.Trim()+"'";
	if(Form_trativ->f_org)
	str1+=" AND kod_org<>"+dmod1->q_org->FieldByName("kod_org")->AsAnsiString;
	dmod1->q->Close();
	dmod1->q->SQL->Text=str1;
	dmod1->q->Open();
	if(dmod1->q->FieldByName("m")->AsInteger != 0)
	{
		ShowMessage("Такая запись уже есть!");
		return;
	}

	if(Form_trativ->f_org)
	{
		str1="UPDATE org SET ";
		str1+="name_org = '" + Edit_name->Text.Trim() + "',";
		str1+="adress_org = '" + Edit_adress->Text.Trim() + "'";
		str1+=" WHERE kod_org ="+dmod1->q_org->FieldByName("kod_org")->AsAnsiString;
		org=dmod1->q_org->FieldByName("kod_org")->AsInteger;
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str1;
		dmod1->ADOQ_Work->ExecSQL();

		std::vector<array_boost> vec1 = std::vector<array_boost>(this->sv->Count);
		for (int i = 0; i < this->sv->Count; i++)
		{
			if(this->sv->Checked[i])
			{
				vec1[i][0] = 1;
				vec1[i][1] = this->vect_sv[i];
			}
			else
			{
				vec1[i][0] = 0;
				vec1[i][1] = this->vect_sv[i];
			}
		}

		org_sv * org_new = new org_sv(org,Edit_name->Text.Trim(),Edit_adress->Text.Trim(),vec1);
		org_old->compera(org_new);
		delete org_new;
		org_old->obnovlenie();
	}
	else
	{
		str1 = "INSERT INTO org (";
		str1 += "name_org,";
		str1 += "adress_org";
		str1 += ") VALUES (";
		str1 += "'" + Edit_name->Text.Trim() + "',";
		str1 += "'" + Edit_adress->Text.Trim() + "')";
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text=str1;
		dmod1->ADOQ_Work->ExecSQL();

		dmod1->q->Close();
		dmod1->q->SQL->Text="SELECT Max(kod_org) AS kod FROM org ";
		dmod1->q->Open();
		org=dmod1->q->FieldByName("kod")->AsInteger;

		std::vector<array_boost> vec1 = std::vector<array_boost>(this->sv->Count);
		for (int i = 0; i < this->sv->Count; i++)
		{
			if(this->sv->Checked[i])
			{
				vec1[i][0] = 1;
				vec1[i][1] = this->vect_sv[i];
			}
			else
			{
				vec1[i][0] = 0;
				vec1[i][1] = this->vect_sv[i];
			}
		}
		org_old->set_org_sv(org, Edit_name->Text.Trim(), Edit_adress->Text.Trim(), vec1);
		org_old->dobavlenie();

		Edit_Clear();
		Edit_name->SetFocus();
	}

	if(Form_orgv)
	{
		Form_orgv->FormShow(Sender);
		dmod1->q_org->Locate("kod_org",org,TLocateOptions()<<loPartialKey);
	}

	Form_gl->CheckListBox_org_add();

	if(Form_trati)
	{
        Form_trati->org_add();
		Form_trati->n_org->ItemIndex=find(Form_trati->id_org.begin(),Form_trati->id_org.end(),org)-Form_trati->id_org.begin();
		Form_trati->n_orgChange(Sender);
		if(Form_trativ->f_trati_cl1)
		{
			Form_trativ->f_trati_cl1=0;
			Form_trati->n_prod_vid->SetFocus();
			Close();
		}
	}

	if(Form_trativ->f_org)
	{
		Form_trativ->FormShow(Sender);
		Close();
	}
}
void __fastcall TForm_org::FormShortCut(TWMKey &Msg, bool &Handled)
{
	switch (Msg.CharCode)
	{
		case 27: Close(); break;
		case 13:Button1->Click();Msg.CharCode=0;break;
		default: break;
	}
}
void __fastcall TForm_org::FormShow(TObject *Sender)
{
	org_old = new org_sv();
	Edit_Clear();
	if(Form_trativ->f_org)
	{
		Caption="Изменение данных компании";
		Edit_name->Text=dmod1->q_org->FieldByName("name_org")->AsAnsiString;
		Edit_adress->Text=dmod1->q_org->FieldByName("adress_org")->AsAnsiString;
		dmod1->q->Close();
		dmod1->q->SQL->Text = "select id_prod_vid_v from org_sv where id_org_v = " + dmod1->q_org->FieldByName("kod_org")->AsAnsiString;
		dmod1->q->Open();
		std::vector<array_boost> v_temp = std::vector<array_boost>(this->vect_sv.size());
		for (int i = 0; i < this->vect_sv.size(); i++)
		{
			v_temp[i][0] = 0;
			v_temp[i][1] = this->vect_sv[i];
		};
		while (!dmod1->q->Eof)
		{
			int k = find_if(this->vect_sv.begin(),this->vect_sv.end(),MyClassComp(dmod1->q->FieldByName("id_prod_vid_v")->AsInteger))-this->vect_sv.begin();
			this->sv->Checked[k] = true;
			v_temp[k][0] = 1;
			dmod1->q->Next();
		}
		Button2->Enabled=0;
		org_old->set_org_sv(dmod1->q_org->FieldByName("kod_org")->AsInteger,Edit_name->Text,Edit_adress->Text,v_temp);
	}
	/* или лямбда
	int k = find_if(this->vect_sv.begin(),this->vect_sv.end(),MyClassComp(dmod1->q->FieldByName("id_prod_vid_v")->AsInteger))-this->vect_sv.begin();
	
	int val = dmod1->q->FieldByName("id_prod_vid_v")->AsInteger;
	int k = find_if(this->vect_sv.begin(),this->vect_sv.end(),[&val](const int& vect){return val == vect})
		
	*/
}

void __fastcall TForm_org::svClick(TObject *Sender)
{
	if (this->sv->ItemIndex!=-1)
	{
		if(!this->sv->Checked[this->sv->ItemIndex])
		this->sv->Checked[this->sv->ItemIndex]=true;
		else
		this->sv->Checked[this->sv->ItemIndex]=false;
	}

	/*std::vector<int> numbers = std::vector<int>();
	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);
	numbers.push_back(4);
	numbers.push_back(5);
	numbers.push_back(10);
	numbers.push_back(15);
	numbers.push_back(20);
	numbers.push_back(25);
	numbers.push_back(35);
	numbers.push_back(45);
	numbers.push_back(50);
	auto great_than_5_count = count_if(numbers.begin(), numbers.end(), [](int x) { return (x > 5); });
    cout << "The number of elements greater than 5 is: "
		 << greater_than_5_count << "." << endl;   */
}
//---------------------------------------------------------------------------

void __fastcall TForm_org::svClickCheck(TObject *Sender)
{
	if(!this->sv->Checked[this->sv->ItemIndex])
	this->sv->Checked[this->sv->ItemIndex]=1;
	else
	this->sv->Checked[this->sv->ItemIndex]=0;
}
//---------------------------------------------------------------------------

void org_sv::dobavlenie()
{
	for (int i = 0; i < this->sv_pv.size(); i++)
	{
		if (this->sv_pv[i][0]==1)
		{
			AnsiString str;
			str = "insert into org_sv (id_org_v,id_prod_vid_v) values ";
			str += "(" + AnsiString(this->id_org) + "," + AnsiString(this->sv_pv[i][1]) + ")";
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text=str;
			dmod1->ADOQ_Work->ExecSQL();
		}
	}
}

void org_sv::compera(const org_sv* old)
{
	for (int i = 0; i < this->sv_pv.size(); i++)
	{
		if (this->sv_pv[i][0] != old->sv_pv[i][0])
		{
			if (this->sv_pv[i][0] == 0)
				this->sv_pv[i][0] = 2;
			else
				this->sv_pv[i][0] = 3;
        }
	}
}

void org_sv::obnovlenie()
{
	for (int i = 0; i < this->sv_pv.size(); i++)
	{
		if (this->sv_pv[i][0]==2)
		{
			AnsiString strn;
			strn = "insert into org_sv (id_org_v,id_prod_vid_v) values ";
			strn += "(" + AnsiString(this->id_org) + "," + AnsiString(this->sv_pv[i][1]) + ")";
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text=strn;
			dmod1->ADOQ_Work->ExecSQL();
		}
		else if (this->sv_pv[i][0]==3)
		{
			AnsiString strn =  " SELECT count (*) as m ";
			strn += " FROM org ";
			strn += " INNER JOIN  ";
			strn += " ((prod_vid INNER JOIN prod ON prod_vid.kod_prod_vid = prod.kod_prod_vid_v)  ";
			strn += "  			 INNER JOIN trati ON prod.kod_prod = trati.kod_prod_tr)  ";
			strn += " ON org.kod_org = trati.kod_org_tr  ";
			strn += " where kod_org = " + AnsiString(this->id_org);
			strn += " and kod_prod_vid = " + AnsiString(this->sv_pv[i][1]);
			dmod1->ADOQ_del->Close();
			dmod1->ADOQ_del->SQL->Text=strn;
			dmod1->ADOQ_del->Open();
			if (dmod1->ADOQ_del->FieldByName("m")->AsInteger != 0){
				strn =  "Нельзя удалить у магазина \"" + this->name + "\"";
				strn += "\nсвязь с продуктом \"" + Form_org->sv->Items->Strings[i] + "\"";
				strn += "\n т.к. есть записи в таблице Траты! Целых " + dmod1->ADOQ_del->FieldByName("m")->AsString + " шт." ;
				ShowMessage(strn);
				continue;
			}
			strn = "delete from org_sv where id_org_v = " + AnsiString(this->id_org);
			strn += " and id_prod_vid_v = " + AnsiString(this->sv_pv[i][1]) + ";";
			dmod1->ADOQ_Work->Close();
			dmod1->ADOQ_Work->SQL->Text=strn;
			dmod1->ADOQ_Work->ExecSQL();
        }
	}
}

void __fastcall TForm_org::Button4Click(TObject *Sender)
{
	for (int i = 0; i < this->sv->Count; i++)
		this->sv->Checked[i] = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm_org::Button5Click(TObject *Sender)
{
   	for (int i = 0; i < this->sv->Count; i++)
		this->sv->Checked[i] = false;
}
//---------------------------------------------------------------------------

