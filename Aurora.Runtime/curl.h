#pragma once

#include "hook.h"

namespace aurora {
	class Curl {
	private:
		Hook* m_pCurlEasySetoptHook;

	public:
		Curl();
		~Curl();
	};
}
