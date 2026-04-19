#include <vcl.h>
#pragma hdrstop

#include <memory>
#include <System.IOUtils.hpp>
#include <System.SysUtils.hpp>
#include <windows.h>
#include <wincrypt.h>

#include "KeyFileService.h"
#include "HexCodec.h"
#include "TriviumEngine.h"

#pragma package(smart_init)
void KeyFileService::FillRandom(TBytes &buffer)
{
    if (buffer.Length == 0)
    {
        return;
    }

    HCRYPTPROV hProvider = 0;

    BOOL acquired = CryptAcquireContext(
        &hProvider,
        NULL,
        NULL,
        PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT
    );

    if (!acquired)
    {
        throw Exception(L"Unable to acquire Windows cryptographic provider.");
    }

    try
    {
        BOOL generated = CryptGenRandom(
            hProvider,
            static_cast<DWORD>(buffer.Length),
            reinterpret_cast<BYTE*>(&buffer[0])
        );

        if (!generated)
        {
            throw Exception(L"Unable to generate cryptographically secure random bytes.");
        }
    }
    __finally
    {
        CryptReleaseContext(hProvider, 0);
    }
}

KeyMaterial KeyFileService::Load(const UnicodeString &path)
{
    if (path.Trim().IsEmpty())
    {
        throw Exception(L"Key file path cannot be empty.");
    }

    if (!TFile::Exists(path))
    {
        throw Exception(L"Key file was not found: " + path);
    }

    std::unique_ptr<TStringList> lines(new TStringList());
    lines->LoadFromFile(path, TEncoding::UTF8);

    UnicodeString keyHex;
    UnicodeString ivHex;

    for (int i = 0; i < lines->Count; ++i)
    {
        UnicodeString line = lines->Strings[i].Trim();

        if (line.IsEmpty() || line[1] == L'#')
        {
            continue;
        }

        if (line.Length() >= 4 && CompareText(line.SubString(1, 4), L"KEY=") == 0)
        {
            keyHex = line.SubString(5, line.Length()).Trim();
            continue;
        }

        if (line.Length() >= 3 && CompareText(line.SubString(1, 3), L"IV=") == 0)
        {
            ivHex = line.SubString(4, line.Length()).Trim();
        }
    }

    if (keyHex.IsEmpty())
    {
        throw Exception(L"Key file must contain line KEY=<20 hex chars>.");
    }

    KeyMaterial material;
    material.Key = HexCodec::ParseDisplayHex(keyHex, TriviumEngine::KeySizeBytes);
    material.HasIV = !ivHex.IsEmpty();

    if (material.HasIV)
    {
        material.IV = HexCodec::ParseDisplayHex(ivHex, TriviumEngine::IvSizeBytes);
    }
    else
    {
		material.IV.Length = 0;
    }

    return material;
}

void KeyFileService::Save(const UnicodeString &path, const TBytes &key)
{
    if (key.Length != TriviumEngine::KeySizeBytes)
    {
        throw Exception(L"Key must be exactly 10 bytes.");
    }

    std::unique_ptr<TStringList> lines(new TStringList());
    lines->Add(L"# Trivium key file");
    lines->Add(L"KEY=" + HexCodec::ToDisplayHex(key));
    lines->SaveToFile(path, TEncoding::UTF8);
}

void KeyFileService::Save(const UnicodeString &path, const TBytes &key, const TBytes &iv)
{
    if (key.Length != TriviumEngine::KeySizeBytes)
    {
        throw Exception(L"Key must be exactly 10 bytes.");
    }

    if (iv.Length != TriviumEngine::IvSizeBytes)
    {
        throw Exception(L"IV must be exactly 10 bytes.");
    }

    std::unique_ptr<TStringList> lines(new TStringList());
    lines->Add(L"# Trivium key file");
    lines->Add(L"KEY=" + HexCodec::ToDisplayHex(key));
    lines->Add(L"IV=" + HexCodec::ToDisplayHex(iv));
    lines->SaveToFile(path, TEncoding::UTF8);
}

TBytes KeyFileService::GenerateRandomKey()
{
	TBytes key;
    key.Length = TriviumEngine::KeySizeBytes;
    FillRandom(key);
	return key;
}

TBytes KeyFileService::GenerateRandomIv()
{
	TBytes iv;
    iv.Length = TriviumEngine::IvSizeBytes;
    FillRandom(iv);
    return iv;
}
