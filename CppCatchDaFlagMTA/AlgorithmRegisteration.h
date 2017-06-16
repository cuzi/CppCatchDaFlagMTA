#pragma once
#include <map>
#include <string>
#include <functional>
#include "AbstractPlayer.h"

class AlgorithmRegistration {
public:
	// our game manager would use the exact same AlgorithmRegistration ctor!
	AlgorithmRegistration(const std::string& id, std::function<AbstractPlayer*(void)> func) {
		algoFactory[id] = func;
	}
	// you cannot assume that our game manager would use this exact same static member
	// in your code, your AlgorithmRegistration should better use a private static member and a public getter
	// your public getter should better return const reference to the map
	static std::map <std::string, std::function < AbstractPlayer*(void) >> algoFactory;
};
