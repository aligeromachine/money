//---------------------------------------------------------------------------

#ifndef f_orgH
#define f_orgH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.CheckLst.hpp>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
typedef boost::array<int, 2> array_boost;
class TForm_org : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit_name;
	TEdit *Edit_adress;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TLabel *Label3;
	TCheckListBox *sv;
	TLabel *Label4;
	TButton *Button4;
	TLabel *Label5;
	TButton *Button5;
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Edit_nameChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall svClick(TObject *Sender);
	void __fastcall svClickCheck(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	inline void Edit_Clear();
	std::vector<int> vect_sv;
	__fastcall TForm_org(TComponent* Owner);
};
class org_sv
{
	private:
	int id_org;
	AnsiString name;
	AnsiString adress;
	std::vector<array_boost> sv_pv;
	public:
	explicit org_sv(): id_org(0), name(""),adress(""), sv_pv(std::vector<array_boost>()) {};
	org_sv(const int& i, const AnsiString& a,const AnsiString& b,const std::vector<array_boost>& c)
	{
		this->id_org = i;
		this->name = a;
		this->adress = b;
		this->sv_pv = c;
	};
	//члены модификаторы
	void set_id(const int& i)
	{
		this->id_org = i;
	};
	void set_name(const AnsiString& a)
	{
		this->name = a;
	};
	void set_adress(const AnsiString& b)
	{
		this->adress = b;
	};
	void set_sv(const std::vector<array_boost>& c)
	{
		this->sv_pv = c;
	};
	void set_org_sv(const int& i, const AnsiString& a,const AnsiString& b,const std::vector<array_boost>& c)
	{
		this->id_org = i;
		this->name = a;
		this->adress = b;
		this->sv_pv = c;
	};
	//члены доступа
	AnsiString get_id() const {return this->id_org;};
	AnsiString get_name() const {return this->name;};
	AnsiString get_adress() const {return this->adress;};
	std::vector<array_boost> get_sv() const {return this->sv_pv;};
	void dobavlenie();
	void obnovlenie();
	void compera(const org_sv*);
};
class MyClassComp
{
private:
  int n;
public:
  explicit MyClassComp(int i): n(i) {};
  inline bool operator()(const int& m) const { return m == n; }
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_org *Form_org;
//---------------------------------------------------------------------------
#endif
