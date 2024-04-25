//---------------------------------------------------------------------------

#ifndef f_dateH
#define f_dateH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_date : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup *RadioGroup1;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton4;
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
private:	// User declarations
public:		// User declarations

	__fastcall TForm_date(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_date *Form_date;
//---------------------------------------------------------------------------
#endif
