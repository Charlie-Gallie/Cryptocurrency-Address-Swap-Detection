#include <iostream>
#include <Windows.h>
#include <chrono>
#include <string>
#include <regex>

using namespace std;

string waitForClipboardUpdate(string oldValue) {
	for (;;) {
		if (OpenClipboard(NULL)) {
			if (IsClipboardFormatAvailable(CF_TEXT)) {
				HANDLE hData = GetClipboardData(CF_TEXT);
				if (hData != nullptr) {
					void* v = GlobalLock(hData);
					if (v != nullptr) {
						string s((char*)v);
						if (s != oldValue) {
							GlobalUnlock(hData);
							return s;
						}
						GlobalUnlock(hData);
					}
				}
			}
			CloseClipboard();
		}
		Sleep(1);
	}
}

std::wstring stringToWString(const std::string& s) {
	int len, slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void warnUser(string previous, string current, chrono::microseconds time) {
	const string message =
		"Cryptocurrency address changed in " +
		to_string(time.count()) +
		" microseconds:\n\n" +
		previous +
		"\nTo\n" +
		current;
	MessageBox(nullptr, stringToWString(message).c_str(), TEXT("Clipboard Manipulation Detected"), MB_OK);
}

bool isCryptoAddress(string value) {
	regex addressRegex("\\b(bc(0([ac-hj-np-z02-9]{39}|[ac-hj-np-z02-9]{59})|1[ac-hj-np-z02-9]{8,87})|[13][a-km-zA-HJ-NP-Z1-9]{25,35})\\b");
	//I'll work on matching more cryptocurrency address formats.
	smatch matches;
	return regex_search(value, matches, addressRegex);
}

bool isSuspicious(string previous, string current, chrono::microseconds time, int sensitivity) {
	if (sensitivity < time.count()) return false;
	return (isCryptoAddress(current));
	return false;
}

int main(int n_args, char* args[]) {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	float sensitivity = n_args > 1 ? stoi(args[1]) : 1;
	string currentClipboardText,
		previousClipboardText;
	chrono::steady_clock::time_point
		firstClip,
		secondClip{chrono::steady_clock::now()};
	for (;;) {
		firstClip = chrono::steady_clock::now();
		previousClipboardText = currentClipboardText;
		currentClipboardText = waitForClipboardUpdate(currentClipboardText);
		secondClip = chrono::steady_clock::now();
		chrono::microseconds timeDifference =
			chrono::duration_cast<chrono::microseconds>(abs(firstClip - secondClip));
		if (isSuspicious(previousClipboardText, currentClipboardText, timeDifference, 1000000 * sensitivity)) {
			warnUser(previousClipboardText, currentClipboardText, timeDifference);
		}
	}
	return 0;
}
