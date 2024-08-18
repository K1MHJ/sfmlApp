#pragma once

#include "Core/PlatformDetection.h"

#ifdef PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

#include "Core/Base.h"
#include "Core/Log.h"
#include "Debug/Instrumentor.h"
