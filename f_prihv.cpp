//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "f_prihv.h"
#include "f_dmod.h"
#include "f_gl.h"
#include "f_prih.h"
#include "f_trativ.h"
#include "f_it.h"
#include "f_visav.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_prihv *Form_prihv;
//---------------------------------------------------------------------------
__fastcall TForm_prihv::TForm_prihv(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::ToolButton2Click(TObject *Sender)
{
	Form_trativ->f_prih=0;
	if (!Form_prih)
	{
		Application->CreateForm(__classid(TForm_prih), &Form_prih);
		Form_prih->ShowModal();
	}
	else
	{
		if (IsIconic(Form_prih->Handle))
		Form_prih->WindowState = wsNormal;
		Form_prih->ShowModal();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::ToolButton4Click(TObject *Sender)
{
	if (ToolButton4->Enabled)
	{
		Form_trativ->f_prih=1;
		if (!Form_prih)
		{
			Application->CreateForm(__classid(TForm_prih), &Form_prih);
			Form_prih->ShowModal();
		}
		else
		{
			if (IsIconic(Form_prih->Handle))
			Form_prih->WindowState = wsNormal;
			Form_prih->ShowModal();
		}
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::ToolButton5Click(TObject *Sender)
{
	if (ToolButton4->Enabled)
	if(MessageBoxA(0,"Вы действительно хотите удалить выбранную запись?","Подтверждение",MB_OKCANCEL)==IDOK)
	{
		DATE d=dmod1->q_prih->FieldByName("data_prih")->AsDateTime;
		dmod1->ADOQ_Work->Close();
		dmod1->ADOQ_Work->SQL->Text="DELETE FROM prih WHERE kod_prih = "+IntToStr(dmod1->q_prih->FieldByName("kod_prih")->AsInteger)+";";
		dmod1->ADOQ_Work->ExecSQL();

		if(YearOf(d)==YearOf(Today()))
		{
			dmod1->q->Close();
			dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih] WHERE Year(data_prih)="+IntToStr(YearOf(d))+" AND Month(data_prih)="+IntToStr(MonthOf(d));
			dmod1->q->Open();
			dmod1->ADOQ_del->Close();
			dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE sum_data="+IntToStr(MonthOf(d));
			dmod1->ADOQ_del->ExecSQL();
		}
		else
		{
			dmod1->q->Close();
			dmod1->q->SQL->Text="SELECT Sum(sum_prih) AS m FROM [prih] WHERE Year(data_prih)<"+IntToStr(YearOf(Today()));
			dmod1->q->Open();
			dmod1->ADOQ_del->Close();
			dmod1->ADOQ_del->SQL->Text="UPDATE [sum] SET sum_p="+IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" WHERE id_sum=1;";
			dmod1->ADOQ_del->ExecSQL();

			Form_trativ->s_prih=0;
		}
		FormShow(Sender);
		Form_trativ->FormShow(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::ToolButton7Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form_prihv = NULL;
	Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
switch (Key)
	{
		case VK_ESCAPE: Close(); break;
		case VK_INSERT: ToolButton2->Click(); break;
		case VK_RETURN: ToolButton4->Click(); break;
		case VK_DELETE: ToolButton5->Click(); break;
		case VK_F12: 	ToolButton8->Click(); break;
		case VK_SPACE:  Edit1->Text=""; break;
		default: break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::FormShow(TObject *Sender)
{
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_p) AS m FROM [sum]";
	dmod1->q->Open();
	sum_p1->Caption=IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" p";
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT Sum(sum_p) AS m FROM [sum] WHERE id_sum<>1";
	dmod1->q->Open();
	sum_p2->Caption=IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" p";
	dmod1->q->Close();
	dmod1->q->SQL->Text="SELECT sum_p AS m FROM [sum] WHERE sum_data="+IntToStr(MonthOf(Today()));;
	dmod1->q->Open();
	sum_p3->Caption=IntToStr(dmod1->q->FieldByName("m")->AsInteger)+" p";

	dmod1->q_prih->Close();
	dmod1->q_prih->Parameters->ParamByName("name")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_prih->Open();
	if (dmod1->q_prih->RecordCount)
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
void __fastcall TForm_prihv::DBGrid1DblClick(TObject *Sender)
{
	ToolButton4Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
	if (State.Contains(gdSelected))
	{
		DBGrid1->Canvas->Brush->Color  = clWebLightCoral;
		DBGrid1->Canvas->Font->Color  = clBlack;
	}

	DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::ToolButton8Click(TObject *Sender)
{
	Form_it->pr_tr0(1);
}
//---------------------------------------------------------------------------
void __fastcall TForm_prihv::Edit1Change(TObject *Sender)
{
 	dmod1->q_prih->Close();
	dmod1->q_prih->Parameters->ParamByName("name")->Value=Trim(Edit1->Text)+"%";
	dmod1->q_prih->Open();
	if (dmod1->q_prih->RecordCount)
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
void __fastcall TForm_prihv::ToolButton11Click(TObject *Sender)
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

