//---------------------------------------------------------------------------

#ifndef f_visaH
#define f_visaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class Tfr_visa : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label5;
	TEdit *visa_n;
	TEdit *visa_nom;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *visa_s;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall visa_nChange(TObject *Sender);
	void __fastcall visa_nKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
private:	// User declarations
public:		// User declarations

	inline void Edit_Clear();

	__fastcall Tfr_visa(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfr_visa *fr_visa;
//---------------------------------------------------------------------------
#endif
