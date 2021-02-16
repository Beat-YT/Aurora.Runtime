#pragma once

#ifdef _DEV
#define BUILD_ID "Dev"
#elif _PROD
#define BUILD_ID "Prod"
#else
#define BUILD_ID "Unknown"
#endif