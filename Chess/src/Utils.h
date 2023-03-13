#pragma once

#include <vector>
#include <string>

#include "BoardEngine.h"

namespace Utils {
	std::vector<std::string> splitString(std::string string, std::string delimiter);

	inline void trimStart(std::string& s);

	inline void trimEnd(std::string& s);

	inline void trim(std::string& s);

	namespace Debug {
		void printVector(std::vector<std::string> vec, bool asList = false);

		void printBoard(const BoardEngine& board);

		void print(std::string msg, bool endLine = true);
	}
}
