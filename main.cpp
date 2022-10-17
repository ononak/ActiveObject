#include "ActiveObject.hpp"
#include "TsQueue.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

template <typename T> class DummyActiveObject : public ActiveObject<T> {

protected:
  void run(T &obj) override {
    std::cout << " Running for data  = " << obj << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
};

int main(int, char **) {

  DummyActiveObject<int> dummyWorker;
  int n = 20;
  for (auto i = 1; i < n; i++) {
    dummyWorker.process(i);
  }

  sleep(n + 1);
  std::cout << "Ending " << std::endl;
}
