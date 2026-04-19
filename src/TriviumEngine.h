#ifndef TriviumEngineH
#define TriviumEngineH

#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

class TriviumEngine
{
private:
    bool FState[288];
    bool FInitialized;

    System::Byte GenerateKeystreamByte();
    System::Byte Step();
    void ShiftRegisters(bool t1, bool t2, bool t3);
    void EnsureInitialized() const;
    static bool GetBitLittleEndian(const TBytes &bytes, int bitIndex);

public:
    static const int KeySizeBytes = 10;
    static const int IvSizeBytes = 10;
    static const int StateSizeBits = 288;
    static const int WarmupCycles = 4 * StateSizeBits;

    TriviumEngine();
    void InitCipher(const TBytes &key, const TBytes &iv);
    System::Byte Stream();
    void Next();
    TBytes EncryptData(const TBytes &plain);
    TBytes DecryptData(const TBytes &cipher);
    TBytes GenerateKeystream(int byteCount);
};

#endif
