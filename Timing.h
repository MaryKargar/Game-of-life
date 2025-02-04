#pragma once
#include <chrono>
#include <string>

class Timing {
public:
    static Timing* getInstance();
    void startSetup();
    void stopSetup();
    void startComputation();
    void stopComputation();
    void startFinalization();
    void stopFinalization();
    std::string getResults() const;

    // Add getter methods for private members
    double getSetupDuration() const;
    double getComputationDuration() const;
    double getFinalizationDuration() const;

private:
    Timing() = default;
    static Timing* mInstance;
    std::chrono::steady_clock::time_point setupStart, computationStart, finalizationStart;
    double setupDuration = 0.0, computationDuration = 0.0, finalizationDuration = 0.0;
};
