//---------------------------------------------------------------------------

#ifndef f_prodvidH
#define f_prodvidH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <vector>
#include <algorithm>
//---------------------------------------------------------------------------
class TForm_prodvid : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *Edit_name;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Edit_nameChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	inline void Edit_Clear();
	__fastcall TForm_prodvid(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_prodvid *Form_prodvid;
//---------------------------------------------------------------------------
#endif
