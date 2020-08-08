#pragma once
#include "stdafx.h"

// Line Chart plotting
void lineChartHTML(const std::string& filename,
	const std::vector<double>& xValues,
	const std::vector<double>& yValues);

void histogramHTML(const std::string& filename,
	const std::vector<double>& yValues);
