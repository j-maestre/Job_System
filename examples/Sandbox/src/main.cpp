#include <stdio.h>
#include <iostream>
#include <chrono>
#include "JobSystem.h"


void Easy(){
  auto inicio = std::chrono::high_resolution_clock::now();

  // 5 millones
  long long int acum = 0;
  const int max = 10000;
  for (int i = 0; i < max; i++){
    for (int j = 0; j < max; j++){
      acum += j + i;
    }
    
  }
  
  auto fin = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duracion = fin - inicio;
  double duracion_ms = duracion.count() * 1000.0;

  printf("Task Easy done in %fms\n", duracion_ms);
}

int Num(){
  return 555;
}

void Medium(){

  auto inicio = std::chrono::high_resolution_clock::now();

  const int range = 50000;
  // Calcular si un numero es primo (divisible solo entre el mismo y 1)
  for (int i = 0; i < range; i++){
    
    bool divisible = false;

    for(int j = 2; j < i; j++){
      // Es divisible entre un numero entre medias
      if(i % j == 0){
       divisible = true;
      }
    }
    //if(!divisible)printf("%d es primo\n",i);
  }

  auto fin = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duracion = fin - inicio;
  double duracion_ms = duracion.count() * 1000.0;

  printf("Task Medium done in %fms\n", duracion_ms);
  
}


int main(int argc, char *argv[]){
  JobSystem job;

  //Easy();
  std::function<void()> func1{Easy};
  std::function<void()> func2{Medium};
  

  std::future<int> future = job.add_task(Num);
  int return_num = future.get();



  printf("Num-> %d\n", return_num);

  for (int i = 0; i < 5; i++){
    job.add_task(func2);
    job.add_task(func1);
  }

  job.wait_until_finish();
  //job.add_task(Medium);



  // No hace las 30 porque llamo al destructor cuando aun siguen habiendo tareas en la cola
  return 0;
}