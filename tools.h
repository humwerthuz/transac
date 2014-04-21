#ifndef TOOLS_H
#define TOOLS_H
#include <string.h>

//Algunas macros para el manejo de strings
#define _STR_CPY(to,from) to=(char*)malloc(sizeof(from));strcpy(to,from)
#define _STRING_COPY _STR_CPY
#define _CHAR_COPY(to,from) strcpy(to,from)
#define _NEWCHAR(to,size) to=(char*)malloc(size + 1)

#endif
