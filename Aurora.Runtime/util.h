#pragma once

#include <windows.h>
#include <psapi.h>
#include <cstdio>

namespace aurora {
	class Util {
	private:
		static BOOL MaskCompare(PVOID pBuffer, LPCSTR lpPattern, LPCSTR lpMask) {
			for (auto val = static_cast<PBYTE>(pBuffer); *lpMask; ++lpPattern, ++lpMask, ++val) {
				if (*lpMask == 'x' && *reinterpret_cast<LPCBYTE>(lpPattern) != *val) {
					return false;
				}
			}

			return true;
		}

		static PBYTE FindPattern(PVOID pBase, DWORD dwSize, LPCSTR lpPattern, LPCSTR lpMask) {
			dwSize -= static_cast<DWORD>(strlen(lpMask));

			for (auto i = 0UL; i < dwSize; ++i) {
				auto pAddr = static_cast<PBYTE>(pBase) + i;

				if (MaskCompare(pAddr, lpPattern, lpMask)) {
					return pAddr;
				}
			}

			return NULL;
		}

	public:
		static VOID InitConsole() {
			AllocConsole();

			// Redirect stdout to our newly allocated console.
			FILE* pFile;
			freopen_s(&pFile, "CONOUT$", "w", stdout);
		}

		static uintptr_t BaseAddress() {
			return reinterpret_cast<uintptr_t>(GetModuleHandle(0));
		}

		static PBYTE FindPattern(LPCSTR lpPattern, LPCSTR lpMask) {
			// Grab module info, used for obtaining info like lpBaseOfDll and SizeOfImage.
			MODULEINFO info{};
			GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));

			// Spin-out until the address has been found.
			PBYTE pAddr = NULL;
			do {
				pAddr = FindPattern(info.lpBaseOfDll, info.SizeOfImage, lpPattern, lpMask);

				Sleep(50); // This could cause Fortnite to hang, at startup. [ NOTE(Cyuubi): Reduced from 200ms to 50ms because Program is on different thread now. ]
			} while (!pAddr);

			// After the spin-out has been completed, return the address!
			return pAddr;
		}
	};
}
