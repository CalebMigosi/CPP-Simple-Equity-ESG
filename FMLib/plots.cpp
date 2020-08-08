#include "plots.h"
#include "stdafx.h"
#include "matlib.h"

using namespace std;

//======================================================
//					PLOTS
//======================================================
static inline void boilerPlateFirstPiece(ostream& outHTML) {
	outHTML << "<html>\n";
	outHTML << "<head>\n";
	outHTML << "<script type = \"text/javascript\" src = \"https://www.gstatic.com/charts/loader.js\"></script>\n";
	outHTML << "<script type = \"text/javascript\">\n";
	outHTML << "google.charts.load('current', { 'packages': ['corechart'] });\n";
	outHTML << "google.charts.setOnLoadCallback(drawChart);\n";

	outHTML << "function drawChart() {\n";
	outHTML << "var data = google.visualization.arrayToDataTable([\n";
}

static inline void boilerPlateFinalPiece(ostream& outHTML, string& curveType) {
	outHTML << "</script>\n";
	outHTML << "</head>\n";
	outHTML << "<body>\n";
	outHTML << "<div id = \""<<curveType <<"\" style = \"width: 900px; height: 500px\"></div>\n";
	outHTML << "</body>\n";
	outHTML << "</html>\n";
}

static inline void varOptionsLineChart(ostream& outHTML) {
	outHTML << "['xAxis', 'yAxis'],\n";
	outHTML << "] );\n";
	outHTML << "\n";
	outHTML << "options = {\n";
	outHTML << "title: 'Line Chart',\n";
	outHTML << "curveType : 'function',\n";
	outHTML << "legend : { position: 'bottom' }\n";
	outHTML << "};\n";
	outHTML << "\n";
	outHTML << "var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));\n";
	outHTML << "\n";
	outHTML << "chart.draw(data, options);\n";
	outHTML << "}\n";
	outHTML << "</script>\n";
	outHTML << "</head>\n";
	outHTML << "<body>\n";
	outHTML << "<div id = \"curve_chart\" style = \"width: 900px; height: 500px\"></div>\n";
	outHTML << "</body>\n";
	outHTML << "</html>\n";
}

static inline void varOptionsHistogram(ostream& outHTML, int minValue, int maxValue, int maxBuckets) {
	outHTML << "] );\n";
	outHTML << "var options = {\n";
	outHTML << "	title: 'Distribution',\n";
	outHTML << "	legend : { position: 'none' },\n";
	outHTML << "	colors : ['#4285F4'] ,\n";
	outHTML << "\n";
	outHTML << "	chartArea : { width: 405 },\n";
	outHTML << "	bar : { gap: 0 },\n";
	outHTML << "\n";
	outHTML << "	histogram : {\n";
	outHTML << "	  bucketSize: 1,\n";
	outHTML << "	  maxNumBuckets : " << maxBuckets << ",\n";
	outHTML << "	  minValue : "<< minValue << ",\n";
	outHTML << "	  maxValue : " << maxValue << "\n";
	outHTML << "	}\n";
	outHTML << "};\n";
	outHTML << "var chart = new google.visualization.Histogram(document.getElementById('chart_div'));\n";
	outHTML << "chart.draw(data, options);\n";
	outHTML << "}\n";

}

// Line Chart
void lineChartHTML(const string& filename,
	const vector<double>& xValues,
	const vector<double>& yValues) {

	// Ensure the labels have the same size as values
	assert(xValues.size() == yValues.size());

	int n = xValues.size(); // Length of labels

	ofstream out;
	out.open(filename + ".html");
	boilerPlateFirstPiece(out);
	out << "['xValues', 'yAxis']";

	// Write the data
	for (int i = 0; i < n; i++) {
		out << "[" << xValues[i] << ", " << yValues[i] << "],\n";
	}
	varOptionsLineChart(out);
	out.close();
}

// Histogram Chart
void histogramHTML(const std::string& filename,
	const std::vector<double>& yValues) {

	// Ensure the labels have the same size as values
	int n = yValues.size(); // Length of labels

	ofstream out;
	out.open(filename + ".html");
	boilerPlateFirstPiece(out);

	out << "['Names', 'Values'],\n";
	// Write the data
	for (int i = 0; i < n; i++) {
		out << "[" << "'Price', " << yValues[i] << "],\n";
	}
	double maxBuckets =  maximum(yValues) -0.001;
	double minBuckets =  minimum(yValues) -0.001;

	if (maxBuckets <= 10) {
		maxBuckets *= 100;
		minBuckets *= 100;
	}
	varOptionsHistogram(out, (int)minBuckets, (int)maxBuckets, 100);
	string chartName("chart_div");
	boilerPlateFinalPiece(out, chartName);
	out.close();
}
