#pragma once

// WinApi 프레임워크
#include <Windows.h>

// WinApi img32 라이브러리
#pragma comment(lib, "MsImg32.lib")

// FMOD 사운드
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

using namespace FMOD;

// C++ 표준 라이브러리
#include <cassert>
#include <chrono>
#include <string>
#include <array>
#include <map>
#include <list>
#include <queue>
#include <unordered_map>

using namespace std;

// Util
#include "SingleTon.h"
#include "Component.h"
#include "Struct.h"
#include "Logger.h"