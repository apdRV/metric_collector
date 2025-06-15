cmake_minimum_required(VERSION 3.10)
project(metric_collector)
set(CMAKE_CXX_STANDARD 17)
add_executable(metric_collector main.cpp MetricsCollector.cpp) 