#include <System.SysUtils.hpp>
#include "HexCodec.h"

UnicodeString HexCodec::Normalize(const UnicodeString &hex)
{
    UnicodeString result;

    for (int i = 1; i <= hex.Length(); ++i)
    {
        wchar_t c = hex[i];
        if (c == L' ' || c == L'\t' || c == L'\r' || c == L'\n' || c == L'-' || c == L':')
        {
            continue;
        }

        result += UpperCase(UnicodeString(c));
    }

    return result;
}

TBytes HexCodec::ParseDisplayHex(const UnicodeString &hex, int expectedBytes)
{
    UnicodeString normalized = Normalize(hex);

    if (normalized.IsEmpty())
    {
        throw Exception(L"Hex string cannot be empty.");
    }

    if (normalized.Length() != expectedBytes * 2)
    {
        throw Exception(L"Hex string must contain exactly " + IntToStr(expectedBytes * 2) + L" hexadecimal characters.");
    }

    TBytes displayBytes;
	displayBytes.Length = expectedBytes;

    for (int i = 0; i < expectedBytes; ++i)
    {
        UnicodeString pair = normalized.SubString(i * 2 + 1, 2);
        int value = StrToInt(L"$" + pair);
        displayBytes[i] = static_cast<System::Byte>(value);
    }

    TBytes internalBytes;
    internalBytes.Length = expectedBytes;

    for (int i = 0; i < expectedBytes; ++i)
    {
        internalBytes[i] = displayBytes[expectedBytes - 1 - i];
    }

    return internalBytes;
}

UnicodeString HexCodec::ToDisplayHex(const TBytes &internalBytes)
{
    UnicodeString result;

    for (int i = internalBytes.Length - 1; i >= 0; --i)
    {
        result += IntToHex(static_cast<int>(internalBytes[i]), 2);
    }

    return result;
}
