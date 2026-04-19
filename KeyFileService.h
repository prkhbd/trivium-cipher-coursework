#ifndef KeyFileServiceH
#define KeyFileServiceH

#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

struct KeyMaterial
{
    TBytes Key;
    TBytes IV;
    bool HasIV;
};

class KeyFileService
{
private:
    static void FillRandom(TBytes &buffer);

public:
    static KeyMaterial Load(const UnicodeString &path);
    static void Save(const UnicodeString &path, const TBytes &key);
    static void Save(const UnicodeString &path, const TBytes &key, const TBytes &iv);
    static TBytes GenerateRandomKey();
    static TBytes GenerateRandomIv();
};

#endif
