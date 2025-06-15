#include "MetricsCollector.h"
#include "Metric.h"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    MetricsCollector collector("metrics.txt");

    for (int i = 0; i < 5; ++i) {
        double cpu = 0.8 + 0.1 * i;
        int rps = 40 + i * 2;
        collector.add_metrics({
            std::make_shared<Metric<double>>("CPU", cpu),
            std::make_shared<Metric<int>>("HTTP requests RPS", rps)
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Metrics written to metrics.txt\n";
} 