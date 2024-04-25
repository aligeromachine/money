//---------------------------------------------------------------------------

#ifndef f_itH
#define f_itH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ComCtrls.hpp>
#include <ComObj.hpp>
#include <vector>
#include <list>
#include <algorithm>
//#include <utilcls.h>
//---------------------------------------------------------------------------
class TForm_it : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TGroupBox *GroupBox4;
	TLabel *Label2;
	TLabel *sum_tr;
	TLabel *Label4;
	TLabel *sum_day;
	TMainMenu *MainMenu1;
	TMenuItem *C1;
	TMenuItem *EXCEL1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *EXCEL2;
	TProgressBar *ProgressBar1;
	TMenuItem *EXCEL3;
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
    void __fastcall N7Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	void __fastcall EXCEL1Click(TObject *Sender);
	void __fastcall EXCEL2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations

	void __fastcall start();

	void __fastcall graf_org();
	void __fastcall graf_prodvid();
	void __fastcall graf_prod();
	void __fastcall graf_dt();

	inline void qwery_org();
	inline void qwery_prodvid();
	inline void qwery_prod();
	inline void qwery_dt();

	void __fastcall excel_exp();
	void __fastcall graf_en();
	void __fastcall graf_inf(const AnsiString&);

	void __fastcall pr_tr0(const int&);
	void __fastcall pr_tr1();
	void __fastcall pr_tr2();
	void __fastcall pr_tr3();

	Variant vVarApp,vVarSheets,vVarSheet,vVarCells,vVarCell;
	int i_inf,list;
	AnsiString s;

	__fastcall TForm_it(TComponent* Owner);
};

class stat
{
	private:
		int god;
		int mes;
		int zp;
		int tr;
	public:
	//конструктор
	stat(): god(0),mes(0),zp(0),tr(0) {};
	stat(const int&,const int&,const int&,const int&);
	//члены модификаторы
	void set_god(const int&);
	void set_mes(const int&);
	void set_zp(const int&);
	void set_tr(const int&);
	//члены доступа
	int get_god() const {return god;};
	int get_mes() const {return mes;};
	int get_zp() const {return zp;};
	int get_tr() const {return tr;};
};
stat::stat(const int& g,const int& m,const int& z,const int& t)
{
	god=g;
	mes=m;
	zp=z;
	tr=t;
}
void stat::set_god(const int& g)
{
	god=g;
}
void stat::set_mes(const int& m)
{
	mes=m;
}
void stat::set_zp(const int& z)
{
	zp=z;
}
void stat::set_tr(const int& t)
{
	tr=t;
}

std::vector<stat*> vstat;
std::vector<stat*>::iterator pstat;
//---------------------------------------------------------------------------
extern PACKAGE TForm_it *Form_it;
//---------------------------------------------------------------------------
#endif
