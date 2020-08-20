#include <iostream>
#include <cmath>

unsigned benchesCount;
unsigned lightsCount;

float** benchesCoordinates;
float** lightsValues;


void freeMemory() {
    for(unsigned i = 0; i < benchesCount; ++i) {
        delete benchesCoordinates[i];
    }

    delete[] benchesCoordinates;

    for(unsigned i = 0; i < lightsCount; ++i) {
        delete lightsValues[i];
    }

    delete[] lightsValues;
}

bool isBenchInLights(float benchX, float benchY) {
    for(unsigned i = 0; i < lightsCount; ++i) {
        float lightX = lightsValues[i][0];
        float lightY = lightsValues[i][1];
        float lightR = lightsValues[i][2];

        float xDistanceFromLight = (lightX-benchX)*(lightX-benchX);
        float yDistanceFromLight = (lightY-benchY)*(lightY-benchY);
        float distanceFromLight = sqrt(xDistanceFromLight + yDistanceFromLight);

        if(distanceFromLight <= lightR) return true;
    }

    return false;
}

int main() {
    std::cout << "Enter the number of benches: ";
    std::cin >> benchesCount;

    std::cout << "Enter the number of lights: ";
    std::cin >> lightsCount;

    benchesCoordinates = new float*[benchesCount];
    lightsValues = new float*[lightsCount];
    
    //Input for benches
    for(unsigned i = 0; i < benchesCount; ++i) {
        float x;
        float y;

        std::cout << "Enter coordinates of bench " << i << ": ";

        std::cin >> x;
        std::cin >> y;

        benchesCoordinates[i] = new float[2];

        benchesCoordinates[i][0] = x;
        benchesCoordinates[i][1] = y;
    }

    //Input for lights
    for(unsigned i = 0; i < lightsCount; ++i) {
        float x;
        float y;
        float r;

        std::cout << "Enter coordinates of light " << i << ": ";

        std::cin >> x;
        std::cin >> y;

        std::cout << "Enter radius of light " << i << ": ";

        std::cin >> r;

        lightsValues[i] = new float[3];

        lightsValues[i][0] = x;
        lightsValues[i][1] = y;
        lightsValues[i][2] = r;
    }

    unsigned unlitBenchesCount = 0;
    unsigned unlitBenches[benchesCount];

    for(unsigned i = 0; i < benchesCount; ++i) {
        if(!isBenchInLights(benchesCoordinates[i][0], benchesCoordinates[i][1])) {
            unlitBenches[unlitBenchesCount++] = i;
        }
    }

    if(unlitBenchesCount == 0) {
        std::cout << "All benches are lit!" << "\n";
    } else {
        for(unsigned i = 0; i < unlitBenchesCount; ++i) {
            std::cout << "Bench " << unlitBenches[i] << " is not lit by any lamp.\n";
        }
    }

    freeMemory();

    return 0;
}
