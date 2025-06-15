#include "MetricsCollector.h"
#include <fstream>
#include <iomanip>

MetricsCollector::MetricsCollector(const std::string& filename)
    : m_filename(filename), m_stop(false), m_writer_thread(&MetricsCollector::writer_thread_func, this) {}

MetricsCollector::~MetricsCollector() {
    m_stop = true;
    m_cv.notify_all();
    if (m_writer_thread.joinable()) {
        m_writer_thread.join();
    }
}

void MetricsCollector::add_metrics(const std::vector<std::shared_ptr<IMetric>>& metrics) {
    auto now = std::chrono::system_clock::now();
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.emplace(now, metrics);
    }
    m_cv.notify_one();
}

static std::string format_time(const std::chrono::system_clock::time_point& tp) {
    auto t = std::chrono::system_clock::to_time_t(tp);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()) % 1000;
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

void MetricsCollector::writer_thread_func() {
    while (!m_stop) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait_for(lock, std::chrono::milliseconds(500), [this] { return !m_queue.empty() || m_stop; });
        if (m_queue.empty()) continue;
        std::queue<std::pair<std::chrono::system_clock::time_point, std::vector<std::shared_ptr<IMetric>>>> local_queue;
        std::swap(local_queue, m_queue);
        lock.unlock();

        std::ofstream ofs(m_filename, std::ios::app);
        while (!local_queue.empty()) {
            const auto& [tp, metrics] = local_queue.front();
            ofs << format_time(tp);
            for (const auto& m : metrics) {
                ofs << " \"" << m->name() << "\" " << m->value_as_string();
            }
            ofs << '\n';
            local_queue.pop();
        }
    }
} 