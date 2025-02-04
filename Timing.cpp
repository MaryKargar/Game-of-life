#include "Timing.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

Timing* Timing::mInstance = nullptr;

Timing* Timing::getInstance() {
    if (!mInstance) {
        mInstance = new Timing();
    }
    return mInstance;
}

void Timing::startSetup() {
    setupStart = std::chrono::steady_clock::now();
}

void Timing::stopSetup() {
    auto end = std::chrono::steady_clock::now();
    setupDuration += std::chrono::duration<double, std::milli>(end - setupStart).count();
}

void Timing::startComputation() {
    computationStart = std::chrono::steady_clock::now();
}

void Timing::stopComputation() {
    auto end = std::chrono::steady_clock::now();
    computationDuration += std::chrono::duration<double, std::milli>(end - computationStart).count();
}

void Timing::startFinalization() {
    finalizationStart = std::chrono::steady_clock::now();
}

void Timing::stopFinalization() {
    auto end = std::chrono::steady_clock::now();
    finalizationDuration += std::chrono::duration<double, std::milli>(end - finalizationStart).count();
}

std::string Timing::getResults() const {
    std::ostringstream oss;
    oss << "Setup: " << setupDuration << " ms\n"
        << "Computation: " << computationDuration << " ms\n"
        << "Finalization: " << finalizationDuration << " ms";
    return oss.str();
}

// Getter methods
double Timing::getSetupDuration() const { return setupDuration; }
double Timing::getComputationDuration() const { return computationDuration; }
double Timing::getFinalizationDuration() const { return finalizationDuration; }
