#include <memory>
#include <System.SysUtils.hpp>
#include <Vcl.Dialogs.hpp>
#include <Winapi.Messages.hpp>
#include "MainForm.h"
#include "HexCodec.h"
#include "KeyFileService.h"
#include "TriviumEngine.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

TMainForm *MainForm;

__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
}

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    AppendLog(L"Застосунок запущено.");
}

void TMainForm::AppendLog(const UnicodeString &message)
{
    UnicodeString line = L"[" + FormatDateTime(L"hh:nn:ss", Now()) + L"] " + message;
    MemoLog->Lines->Add(line);
    MemoLog->SelStart = MemoLog->Text.Length();
    MemoLog->Perform(EM_SCROLLCARET, 0, 0);
}

void TMainForm::EnsureRequiredFieldsForEncryption()
{
    if (EditInputFile->Text.Trim().IsEmpty())
    {
        throw Exception(L"Не вказано вхідний файл.");
    }

    if (EditOutputFile->Text.Trim().IsEmpty())
    {
        throw Exception(L"Не вказано вихідний файл.");
    }

    if (EditKeyFile->Text.Trim().IsEmpty())
    {
        throw Exception(L"Не вказано key-файл.");
    }
}

void TMainForm::EnsureRequiredFieldsForDecryption()
{
    if (EditInputFile->Text.Trim().IsEmpty())
    {
        throw Exception(L"Не вказано шифрований файл.");
    }

    if (EditOutputFile->Text.Trim().IsEmpty())
    {
        throw Exception(L"Не вказано вихідний файл.");
    }

    if (EditKeyFile->Text.Trim().IsEmpty())
    {
        throw Exception(L"Не вказано key-файл.");
    }
}

UnicodeString TMainForm::EnsureIvHexForEncryption()
{
    UnicodeString ivHex = EditIV->Text.Trim();

    if (!ivHex.IsEmpty())
    {
        HexCodec::ParseDisplayHex(ivHex, TriviumEngine::IvSizeBytes);
        return ivHex;
    }

    TBytes iv = KeyFileService::GenerateRandomIv();
    ivHex = HexCodec::ToDisplayHex(iv);
    EditIV->Text = ivHex;
    AppendLog(L"IV не був заданий, згенеровано випадковий IV: " + ivHex);
    return ivHex;
}

void TMainForm::ShowError(const Exception &ex)
{
    AppendLog(L"ПОМИЛКА: " + ex.Message);
    MessageDlg(ex.Message, mtError, TMsgDlgButtons() << mbOK, 0);
}

void __fastcall TMainForm::ButtonBrowseInputClick(TObject *Sender)
{
    OpenDialog1->Filter = L"All files (*.*)|*.*";
    if (OpenDialog1->Execute())
    {
        EditInputFile->Text = OpenDialog1->FileName;

        if (CheckBoxAutoFillOutput->Checked && EditOutputFile->Text.Trim().IsEmpty())
        {
            EditOutputFile->Text = OpenDialog1->FileName + L".tvm";
        }

        AppendLog(L"Обрано вхідний файл: " + OpenDialog1->FileName);
    }
}

void __fastcall TMainForm::ButtonBrowseOutputClick(TObject *Sender)
{
    SaveDialog1->Filter = L"All files (*.*)|*.*";
    if (SaveDialog1->Execute())
    {
        EditOutputFile->Text = SaveDialog1->FileName;
        AppendLog(L"Обрано вихідний файл: " + SaveDialog1->FileName);
    }
}

void __fastcall TMainForm::ButtonBrowseKeyClick(TObject *Sender)
{
    OpenDialog1->Filter = L"Key files (*.key;*.txt)|*.key;*.txt|All files (*.*)|*.*";
    if (OpenDialog1->Execute())
    {
        EditKeyFile->Text = OpenDialog1->FileName;
        AppendLog(L"Обрано key-файл: " + OpenDialog1->FileName);
    }
}

void __fastcall TMainForm::ButtonGenerateIVClick(TObject *Sender)
{
    TBytes iv = KeyFileService::GenerateRandomIv();
    UnicodeString ivHex = HexCodec::ToDisplayHex(iv);
    EditIV->Text = ivHex;
    AppendLog(L"Згенеровано IV: " + ivHex);
}

void __fastcall TMainForm::ButtonGenerateKeyClick(TObject *Sender)
{
    SaveDialog1->Filter = L"Key files (*.key)|*.key|Text files (*.txt)|*.txt|All files (*.*)|*.*";
    SaveDialog1->FileName = L"trivium.key";

    if (!SaveDialog1->Execute())
    {
        return;
    }

    TBytes key = KeyFileService::GenerateRandomKey();
    KeyFileService::Save(SaveDialog1->FileName, key);

    EditKeyFile->Text = SaveDialog1->FileName;
    AppendLog(L"Створено key-файл: " + SaveDialog1->FileName);
    AppendLog(L"KEY=" + HexCodec::ToDisplayHex(key));
}

void __fastcall TMainForm::ButtonEncryptClick(TObject *Sender)
{
    try
    {
        EnsureRequiredFieldsForEncryption();
        UnicodeString ivHex = EnsureIvHexForEncryption();

        EncryptionResult result = FFileCipher.EncryptFile(
            EditInputFile->Text.Trim(),
            EditOutputFile->Text.Trim(),
            EditKeyFile->Text.Trim(),
            ivHex);

        AppendLog(L"Операція: шифрування");
        AppendLog(L"Вхідний файл: " + EditInputFile->Text.Trim());
        AppendLog(L"Вихідний файл: " + EditOutputFile->Text.Trim());
        AppendLog(L"Використаний IV: " + result.UsedIvHex);
        AppendLog(L"Розмір відкритого тексту: " + IntToStr(result.InputLength) + L" байт");
        AppendLog(L"Розмір шифрованого файлу: " + IntToStr(result.OutputLength) + L" байт");
        AppendLog(L"Шифрування завершено успішно.");
    }
    catch (const Exception &ex)
    {
        ShowError(ex);
    }
}

void __fastcall TMainForm::ButtonDecryptClick(TObject *Sender)
{
    try
    {
        EnsureRequiredFieldsForDecryption();

        DecryptionResult result = FFileCipher.DecryptFile(
            EditInputFile->Text.Trim(),
            EditOutputFile->Text.Trim(),
            EditKeyFile->Text.Trim());

        AppendLog(L"Операція: розшифрування");
        AppendLog(L"Вхідний файл: " + EditInputFile->Text.Trim());
        AppendLog(L"Вихідний файл: " + EditOutputFile->Text.Trim());
        AppendLog(L"IV із заголовка TVM1: " + result.UsedIvHex);
        AppendLog(L"Розмір шифрованого файлу: " + IntToStr(result.InputLength) + L" байт");
        AppendLog(L"Розмір відкритого тексту: " + IntToStr(result.OutputLength) + L" байт");
        AppendLog(L"Розшифрування завершено успішно.");
    }
    catch (const Exception &ex)
    {
        ShowError(ex);
    }
}

void __fastcall TMainForm::ButtonClearLogClick(TObject *Sender)
{
    MemoLog->Clear();
    AppendLog(L"Журнал очищено.");
}
