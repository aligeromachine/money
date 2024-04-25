//---------------------------------------------------------------------------

#ifndef f_visavH
#define f_visavH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ToolWin.hpp>
//---------------------------------------------------------------------------
class Tfr_visav : public TForm
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
	TGroupBox *GroupBox1;
	TLabel *p1;
	TGroupBox *GroupBox2;
	TLabel *p2;
	TDBGrid *DBGrid1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ToolButton7Click(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton4Click(TObject *Sender);
	void __fastcall ToolButton5Click(TObject *Sender);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
private:	// User declarations
public:		// User declarations
	__fastcall Tfr_visav(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfr_visav *fr_visav;
//---------------------------------------------------------------------------
#endif
