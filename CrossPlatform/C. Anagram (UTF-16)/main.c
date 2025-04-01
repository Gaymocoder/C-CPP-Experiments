#include "gcsio.h"
#include "anagram.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char** argv)
{
    setNormalLocaleW();
    
    const size_t MAX_STR_LEN = 1024;
    wchar_t* str = (wchar_t*) malloc (MAX_STR_LEN * sizeof(wchar_t));

    wprintf(L"Введите строку: ");
    gcs_fgetws(&str, MAX_STR_LEN);
    reversit(str);
    
    wprintf(L"Перевернутая строка: %ls\n", str);
    free(str);

    return 0;
}
