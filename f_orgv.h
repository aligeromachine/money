//---------------------------------------------------------------------------

#ifndef f_orgvH
#define f_orgvH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <vector>
#include <algorithm>
//---------------------------------------------------------------------------
class TForm_orgv : public TForm
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
	TToolButton *ToolButton1;
	TEdit *Edit1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ToolButton7Click(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton4Click(TObject *Sender);
	void __fastcall ToolButton5Click(TObject *Sender);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_orgv(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_orgv *Form_orgv;
//---------------------------------------------------------------------------
#endif
