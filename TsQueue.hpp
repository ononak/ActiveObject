#ifndef TS_QUEUE_HPP
#define TS_QUEUE_HPP
#pragma once

#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>

template <typename T> class TsQueue {
private:
  std::queue<T> tQ;
  std::mutex protector;

public:
  virtual ~TsQueue() {
    std::cout << "TSQueue destructor" << std::endl;
    tQ = {};
  }
  void push(const T &value) {
    std::unique_lock<std::mutex> lock(protector);
    tQ.push(value);
  }

  T front() {
    std::unique_lock<std::mutex> lock(protector);
    auto data = tQ.front();
    tQ.pop();
    return data;
  }

  size_t size() {
    std::unique_lock<std::mutex> lock(protector);
    return tQ.size();
  }

  bool empty() {
    std::unique_lock<std::mutex> lock(protector);
    return tQ.empty();
  }
};

#endif
