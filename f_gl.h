//---------------------------------------------------------------------------

#ifndef f_glH
#define f_glH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.XPMan.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.AppEvnts.hpp>
#include <vector>
//---------------------------------------------------------------------------
class TForm_gl : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TDateTimePicker *DateTimePicker_n;
	TDateTimePicker *DateTimePicker_k;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label8;
	TComboBox *ComboBox_mon;
	TStatusBar *StatusBar1;
	TGroupBox *GroupBox5;
	TCheckListBox *CheckListBox_org;
	TGroupBox *GroupBox6;
	TCheckListBox *CheckListBox_prodvid;
	TGroupBox *GroupBox2;
	TCheckListBox *CheckListBox_prod;
	TApplicationEvents *ApplicationEvents1;
	TCheckBox *not_org;
	TCheckBox *not_prod_vid;
	TCheckBox *not_prod;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ApplicationEvents1Hint(TObject *Sender);
	void __fastcall CheckListBox_orgClick(TObject *Sender);
	void __fastcall CheckListBox_prodvidClick(TObject *Sender);
	void __fastcall CheckListBox_orgClickCheck(TObject *Sender);
	void __fastcall CheckListBox_prodvidClickCheck(TObject *Sender);
	void __fastcall CheckListBox_prodClick(TObject *Sender);
	void __fastcall CheckListBox_prodClickCheck(TObject *Sender);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CheckListBox_orgMouseLeave(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	void __fastcall Mes();
	void __fastcall itog();
	std::vector<int> myvector_o,myvector_p,myvector_v;

	void __fastcall CheckListBox_org_add();
	void __fastcall CheckListBox_prodvid_add();
	void __fastcall Clear();

	__fastcall TForm_gl(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_gl *Form_gl;
//---------------------------------------------------------------------------
#endif
