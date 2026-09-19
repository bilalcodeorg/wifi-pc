#ifndef WPC_EXPORT_H
#define WPC_EXPORT_H

/*
 * WPC_BUILD_SHARED   - define when building the library as a shared lib (.dll/.so/.dylib)
 * WPC_STATIC         - define when building/using the library as a static lib
 * WPC_COMPILING      - define only in the library's own source files (not by consumers)
 */


/* Static builds need no import/export decoration */
#if defined(WPC_STATIC)
	#define WPC_API


/* Windows: __declspec(dllexport/dllimport) */
#elif defined(_WIN32) || defined(__CYGWIN__)
	#ifdef WPC_COMPILING
		#ifdef __GNUC__
			#define WPC_API __attribute__((dllexport))
		#else
			#define WPC_API __declspec(dllexport)
		#endif // __GNUC__
	#else // WPC_COMPILING
		#ifdef __GNUC__
			#define WPC_API __attribute__((dllimport))
		#else
			#define WPC_API __declspec(dllimport)
		#endif // __GNUC__
	#endif // WPC_COMPILING


/* GCC/Clang on Linux, macOS, etc. */
#elif defined(__GNUC__) && __GNUC__ >= 4
	#define WPC_API __attribute__((visibility("default")))
#else
	#define WPC_API
#endif

/* Optional: local/hidden symbol marker for internal-only functions */
#if defined(_WIN32) || defined(__CYGWIN__)
	#define WPC_LOCAL
#elif defined(__GNUC__) && __GNUC__ >= 4
	#define WPC_LOCAL __attribute__((visibility("hidden")))
#else
	#define WPC_LOCAL
#endif

#endif /* WPC_EXPORT_H */