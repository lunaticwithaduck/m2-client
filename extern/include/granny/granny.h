#ifndef GRANNY_INCALL_H
#define GRANNY_INCALL_H

#if !defined(__GRANNY_VERSION__) || __GRANNY_VERSION__ == 4
#include "granny24.h"
#pragma comment(lib, "granny24.lib")
#elif __GRANNY_VERSION__ == 9
#include "granny29.h"
#pragma comment(lib, "granny29.lib")
#else
#error "Unsupported __GRANNY_VERSION__" __GRANNY_VERSION__
#endif

#endif // GRANNY_H
