//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------


USEFORM("f_prod.cpp", Form_prod);
USEFORM("f_prodv.cpp", Form_prodv);
USEFORM("f_prihvid.cpp", Form_prihvid);
USEFORM("f_prihvidv.cpp", Form_prihvidv);
USEFORM("f_prodvid.cpp", Form_prodvid);
USEFORM("f_trativ.cpp", Form_trativ);
USEFORM("f_visa.cpp", fr_visa);
USEFORM("f_prodvidv.cpp", Form_prodvidv);
USEFORM("f_trati.cpp", Form_trati);
USEFORM("f_dmod.cpp", dmod1); /* TDataModule: File Type */
USEFORM("f_gl.cpp", Form_gl);
USEFORM("f_date.cpp", Form_date);
USEFORM("f_it.cpp", Form_it);
USEFORM("f_prih.cpp", Form_prih);
USEFORM("f_prihv.cpp", Form_prihv);
USEFORM("f_org.cpp", Form_org);
USEFORM("f_orgv.cpp", Form_orgv);
USEFORM("f_visav.cpp", fr_visav);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(Tdmod1), &dmod1);
		Application->CreateForm(__classid(TForm_trativ), &Form_trativ);
		Application->CreateForm(__classid(TForm_date), &Form_date);
		Application->CreateForm(__classid(TForm_gl), &Form_gl);
		Application->CreateForm(__classid(TForm_it), &Form_it);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
