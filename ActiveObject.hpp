#ifndef ACTIVE_OBJECT_HPP
#define ACTIVE_OBJECT_HPP
#pragma once

#include "TsQueue.hpp"
#include <condition_variable>
#include <iostream>
#include <thread>

template <typename T> class ActiveObject {
private:
  TsQueue<T> safeQueue;
  std::condition_variable cv;
  std::mutex protector;
  std::thread processor;
  bool shutdown;

public:
  ActiveObject() : shutdown(false) {
    processor = std::thread(&ActiveObject<T>::dataLoop, this);
  }
  virtual ~ActiveObject() {
    std::cout << "ActiveObject destruct" << std::endl;
    shutdown = true;
    cv.notify_one();
    processor.join();
  }
  void process(T &obj) {
    safeQueue.push(obj);
    std::cout << "Number of the data in the loop is" << safeQueue.size()
              << std::endl;
    cv.notify_one();
  }

protected:
  void dataLoop() {
    std::unique_lock<std::mutex> lock(protector);

    while (!shutdown) {
      if (safeQueue.empty()) {
        std::cout << "Waiting for data..." << std::endl;
        cv.wait(lock);
      }

      if (!shutdown) {
        auto data = safeQueue.front();
        run(data);
      }
    }
  }

  virtual void run(T &obj) {}

private:
  ActiveObject(const ActiveObject &) = delete;
  ActiveObject(const ActiveObject &&) = delete;
  ActiveObject &operator=(const ActiveObject &) = delete;
};

#endif // ACTIVE_OBJECT_HPP
