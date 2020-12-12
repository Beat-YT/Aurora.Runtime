#pragma once

#ifdef _LOCAL
#define BUILD_ID "Local"
#elif _PROD
#define BUILD_ID "Prod"
#else
#define BUILD_ID "Unknown"
#endif

#ifdef _LOCAL
#define HOST_URL "http://localhost"
#else
#define HOST_URL "https://aurorafn.dev"
#endif