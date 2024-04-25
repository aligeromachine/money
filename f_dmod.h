//---------------------------------------------------------------------------

#ifndef f_dmodH
#define f_dmodH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class Tdmod1 : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *ADOConnection1;
	TADOQuery *ADOQ_Work;
	TDataSource *s_prihvid;
	TADOQuery *ADOQ_see;
	TDataSource *DS_it;
	TIntegerField *ADOQ_seenom;
	TStringField *ADOQ_seename_org;
	TStringField *ADOQ_seename_prod_vid;
	TStringField *ADOQ_seename_prod;
	TDateTimeField *ADOQ_seedata_tr;
	TStringField *ADOQ_seeprim_tr;
	TADOQuery *q_prod;
	TDataSource *s_prod;
	TADOQuery *q_trati;
	TDataSource *s_trati;
	TADOQuery *q_prih;
	TDataSource *s_prih;
	TIntegerField *q_prodkod_prod;
	TIntegerField *q_prodnom_prod;
	TStringField *q_prodname_prod_vid;
	TStringField *q_prodname_prod;
	TStringField *ADOQ_seekol_ed_tr;
	TADOQuery *ADOQ_del;
	TADOQuery *q;
	TADOQuery *q_org;
	TADOQuery *q_prodvid;
	TDataSource *s_org;
	TDataSource *s_prodvid;
	TIntegerField *q_orgkod_org;
	TStringField *q_orgname_org;
	TStringField *q_orgadress_org;
	TIntegerField *q_orgnom;
	TIntegerField *q_prodvidkod_prod_vid;
	TStringField *q_prodvidname_prod_vid;
	TIntegerField *q_prodvidnom;
	TADOQuery *ADOQ_en;
	TADOQuery *ADOQ_inf;
	TADOQuery *ADOQ_sea;
	TIntegerField *IntegerField1;
	TStringField *StringField1;
	TStringField *StringField2;
	TStringField *StringField3;
	TStringField *StringField4;
	TDateTimeField *DateTimeField1;
	TStringField *StringField5;
	TADOQuery *q_prihvid;
	TIntegerField *ADOQ_seecena_tr;
	TIntegerField *ADOQ_seacena_tr;
	TIntegerField *q_prodkod_prod_vid;
	TADOQuery *q_visa;
	TDataSource *s_visa;
	void __fastcall q_orgCalcFields(TDataSet *DataSet);
	void __fastcall q_prodvidCalcFields(TDataSet *DataSet);
	void __fastcall q_prodCalcFields(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall Tdmod1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tdmod1 *dmod1;
//---------------------------------------------------------------------------
#endif
