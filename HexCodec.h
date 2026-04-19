#ifndef HexCodecH
#define HexCodecH

#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

class HexCodec
{
public:
    static TBytes ParseDisplayHex(const UnicodeString &hex, int expectedBytes);
    static UnicodeString ToDisplayHex(const TBytes &internalBytes);
    static UnicodeString Normalize(const UnicodeString &hex);
};

#endif
