#pragma once

#include <set>
#include <vector>

std::vector<bool> SieveResult(size_t bound); // позиции простых по решету Эратосфена
std::set<size_t> GeneratePrimeNumbersSet(size_t upperBound); // множество простых, не больших upperBound
