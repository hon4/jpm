#ifndef BUILD_ARCH_HPP
#define BUILD_ARCH_HPP

//Not Ready
#if defined(__x86_64__) || defined(_M_X64)
	#define JPM_ARCHITECTURE "amd64"
#elif defined(__i386__) || defined(_M_IX86)
	#define JPM_ARCHITECTURE "i386"
#else
	#define JPM_ARCHITECTURE "unknown"
#endif

#endif
