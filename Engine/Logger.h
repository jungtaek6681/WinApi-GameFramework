#pragma once

//============================================
//## Logger (Visual Studio 출력창에 정보표시	##
//============================================

class Logger
{
private:
	static void Log(const WCHAR tag[], const WCHAR content[])
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		GetLocalTime(&st);

		WCHAR str[30];
		swprintf_s(str, TEXT("%d/%d/%d %02d:%02d:%02d"),
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		OutputDebugString(str);
		OutputDebugString(TEXT(" "));
		OutputDebugString(tag);
		OutputDebugString(TEXT(" "));
		OutputDebugString(content);
		OutputDebugString(TEXT("\n"));
	}
public:
	static void Debug(const wstring& content)
	{
#ifdef _DEBUG	// 빌드 구성이 Debug일 경우 포함
		Log(TEXT("[Debug]"), content.c_str());
#endif
	}

	static void Info(const wstring& content)
	{
		Log(TEXT("[ Info]"), content.c_str());
	}

	static void Warning(const wstring& content)
	{
		Log(TEXT("[ Warn]"), content.c_str());
	}

	static void Error(const wstring& content)
	{
		Log(TEXT("[Error]"), content.c_str());
	}
};