#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>

#define VAL const auto
#define VAR auto
#define REF auto&
#define SCN const auto&

namespace Charis {

	static void DynamicAssert(bool condition, const std::string& errorMessage) {
		if (!condition) {
			std::cout << errorMessage << std::endl;
			abort();
		}
	}

}