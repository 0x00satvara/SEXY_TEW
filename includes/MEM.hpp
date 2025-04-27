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
		MEM(const wchar_t* ExecName)  noexcept;
		~MEM();
		DWORD_PTR RPM(DWORD_PTR address, const int* Target, size_t size) noexcept;
		void WPM(DWORD_PTR address, int value) noexcept;
		DWORD_PTR GetBaseAddress(void);
};
