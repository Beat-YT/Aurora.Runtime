#pragma once

#include "curl.h"

namespace aurora
{
	class Program
	{
	private:
		Curl* m_pCurl;

	public:
		Program();
		~Program();
	};
}
