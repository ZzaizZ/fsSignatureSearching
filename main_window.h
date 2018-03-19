//---------------------------------------------------------------------------

#ifndef main_windowH
#define main_windowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include "NTFSFileSystem.h"
//---------------------------------------------------------------------------
class TMainWindow : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *vstFindingSectors;
	TEdit *tedName;
	TButton *btnSearch;
	TLabel *lblPath;
	TCheckBox *checkSqlite;
	TLabel *lblStatusBar;
	void __fastcall btnSearchClick(TObject *Sender);
private:	// User declarations
    WCHAR sqlite_signature;
public:		// User declarations
	__fastcall TMainWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWindow *MainWindow;
//---------------------------------------------------------------------------
#endif
