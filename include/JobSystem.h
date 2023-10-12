#pragma once
#include <stdio.h>
#include <iostream>

#include <typeinfo>

#include <memory>
#include <queue>
#include <vector>

#include <functional>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>  

class JobSystem{

public:
  JobSystem();
  JobSystem(const JobSystem&) = delete;
  JobSystem(JobSystem&&) = delete;
  ~JobSystem();

  void add_task(std::function<void()>);

  void wait_until_finish();


private:

  std::vector<std::thread> m_thread_vector;
  std::queue<std::function<void()>> m_task_queue;
  std::mutex m_mutex_task;
  bool m_stop;

  std::vector<std::future<void>> m_futures;

};