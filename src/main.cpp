#include "../includes/utils.hpp"
#include "../includes/colors.hpp"
#include <synchapi.h>

void print(void) {
	std::cout << MAGENTA << R"(
   _____      _________      __     _____               _____ ____  _   _  _____  ____  _      ______ 
  / ____|  /\|__   __\ \    / /\   |  __ \     /\      / ____/ __ \| \ | |/ ____|/ __ \| |    |  ____|
 | (___   /  \  | |   \ \  / /  \  | |__) |   /  \    | |   | |  | |  \| | (___ | |  | | |    | |__   
  \___ \ / /\ \ | |    \ \/ / /\ \ |  _  /   / /\ \   | |   | |  | | . ` |\___ \| |  | | |    |  __|  
  ____) / ____ \| |     \  / ____ \| | \ \  / ____ \  | |___| |__| | |\  |____) | |__| | |____| |____ 
 |_____/_/    \_\_|      \/_/    \_\_|  \_\/_/    \_\  \_____\____/|_| \_|_____/ \____/|______|______|                                                             
	)" << RESET;
	std::cout << CYAN << "---------------------------------------------------------------------------------\n\n" << RESET;
	std::cout << BLUE << "[+] PRESS 1 TO INCREMENT PISTOL MAGAZINE\n\n";
	std::cout << "[+] PRESS 2 TO INCREMENT SHOTGUN MAGAZINE\n\n";
	std::cout << "[+] PRESS 3 TO INCREMENT NUMBER OF MEDKITS\n\n" << RESET;
}

void	success(void) {
	std::cout << RED << "Memory written successfully !!!\n" << RESET;
	std::cout << YELLOW << ">> " << RESET;
}

int main(void) {

	print();
	MEM mem { L"EvilWithin.exe" };
	DWORD_PTR ToWrite;

	DWORD_PTR BaseAddress = mem.GetBaseAddress();
	BaseAddress += LocalPlayer;

	std::cout << YELLOW << ">> " << RESET;
	while (true) {
		for (int vkey = 0; vkey < 256; vkey++) {
			if (GetAsyncKeyState(vkey) & 0x8000) {
				switch (vkey) {
				case (49):
					ToWrite = mem.RPM(BaseAddress, PistolAmmo, sizeof(PistolAmmo));
					mem.WPM(ToWrite, 999);
					success();
					break;
				case (50):
					ToWrite = mem.RPM(BaseAddress, ShotgunAmmo, sizeof(ShotgunAmmo));
					mem.WPM(ToWrite, 999);
					success();
					break;
				case (51):
					ToWrite = mem.RPM(BaseAddress, Medkit, sizeof(ShotgunAmmo));
					mem.WPM(ToWrite, 999);
					success();
					break;
				default:
					break;
				}
			}
		}
		Sleep(100);
	}
	return (EXIT_SUCCESS);
}
