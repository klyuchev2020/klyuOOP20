#pragma once

#include "stdafx.h"

std::vector<float> LoadSeriesToVector(std::istream& input);
void LoadVectorToSeries(const std::vector<float>& values, std::ostream& output);
void Modificate(std::vector<float>& values);
