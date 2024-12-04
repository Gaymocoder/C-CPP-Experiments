#include "gcsio.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _WIN32
    #include <fcntl.h>
#endif

// 
void setNormalLocaleW()
{
    #ifdef _WIN32
        _setmode(_fileno(stdin), _O_U16TEXT);
        _setmode(_fileno(stdout), _O_U16TEXT);
    #else
        setlocale(LC_CTYPE, "en_US.utf8");
    #endif
}

void clearConsole()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clearStdinBuf()
{
    wchar_t wc = -1;
    while (wc != EOF && wc != 10)
        wc = getwchar();
}

void gcs_fgetws(wchar_t** wcstr, const size_t MAX_STR_LEN)
{
    fgetws(*wcstr, MAX_STR_LEN, stdin);
    size_t wcstrLen = wcslen(*wcstr);

    if ((*wcstr)[wcstrLen-1] == 10)
    {
        (*wcstr)[wcstrLen-1] = 0;
        --wcstrLen;
    }
    else clearStdinBuf();

    *wcstr = (wchar_t*) realloc (*wcstr, (wcstrLen + 1) * sizeof(wchar_t));
}
