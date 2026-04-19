#include <algorithm>
#include "TriviumEngine.h"

TriviumEngine::TriviumEngine()
    : FInitialized(false)
{
    std::fill(FState, FState + StateSizeBits, false);
}

void TriviumEngine::InitCipher(const TBytes &key, const TBytes &iv)
{
    if (key.Length != KeySizeBytes)
    {
        throw Exception(L"Trivium key must be exactly 10 bytes.");
    }

    if (iv.Length != IvSizeBytes)
    {
        throw Exception(L"Trivium IV must be exactly 10 bytes.");
    }

    std::fill(FState, FState + StateSizeBits, false);

    for (int i = 0; i < 80; ++i)
    {
        FState[i] = GetBitLittleEndian(key, i);
    }

    for (int i = 0; i < 80; ++i)
    {
        FState[93 + i] = GetBitLittleEndian(iv, i);
    }

    FState[285] = true;
    FState[286] = true;
    FState[287] = true;

    FInitialized = true;

    for (int i = 0; i < WarmupCycles; ++i)
    {
        Next();
    }
}

System::Byte TriviumEngine::Stream()
{
    EnsureInitialized();
    return Step();
}

void TriviumEngine::Next()
{
    EnsureInitialized();
    Step();
}

TBytes TriviumEngine::EncryptData(const TBytes &plain)
{
    EnsureInitialized();

    TBytes result;
	result.Length = plain.Length;

    for (int i = 0; i < plain.Length; ++i)
    {
        result[i] = static_cast<System::Byte>(plain[i] ^ GenerateKeystreamByte());
    }

    return result;
}

TBytes TriviumEngine::DecryptData(const TBytes &cipher)
{
    EnsureInitialized();

    TBytes result;
	result.Length = cipher.Length;

    for (int i = 0; i < cipher.Length; ++i)
    {
        result[i] = static_cast<System::Byte>(cipher[i] ^ GenerateKeystreamByte());
    }

    return result;
}

TBytes TriviumEngine::GenerateKeystream(int byteCount)
{
    if (byteCount < 0)
    {
        throw Exception(L"Keystream length cannot be negative.");
    }

    EnsureInitialized();

    TBytes output;
	output.Length = byteCount;

    for (int i = 0; i < byteCount; ++i)
    {
        output[i] = GenerateKeystreamByte();
    }

    return output;
}

System::Byte TriviumEngine::GenerateKeystreamByte()
{
    System::Byte value = 0;

    for (int bit = 0; bit < 8; ++bit)
    {
        value |= static_cast<System::Byte>(Stream() << bit);
    }

    return value;
}

System::Byte TriviumEngine::Step()
{
    bool t1 = FState[65] ^ FState[92];
    bool t2 = FState[161] ^ FState[176];
    bool t3 = FState[242] ^ FState[287];

    bool z = t1 ^ t2 ^ t3;

    t1 = t1 ^ (FState[90] && FState[91]) ^ FState[170];
    t2 = t2 ^ (FState[174] && FState[175]) ^ FState[263];
    t3 = t3 ^ (FState[285] && FState[286]) ^ FState[68];

    ShiftRegisters(t1, t2, t3);

    return z ? 1 : 0;
}

void TriviumEngine::ShiftRegisters(bool t1, bool t2, bool t3)
{
    for (int i = 92; i >= 1; --i)
    {
        FState[i] = FState[i - 1];
    }
    FState[0] = t3;

    for (int i = 176; i >= 94; --i)
    {
        FState[i] = FState[i - 1];
    }
    FState[93] = t1;

    for (int i = 287; i >= 178; --i)
    {
        FState[i] = FState[i - 1];
    }
    FState[177] = t2;
}

void TriviumEngine::EnsureInitialized() const
{
    if (!FInitialized)
    {
        throw Exception(L"Cipher is not initialized. Call InitCipher first.");
    }
}

bool TriviumEngine::GetBitLittleEndian(const TBytes &bytes, int bitIndex)
{
    int byteIndex = bitIndex / 8;
    int bitInByte = bitIndex % 8;
    return ((bytes[byteIndex] >> bitInByte) & 1) == 1;
}
