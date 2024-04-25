//---------------------------------------------------------------------------

#ifndef f_trativH
#define f_trativH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.XPMan.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.SysUtils.hpp>
#include <DateUtils.hpp>
#include <time.h>

//---------------------------------------------------------------------------
class TForm_trativ : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TToolButton *ToolButton1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit1;
	TDBGrid *DBGrid1;
	TGroupBox *GroupBox4;
	TMainMenu *MainMenu1;
	TMenuItem *N9;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N11;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *N10;
	TImageList *ImageList1;
	TXPManifest *XPManifest1;
	TMenuItem *N1;
	TLabel *sum_pr;
	TMenuItem *N6;
	TMenuItem *ASC1;
	TMenuItem *DESC1;
	TMenuItem *ASC2;
	TMenuItem *DESC2;
	TMenuItem *ASC3;
	TMenuItem *DESC3;
	TMenuItem *N14;
	TMenuItem *N17;
	TMenuItem *ASC4;
	TMenuItem *DESC4;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TToolButton *ToolButton10;
	TToolButton *ToolButton11;
	TGroupBox *GroupBox1;
	TLabel *sum_tr;
	TGroupBox *GroupBox2;
	TLabel *sum_trm;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox5;
	TLabel *sum_kr;
	TGroupBox *GroupBox6;
	TLabel *sum_kh;
	TLabel *sum_trn;
	TGroupBox *GroupBox7;
	TLabel *sum_prm;
	TGroupBox *GroupBox8;
	TLabel *sum_trd;
	TToolButton *ToolButton15;
	TMenuItem *N18;
	TToolButton *ToolButton16;
	TToolButton *ToolButton18;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TTimer *Timer1;
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton4Click(TObject *Sender);
	void __fastcall ToolButton5Click(TObject *Sender);
	void __fastcall ToolButton7Click(TObject *Sender);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N15Click(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall ASC1Click(TObject *Sender);
	void __fastcall DESC1Click(TObject *Sender);
	void __fastcall ASC2Click(TObject *Sender);
	void __fastcall DESC2Click(TObject *Sender);
	void __fastcall ASC3Click(TObject *Sender);
	void __fastcall DESC3Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall N17Click(TObject *Sender);
	void __fastcall ASC4Click(TObject *Sender);
	void __fastcall DESC4Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall ToolButton8Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ToolButton11Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall N18Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
private:	// User declarations
public:		// User declarations

	bool f_trati;
	bool f_trati_cl1;
	bool f_trati_cl2;
	bool f_trati_cl3;
	bool f_prod_cl4;
	bool f_prih_cl5;

	bool f_org;
	bool f_prod;
	bool f_prodvid;
	bool f_prih;
	bool f_prihvid;
	bool f_visa;

	int s_prih;
	int s_trati;

	DATE dn;

	__fastcall TForm_trativ(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_trativ *Form_trativ;
//---------------------------------------------------------------------------
#endif
