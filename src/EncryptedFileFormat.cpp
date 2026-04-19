#include <vcl.h>
#pragma hdrstop

#include "EncryptedFileFormat.h"
#include <System.SysUtils.hpp>

const int HeaderLength = 15;
const int IvLength = 10;
const System::Byte Version = 1;

TBytes EncryptedFileFormat::Build(const TBytes& iv, const TBytes& ciphertext)
{
    if (iv.Length != IvLength)
        throw Exception(L"IV ïîâèíåí ìàòè äîâæèíó 10 áàéò.");

    TBytes result;
    result.Length = HeaderLength + ciphertext.Length;

    result[0] = static_cast<System::Byte>('T');
    result[1] = static_cast<System::Byte>('V');
    result[2] = static_cast<System::Byte>('M');
    result[3] = static_cast<System::Byte>('1');
    result[4] = Version;

    for (int i = 0; i < iv.Length; ++i)
    {
        result[5 + i] = iv[i];
    }

    for (int i = 0; i < ciphertext.Length; ++i)
    {
        result[HeaderLength + i] = ciphertext[i];
    }

    return result;
}

EncryptedPayload EncryptedFileFormat::Parse(const TBytes& data)
{
    if (data.Length < HeaderLength)
        throw Exception(L"Ôàéë çàíàäòî êîðîòêèé ³ íå ì³ñòèòü êîðåêòíîãî çàãîëîâêà.");

    if (data[0] != static_cast<System::Byte>('T') ||
        data[1] != static_cast<System::Byte>('V') ||
        data[2] != static_cast<System::Byte>('M') ||
        data[3] != static_cast<System::Byte>('1'))
    {
        throw Exception(L"Íåâ³ðíà ñèãíàòóðà øèôðîâàíîãî ôàéëó.");
    }

    if (data[4] != Version)
        throw Exception(L"Íåï³äòðèìóâàíà âåðñ³ÿ ôîðìàòó øèôðîâàíîãî ôàéëó.");

    TBytes iv;
    iv.Length = IvLength;

    for (int i = 0; i < IvLength; ++i)
    {
        iv[i] = data[5 + i];
    }

    TBytes ciphertext;
    ciphertext.Length = data.Length - HeaderLength;

    for (int i = 0; i < ciphertext.Length; ++i)
    {
        ciphertext[i] = data[HeaderLength + i];
    }

    EncryptedPayload payload;
    payload.IV = iv;
    payload.Ciphertext = ciphertext;

    return payload;
}
