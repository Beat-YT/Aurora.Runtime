#pragma once

#include "hook.h"

namespace aurora
{
	class Curl
	{
	public:
		Curl();
		~Curl();

		uintptr_t m_pCurlVsetoptAddress;

		Hook* m_pCurlVsetoptHook;
	};
}

extern aurora::Curl* g_pCurl;
