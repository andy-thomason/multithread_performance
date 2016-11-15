
#include <mutex>
#include <chrono>
#include <future>
#include <iostream>

template <class Fn>
int time(Fn fn) {
  auto t1 = std::async(std::launch::async, fn);
  auto t2 = std::async(std::launch::async, fn);

  typedef std::chrono::high_resolution_clock clock;
  auto start = clock::now();
  t1.wait(); t2.wait();
  return (int)std::chrono::nanoseconds(clock::now() - start).count();
}

class double_check {
  // http://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
  std::atomic<bool> flag = false;
  std::mutex mtx;
public:
  void lock() {
    bool tmp = flag.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (!tmp) {
      mtx.lock();
      std::atomic_thread_fence(std::memory_order_release);
      flag.store(std::memory_order_release, true);
    }
  }

  void unlock() {
    
  }
};

template <class Mutex>
void time_mutex() {
  Mutex mtx;
  int x = 0;

  auto fn = [&mtx, &x]() {
    for (int i = 0; i != 10000; ++i) {
      std::lock_guard<std::mutex> lock(mtx);
      x++;
    }
  };

  for (int i = 0; i != 4; ++i) {
    printf("time_mutex %s: %d ns x=%d\n", typeid(Mutex).name(), time(fn), x);
  }
}

int main() {
  time_mutex<std::mutex>();
}


