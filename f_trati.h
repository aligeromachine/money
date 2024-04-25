//---------------------------------------------------------------------------

#ifndef f_tratiH
#define f_tratiH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Buttons.hpp>
#include <Data.FMTBcd.hpp>
#include <DateUtils.hpp>
#include <vector>
#include <algorithm>
//---------------------------------------------------------------------------
class TForm_trati : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit_prim;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TComboBox *n_prod_vid;
	TEdit *Edit_cena;
	TLabel *Label4;
	TComboBox *n_prod;
	TLabel *Label5;
	TComboBox *n_org;
	TLabel *Label6;
	TDateTimePicker *DateTimePicker_trati;
	TLabel *Label7;
	TEdit *Edit_kol_ed;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall n_prod_vidChange(TObject *Sender);
	void __fastcall n_orgChange(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Edit_cenaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall n_prodChange(TObject *Sender);
	void __fastcall Edit_cenaChange(TObject *Sender);

private:	// User declarations
public:		// User declarations

	int sum;
	DATE a;
	std::vector<int> id_org,id_prod,id_prodvid;

	inline void sum_add1(const int&,const int&);
	inline void sum_add2(const int&);
	inline void sum_ins1(const int&);
	inline void sum_ins2(const int&,const int&);
	inline void sum_ins3(const int&);
	inline void sum_ins4();
	inline void Edit_Clear();
	inline void org_add();
	inline void pv_add();
	inline void pr_add();

	__fastcall TForm_trati(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_trati *Form_trati;
//---------------------------------------------------------------------------
#endif
