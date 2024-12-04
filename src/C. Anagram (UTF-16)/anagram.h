#ifndef __ANAGRAM_H__
#define __ANAGRAM_H__

#include <wchar.h>

#ifdef _WIN32
	#include <stddef.h>
#endif

// Function which reverses wchar-c-string
void reversit(wchar_t* str);

#endif
