#include "JobSystem.h"


JobSystem::JobSystem(){

  m_stop = false;
  auto threads_count = std::thread::hardware_concurrency();
  printf("threads-> %d\n", threads_count);

  // Creamos tantos thread como podamos y los metemos en el vector de threads
  for(int i = 0; i < threads_count; i++){

    auto thread_worker = [this](){
      while(!m_stop){
        std::function<void()> task;

        {
          std::lock_guard<std::mutex> locked {m_mutex_task};
          if(!m_task_queue.empty()){
            task = m_task_queue.front();
            m_task_queue.pop();
          }
        }

        task();

      }
    };

    m_thread_vector.push_back( std::thread{ std::move(thread_worker) } );
  }



}

void JobSystem::add_task(std::function<void()> callback){
  std::lock_guard<std::mutex> locked {m_mutex_task};
  m_task_queue.push(std::move(callback));
}

JobSystem::~JobSystem(){

  m_stop = true;
  // Esperamos a que terminen todos los hilos antes de destruir
  /*for(auto &t : m_thread_vector){
    
    if(t.joinable()){
      t.join();
    }
  }*/

}

