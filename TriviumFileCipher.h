#ifndef TriviumFileCipherH
#define TriviumFileCipherH

#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

struct EncryptionResult
{
    int InputLength;
    int OutputLength;
    UnicodeString UsedIvHex;
};

struct DecryptionResult
{
    int InputLength;
    int OutputLength;
    UnicodeString UsedIvHex;
};

class TriviumFileCipher
{
private:
    static void ValidatePaths(const UnicodeString &inputPath,
                              const UnicodeString &outputPath,
                              const UnicodeString &keyFilePath);

public:
    EncryptionResult EncryptFile(const UnicodeString &inputPath,
                                 const UnicodeString &outputPath,
                                 const UnicodeString &keyFilePath,
                                 const UnicodeString &manualIvHex = L"");

    DecryptionResult DecryptFile(const UnicodeString &inputPath,
                                 const UnicodeString &outputPath,
                                 const UnicodeString &keyFilePath);
};

#endif
