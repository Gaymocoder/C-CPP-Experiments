#include "anagram.h"

void reversit(wchar_t* str)
{
    size_t strLen = wcslen(str);

    for(size_t i = 0; i < (strLen / 2); ++i)
    {
        wchar_t cbuf = str[i];
        str[i] = str[strLen - (i+1)];
        str[strLen - (i+1)] = cbuf;
    }
}
