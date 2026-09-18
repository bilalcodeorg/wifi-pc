#ifndef WIFI_PC_EXPORT_H
#define WIFI_PC_EXPORT_H

/*
 * WIFI_PC_BUILD_SHARED   - define when building the library as a shared lib (.dll/.so/.dylib)
 * WIFI_PC_STATIC         - define when building/using the library as a static lib
 * WIFI_PC_COMPILING      - define only in the library's own source files (not by consumers)
 */


/* Static builds need no import/export decoration */
#if defined(WIFI_PC_STATIC)
	#define WIFI_PC_API


/* Windows: __declspec(dllexport/dllimport) */
#elif defined(_WIN32) || defined(__CYGWIN__)
	#ifdef WIFI_PC_COMPILING
		#ifdef __GNUC__
			#define WIFI_PC_API __attribute__((dllexport))
		#else
			#define WIFI_PC_API __declspec(dllexport)
		#endif // __GNUC__
	#else // WIFI_PC_COMPILING
		#ifdef __GNUC__
			#define WIFI_PC_API __attribute__((dllimport))
		#else
			#define WIFI_PC_API __declspec(dllimport)
		#endif // __GNUC__
	#endif // WIFI_PC_COMPILING


/* GCC/Clang on Linux, macOS, etc. */
#elif defined(__GNUC__) && __GNUC__ >= 4
	#define WIFI_PC_API __attribute__((visibility("default")))
#else
	#define WIFI_PC_API
#endif

/* Optional: local/hidden symbol marker for internal-only functions */
#if defined(_WIN32) || defined(__CYGWIN__)
	#define WIFI_PC_LOCAL
#elif defined(__GNUC__) && __GNUC__ >= 4
	#define WIFI_PC_LOCAL __attribute__((visibility("hidden")))
#else
	#define WIFI_PC_LOCAL
#endif

#endif /* WIFI_PC_EXPORT_H */