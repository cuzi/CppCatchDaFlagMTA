#include "AlgorithmRegisteration.h"

std::map<std::string, std::function<AbstractPlayer*(void)>> AlgorithmRegistration::algoFactory;
