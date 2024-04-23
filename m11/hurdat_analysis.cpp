/*
    Data analysis with std::regex to print out the Saffir-Simpson Day
    of hurricanes for year 1851 to year 2011.

    Data source from hurdat_atlantic_1851-2011.txt and its format clarification in HURDAT format.pdf
*/

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>
#include <sstream>

// Can also test hypothesis that hurricane is getting stronger -> whether slope of the plotted line is 0
// p value < 0.05 -> reject null hypothesis <hurricane is not getting strong>.
// p value is 0.3 in our case, not enough evidence for hurricane getting stronger.

// Map wind speed to Saffir-Simpson scale.
// https://en.wikipedia.org/wiki/Saffir%E2%80%93Simpson_scale
int mapToSaffirSimpson(int windSpeed) {
    if (windSpeed < 64) return 0; // TS or TD
    else if (windSpeed < 83) return 1; // Category 1
    else if (windSpeed < 96) return 2; // Category 2
    else if (windSpeed < 113) return 3; // Category 3
    else if (windSpeed < 137) return 4; // Category 4
    return 5; // Category 5
}

int main() {
    std::ifstream file("hurdat_atlantic_1851-2011.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::map<int, double> yearSaffirSimpsonTotals;

    std::string line;
    std::regex yearRegex(R"(\d{2}/\d{2}/(\d{4}))");
    std::regex dayRegex(R"(M=\s*(\d+)\s)");
    std::smatch match;
    int year;
    int day;

    while (std::getline(file, line)) {
        std::regex_search(line, match, yearRegex); // return bool
        // Parse the year
        year = std::stoi(match[1]);
        if (!yearSaffirSimpsonTotals.count(year)) {
            yearSaffirSimpsonTotals[year] = 0;
        }

        // Parse the number of days
        std::regex_search(line, match, dayRegex);
        day = std::stoi(match[1]);


        for (int i = 0; i < day; ++i) {
            std::getline(file, line); // Move to the data line

            // Data formats include:
            //00010 06/25*280 948  80    0*280 954  80    0*280 960  80    0*281 965  80    0*
            //02535 07/25*  0   0   0    0*  0   0   0    0*240 890  60    0*  0   0   0    0*
            //02495 10/01E303 913  40    0E304 907  40    0E305 901  40    0E306 895  40    0*
            //There may also be press after the windspeed (see HURDAT format.pdf for clarifications)
            std::regex windSpeedRegex(R"(\d{5}\s\d{2}/\d{2}.\s*\d+\s*\d+\s+(\d+)\s+\d+.\s*\d+\s*\d+\s+(\d+)\s+\d+.\s*\d+\s*\d+\s+(\d+)\s+\d+.\s*\d+\s*\d+\s+(\d+))");
            std::regex_search(line, match, windSpeedRegex);
            int windSpeed;

            for (int j = 1; j < 5; j++) {
                windSpeed = std::stoi(match[j]);
                yearSaffirSimpsonTotals[year] += (float) mapToSaffirSimpson(windSpeed) / 4.0;
            }
            
        }

        // Skip the trailer line
        std::getline(file, line);
    }

    // Print the Year and its Saffir-Simpson Day total
    std::cout << "Year\tSaffir-Simpson Day Totals" << std::endl;
    for (const auto& entry : yearSaffirSimpsonTotals) {
        std::cout << entry.first << "\t" << entry.second << std::endl;
    }

    file.close();
    return 0;
}
