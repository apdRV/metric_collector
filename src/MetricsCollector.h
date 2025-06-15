#pragma once
#include "IMetric.h"
#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <chrono>
#include <memory>

class MetricsCollector {
public:
    MetricsCollector(const std::string& filename);
    ~MetricsCollector();

    void add_metrics(const std::vector<std::shared_ptr<IMetric>>& metrics);

private:
    void writer_thread_func();
    std::string m_filename;
    std::queue<std::pair<std::chrono::system_clock::time_point, std::vector<std::shared_ptr<IMetric>>>> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::thread m_writer_thread;
    std::atomic<bool> m_stop;
}; 