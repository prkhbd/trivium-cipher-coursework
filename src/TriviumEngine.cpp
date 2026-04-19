#include <System.IOUtils.hpp>
#include "TriviumFileCipher.h"
#include "KeyFileService.h"
#include "HexCodec.h"
#include "EncryptedFileFormat.h"
#include "TriviumEngine.h"

void TriviumFileCipher::ValidatePaths(const UnicodeString &inputPath,
                                      const UnicodeString &outputPath,
                                      const UnicodeString &keyFilePath)
{
    if (inputPath.Trim().IsEmpty())
    {
        throw Exception(L"Input file path is empty.");
    }

    if (outputPath.Trim().IsEmpty())
    {
        throw Exception(L"Output file path is empty.");
    }

    if (keyFilePath.Trim().IsEmpty())
    {
        throw Exception(L"Key file path is empty.");
    }

    if (!TFile::Exists(inputPath))
    {
        throw Exception(L"Input file not found: " + inputPath);
    }

    if (!TFile::Exists(keyFilePath))
    {
        throw Exception(L"Key file not found: " + keyFilePath);
    }
}

EncryptionResult TriviumFileCipher::EncryptFile(const UnicodeString &inputPath,
                                                const UnicodeString &outputPath,
                                                const UnicodeString &keyFilePath,
                                                const UnicodeString &manualIvHex)
{
    ValidatePaths(inputPath, outputPath, keyFilePath);

    TBytes plain = TFile::ReadAllBytes(inputPath);
    KeyMaterial keyMaterial = KeyFileService::Load(keyFilePath);

    TBytes iv;
    if (!manualIvHex.Trim().IsEmpty())
    {
        iv = HexCodec::ParseDisplayHex(manualIvHex, TriviumEngine::IvSizeBytes);
    }
    else if (keyMaterial.HasIV)
    {
        iv = keyMaterial.IV;
    }
    else
    {
        iv = KeyFileService::GenerateRandomIv();
    }

    TriviumEngine engine;
    engine.InitCipher(keyMaterial.Key, iv);

    TBytes ciphertext = engine.EncryptData(plain);
    TBytes fileBytes = EncryptedFileFormat::Build(iv, ciphertext);
    TFile::WriteAllBytes(outputPath, fileBytes);

    EncryptionResult result;
    result.InputLength = plain.Length;
    result.OutputLength = fileBytes.Length;
    result.UsedIvHex = HexCodec::ToDisplayHex(iv);
    return result;
}

DecryptionResult TriviumFileCipher::DecryptFile(const UnicodeString &inputPath,
                                                const UnicodeString &outputPath,
                                                const UnicodeString &keyFilePath)
{
    ValidatePaths(inputPath, outputPath, keyFilePath);

    TBytes fileBytes = TFile::ReadAllBytes(inputPath);
    KeyMaterial keyMaterial = KeyFileService::Load(keyFilePath);
    EncryptedPayload payload = EncryptedFileFormat::Parse(fileBytes);

    TriviumEngine engine;
    engine.InitCipher(keyMaterial.Key, payload.IV);

    TBytes plain = engine.DecryptData(payload.Ciphertext);
    TFile::WriteAllBytes(outputPath, plain);

    DecryptionResult result;
    result.InputLength = fileBytes.Length;
    result.OutputLength = plain.Length;
    result.UsedIvHex = HexCodec::ToDisplayHex(payload.IV);
    return result;
}
