#ifndef EncryptedFileFormatH
#define EncryptedFileFormatH

#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

struct EncryptedPayload
{
    TBytes IV;
    TBytes Ciphertext;
};

class EncryptedFileFormat
{
public:
    static const System::Byte Version = 1;
    static const int HeaderLength = 4 + 1 + 10;

    static TBytes Build(const TBytes &iv, const TBytes &ciphertext);
    static EncryptedPayload Parse(const TBytes &data);
};

#endif
