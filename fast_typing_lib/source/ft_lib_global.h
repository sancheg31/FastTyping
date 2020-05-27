#pragma once


#include <QtCore/qglobal.h>

#if defined(FAST_TYPING_LIBRARY)
#  define FT_LIB_EXPORT Q_DECL_EXPORT
#else
#  define FT_LIB_EXPORT Q_DECL_IMPORT
#endif
