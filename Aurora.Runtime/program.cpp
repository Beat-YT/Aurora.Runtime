#include "program.h"
#include "build.h"
#include "util.h"

namespace aurora {
	Program::Program() {
		Util::InitConsole();

		printf("Aurora.Runtime (%s) by Cyuubi.\n", BUILD_ID);
#ifdef _PROD
		printf("Aurora by Slushia, darkblade and irma.\n");
#endif
		printf("Built on: %s at %s\n", __DATE__, __TIME__);

		m_pCurl = new Curl;
	}
	Program::~Program() {
		if (m_pCurl) {
			delete m_pCurl;
		}
	}
}
