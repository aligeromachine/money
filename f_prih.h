//---------------------------------------------------------------------------

#ifndef f_prihH
#define f_prihH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <DateUtils.hpp>
#include <vector>
#include <algorithm>
//---------------------------------------------------------------------------
class TForm_prih : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *Edit_sum;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TComboBox *n_prihvid;
	TLabel *Label4;
	TEdit *Edit_prim;
	TDateTimePicker *DateTimePicker_prih;
	TLabel *Label3;
	TBitBtn *BitBtn1;
	TLabel *Label6;
	TComboBox *visa;
	TLabel *Label2;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall n_prihvidChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Edit_sumKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations

	DATE a;
	int sum;

	inline void sum_add1(const int&,const int&);
	inline void sum_add2(const int&);
	inline void sum_ins1(const int&);
	inline void sum_ins2(const int&,const int&);
	inline void sum_ins3(const int&);
	inline void sum_ins4();
	inline void Edit_Clear();
	inline void prih_add();
	inline void visa_add();

	std::vector<int> id_prihvid,v_visa;

	__fastcall TForm_prih(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_prih *Form_prih;
//---------------------------------------------------------------------------
#endif
