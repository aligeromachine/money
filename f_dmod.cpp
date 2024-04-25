//---------------------------------------------------------------------------


#pragma hdrstop

#include "f_dmod.h"
#include "f_prodv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "System.Classes.TPersistent"
#pragma resource "*.dfm"
Tdmod1 *dmod1;
//---------------------------------------------------------------------------
__fastcall Tdmod1::Tdmod1(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tdmod1::q_orgCalcFields(TDataSet *DataSet)
{
	if (dmod1->q_org->RecNo==-1) {
		dmod1->q_org->FieldByName("nom")->Value=1;
	}
	else
	dmod1->q_org->FieldByName("nom")->Value=dmod1->q_org->RecNo;
}
//---------------------------------------------------------------------------
void __fastcall Tdmod1::q_prodvidCalcFields(TDataSet *DataSet)
{
	if (dmod1->q_prodvid->RecNo==-1) {
		dmod1->q_prodvid->FieldByName("nom")->Value=1;
	}
	else
	dmod1->q_prodvid->FieldByName("nom")->Value=dmod1->q_prodvid->RecNo;
}
//---------------------------------------------------------------------------
void __fastcall Tdmod1::q_prodCalcFields(TDataSet *DataSet)
{
	if (dmod1->q_prod->RecNo==-1) {
		dmod1->q_prod->FieldByName("nom")->Value=1;
	}
	else
	dmod1->q_prod->FieldByName("nom")->Value=dmod1->q_prod->RecNo;
}
//---------------------------------------------------------------------------
