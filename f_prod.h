//---------------------------------------------------------------------------

#ifndef f_prodH
#define f_prodH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <vector>
#include <algorithm>
//---------------------------------------------------------------------------
class TForm_prod : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *Edit_name;
	TLabel *Label2;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TComboBox *n_prodvid;
	TBitBtn *BitBtn1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall n_prodvidChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations

	std::vector<int> id_prodvid;
	inline void Edit_Clear();
	inline void pv_add();

	__fastcall TForm_prod(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_prod *Form_prod;
//---------------------------------------------------------------------------
#endif
