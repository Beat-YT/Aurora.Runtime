#include "curl.h"
#include "util.h"
#include "build.h"
#include <windows.h>
#include <string>
#include <regex>

#include <minhook.h>
#pragma comment(lib, "libMinHook.x64.lib")

aurora::Curl* g_pCurl;

namespace aurora
{
	INT (*CurlVsetopt_)(LPVOID, INT, va_list) = NULL;
	INT CurlVsetoptHook(LPVOID lpContext, INT iOption, va_list param); // Forward declaring this is necessary!! 
	INT CurlVsetopt(LPVOID lpContext, INT iOption, va_list param)
	{
		g_pCurl->m_pCurlVsetoptHook->~Hook();

		INT iResult = CurlVsetopt_(lpContext, iOption, param);

		g_pCurl->m_pCurlVsetoptHook = new Hook(g_pCurl->m_pCurlVsetoptAddress, reinterpret_cast<uintptr_t>(CurlVsetoptHook));
		if (!g_pCurl->m_pCurlVsetoptHook->bSuccess)
		{
			printf("Reinstalling hook for CurlVsetopt has failed, exiting immediately!\n");
			exit(EXIT_FAILURE);
		}

		return iResult;
	}
	INT CurlVsetoptVa(LPVOID lpContext, INT iOption, ...)
	{
		va_list list{};
		va_start(list, iOption);

		INT iResult = CurlVsetopt(lpContext, iOption, list);

		va_end(list);

		return iResult;
	}
	INT CurlVsetoptHook(LPVOID lpContext, INT iOption, va_list param)
	{
		va_list copy{}; // Copy only exists for our tag overrides.
		va_copy(copy, param);

		INT iResult = 0;

		switch (iOption)
		{
			case 64: // CURLOPT_SSL_VERIFYPEER
				iResult = CurlVsetoptVa(lpContext, iOption, FALSE); // Disables VerifyPeer.
				break;

			default: // Everything else.
				iResult = CurlVsetopt(lpContext, iOption, param);
				break;
		}

		va_end(copy);

		return iResult;
	}

	Curl::Curl()
	{
		g_pCurl = this;

		m_pCurlVsetoptAddress = reinterpret_cast<uintptr_t>(Util::FindPattern
		(
			"\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x48\x89\x7C\x24\x20\x41\x56\x48\x83\xEC\x40\x33\xED\x49\x8B\xF0\x44",
			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
		));
		if (!m_pCurlVsetoptAddress)
		{
			printf("Finding pattern for CurlVsetopt has failed, exiting immediately!\n");
			exit(EXIT_FAILURE);
		}

		CurlVsetopt_ = reinterpret_cast<decltype(CurlVsetopt_)>(m_pCurlVsetoptAddress);

		m_pCurlVsetoptHook = new Hook(m_pCurlVsetoptAddress, reinterpret_cast<uintptr_t>(CurlVsetoptHook));
		if (!m_pCurlVsetoptHook->bSuccess)
		{
			printf("Initializing hook for CurlVsetopt has failed, exiting immediately!\n");
			exit(EXIT_FAILURE);
		}
	}
	Curl::~Curl()
	{
		if (m_pCurlVsetoptHook)
		{
			delete m_pCurlVsetoptHook;
		}
	}
}
