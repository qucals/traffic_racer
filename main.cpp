#include <iostream>

#include <random>
#include <ctime>

#include "traffic_racer/engine.h"

int main() {
    srand(time(nullptr));

    traffic_racer::engine eng;
    eng.run();

    return 0;
}

