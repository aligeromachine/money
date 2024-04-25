//---------------------------------------------------------------------------

#ifndef f_prihvH
#define f_prihvH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ToolWin.hpp>
#include <vector>
#include <algorithm>
//---------------------------------------------------------------------------
class TForm_prihv : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TDBGrid *DBGrid1;
	TGroupBox *GroupBox1;
	TLabel *sum_p1;
	TGroupBox *GroupBox2;
	TLabel *sum_p2;
	TGroupBox *GroupBox3;
	TLabel *sum_p3;
	TToolButton *ToolButton1;
	TToolButton *ToolButton8;
	TEdit *Edit1;
	TToolButton *ToolButton9;
	TToolButton *ToolButton10;
	TToolButton *ToolButton11;
	TToolButton *ToolButton12;
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton4Click(TObject *Sender);
	void __fastcall ToolButton5Click(TObject *Sender);
	void __fastcall ToolButton7Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
	void __fastcall ToolButton8Click(TObject *Sender);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall ToolButton11Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_prihv(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_prihv *Form_prihv;
//---------------------------------------------------------------------------
#endif
