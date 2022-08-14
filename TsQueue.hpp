#ifndef TS_QUEUE_HPP
#define TS_QUEUE_HPP
#pragma once

#include <cstddef>
#include <mutex>
#include <queue>

template <typename T> class TsQueue {
private:
  std::queue<T> tQ;
  std::mutex protector;

public:
  void push(T &value) {
    std::unique_lock<std::mutex> lock(protector);
    tQ.push(value);
  }

  T &front() {
    std::unique_lock<std::mutex> lock(protector);
    auto data = tQ.front();
    tQ.pop();
    return data;
  }

  size_t size() const {
    std::unique_lock<std::mutex> lock(protector);
    return tQ.size();
  }

  bool empty() const {
    std::unique_lock<std::mutex> lock(protector);
    return tQ.empty();
  }
};

#endif