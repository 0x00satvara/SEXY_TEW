#pragma once
#include <iostream>
#include <Windows.h>
#include <stdint.h>
#include <TlHelp32.h>
#include "colors.hpp"
#include "offsets.hpp"
#include <Psapi.h>

class MEM {
	private:
		DWORD PID { };
		HANDLE hTEW { };
	public:
		// getting a snapshot to automate getting handle on the target process (TEW)
		MEM(const wchar_t* ExecName)  noexcept {
			PROCESSENTRY32W Sentry { };
			Sentry.dwSize = sizeof(PROCESSENTRY32W);
			HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			Process32FirstW(hSnap, &Sentry);
			while (Process32NextW(hSnap, &Sentry)) {
				if (!wcscmp(Sentry.szExeFile, ExecName)) {
					PID = Sentry.th32ProcessID;
					hTEW = OpenProcess(GENERIC_ALL, FALSE, PID);
					break;
				}
			}
			if (!hTEW) {
				std::cout << RED << "Make sure The evil within is launched\n" << RESET;
				std::cin.get();
				exit(EXIT_FAILURE);
			}
			if (hSnap)
				CloseHandle(hSnap);
		}
		~MEM() {
			CloseHandle(hTEW);
		}
		DWORD_PTR RPM(DWORD_PTR address, const int* Target, size_t size) noexcept {
			// looping through pointer chain reading from each one until we get to the target address,
			// that contains = the value we want to write on E.G pistol ammo etc...
			
			for (int i = 0; i < size / 4; i++) {
				if (!ReadProcessMemory(hTEW, (LPVOID)address, &address, sizeof(DWORD_PTR), NULL)) {
					CloseHandle(hTEW);
					std::cout << RED << "Make sure that you are in game\n" << RESET;
					std::cin.get();
					exit(EXIT_FAILURE);
				}
				address += Target[i];
			}
			return (address);
		}
		void WPM(DWORD_PTR address, int value) noexcept {
			WriteProcessMemory(hTEW, (LPVOID)address, &value, sizeof(int), NULL);
		}
		DWORD_PTR GetBaseAddress(void) {
			// note that number of bytes needed to fit all TEW 64bit modules in lphModule is 848
			
			HMODULE lphModule[1024];
			DWORD lpcbNeeded { };
			EnumProcessModulesEx(hTEW, lphModule, sizeof(lphModule), &lpcbNeeded, LIST_MODULES_64BIT);
			return ((DWORD_PTR)lphModule[0]);
		}
};
