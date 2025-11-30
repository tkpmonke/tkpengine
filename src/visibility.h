#pragma once

#if !defined(TKP_EXPORT)
	#if defined(_MSC_VER)
		#define TKP_EXPORT __declspec(dllexport)
	#elif defined(__GNUC__)
		#define TKP_EXPORT __attribute__((visibility("default")))
	#endif
#endif
