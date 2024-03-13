#include <iostream>
#include <cmath>
#include <iomanip>
#include <map>

const double PI = 3.14159265358979323846;
using namespace std;
std::map<double, double> createSinLookupTable(int steps) {
    std::map<double, double> sinTable;
    double stepSize = PI / (2*steps);
    for (int i = 0; i <= steps; ++i) {
        double angle = i * stepSize ;
        sinTable[angle] = std::sin(angle);
    }
    return sinTable;
}

void printLookupTable(const std::map<double, double>& sinTable) {
    for (const auto& entry : sinTable) {
        //std::cout << std::fixed << std::setprecision(4);
        //std::cout << std::setw(10) << entry.first << std::setw(15) << entry.second << std::endl;
        cout<<"{"<<entry.first<<","<<entry.second<<"},"<<endl;
    }
    cout<<"};";
}

map<double, double> createCosLookupTable(int steps) {
    std::map<double, double> cosTable;
    double stepSize = PI / (2*steps);
    for (int i = 0; i <= steps; ++i) {
        double angle = i * stepSize;
        cosTable[angle] = std::cos(angle);
    }
    return cosTable;
}

map<double, double> createAsinLookupTable(int steps) {
    std::map<double, double> asinTable;
    double stepSize = 2.0 / steps;
    for (int i = 0; i <= steps; ++i) {
        double angle = i * stepSize - 1;
        asinTable[angle] = std::asin(angle);
    }
    return asinTable;
}

int main() {
    int steps = 1000; // Adjust the number of steps for better resolution
    std::map<double, double> sinTable = createSinLookupTable(steps);
    std::map<double, double> cosTable = createCosLookupTable(steps);
    std::map<double, double> asinTable = createAsinLookupTable(steps);

    // Print the sine lookup table
    cout<<"map<double,double> map_sin ={";
    printLookupTable(sinTable);
    cout<<"map<double,double> map_asin ={";
    printLookupTable(asinTable);
    cout<<"map<double,double> map_cos ={";
    printLookupTable(cosTable);


    return 0;
}
