#ifndef PNG_USE_H
#define PNG_USE_H
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>

/* Microsoft Visual C++ */
#ifdef _MSC_VER
#pragma comment (lib, "libpng.lib")
#pragma comment (lib, "zlib.lib")
#pragma comment (linker, "/nodefaultlib:libc")
#endif	/* _MSC_VER */

GLuint loadPNGTexture (const char *filename);

#endif
