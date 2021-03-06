//---------------------------------------------------------------------------

#ifndef main_windowH
#define main_windowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include "ReadingThread.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainWindow : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *vstFindingSectors;
	TEdit *tedName;
	TButton *btnSearch;
	TLabel *lblPath;
	TLabel *lblStatusBar;
	TLabel *lblCurrentClusterNumber;
	TButton *btnStop;
	TLabel *lblTotalClustersCount;
	TProgressBar *pbSearchingStatus;
	TLabel *lblSlash;
	TLabel *lblClusterInfo;
	TRadioGroup *RadioGroup1;
	TRadioButton *radAll;
	TRadioButton *radRange;
	TEdit *tedStartCluster;
	TEdit *tedStopCluster;
	TComboBox *cbFsType;
	TLabel *lblFsType;
	void __fastcall btnSearchClick(TObject *Sender);
	void __fastcall vstFindingSectorsGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall btnStopClick(TObject *Sender);

private:	// User declarations
	ReadingThread *reading_thread;
public:		// User declarations
	__fastcall TMainWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWindow *MainWindow;
//---------------------------------------------------------------------------
#endif
