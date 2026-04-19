#ifndef MainFormH
#define MainFormH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "TriviumFileCipher.h"

class TMainForm : public TForm
{
__published:
    TGroupBox *GroupBoxFiles;
    TLabel *LabelInput;
    TEdit *EditInputFile;
    TButton *ButtonBrowseInput;
    TLabel *LabelOutput;
    TEdit *EditOutputFile;
    TButton *ButtonBrowseOutput;
    TLabel *LabelKey;
    TEdit *EditKeyFile;
    TButton *ButtonBrowseKey;
    TGroupBox *GroupBoxParams;
    TLabel *LabelIV;
    TEdit *EditIV;
    TButton *ButtonGenerateIV;
    TCheckBox *CheckBoxAutoFillOutput;
    TGroupBox *GroupBoxOps;
    TButton *ButtonEncrypt;
    TButton *ButtonDecrypt;
    TButton *ButtonGenerateKey;
    TButton *ButtonClearLog;
    TMemo *MemoLog;
    TLabel *LabelLog;
    TPanel *PanelHeader;
    TLabel *LabelTitle;
    TLabel *LabelSubtitle;
    TPanel *PanelNote;
    TLabel *LabelNote;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;

    void __fastcall ButtonBrowseInputClick(TObject *Sender);
    void __fastcall ButtonBrowseOutputClick(TObject *Sender);
    void __fastcall ButtonBrowseKeyClick(TObject *Sender);
    void __fastcall ButtonGenerateIVClick(TObject *Sender);
    void __fastcall ButtonGenerateKeyClick(TObject *Sender);
    void __fastcall ButtonEncryptClick(TObject *Sender);
    void __fastcall ButtonDecryptClick(TObject *Sender);
    void __fastcall ButtonClearLogClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);

private:
    TriviumFileCipher FFileCipher;

    void AppendLog(const UnicodeString &message);
    UnicodeString EnsureIvHexForEncryption();
    void EnsureRequiredFieldsForEncryption();
    void EnsureRequiredFieldsForDecryption();
    void ShowError(const Exception &ex);

public:
    __fastcall TMainForm(TComponent* Owner);
};

extern PACKAGE TMainForm *MainForm;

#endif
