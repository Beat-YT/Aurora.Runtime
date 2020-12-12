#pragma once

#ifdef _LOCAL
#define BUILD_NAME "Local"
#elif _PROD
#define BUILD_NAME "Prod"
#else
#define BUILD_NAME "Unknown"
#endif

//#define AURORA
#ifndef AURORA
#define HOST_URL "http://localhost"
#else
#define HOST_URL "https://aurorafn.dev"
#endif