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
  return rand()%10000;
}

int NumRange(int range){
  printf("Num que recibe-> %d\n", range);
  return rand()%range;
}

double CalculePrim(int begining){
  auto inicio = std::chrono::high_resolution_clock::now();

  
  // Calcular si un numero es primo (divisible solo entre el mismo y 1)
  for (int i = begining; i < begining + 10000; i++){
    
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

  printf("Task prim in range %d to %d done in %fms\n",begining, begining + 10000, duracion_ms);
  return duracion_ms;
}

void Medium(){

  auto inicio = std::chrono::high_resolution_clock::now();

  const int range = 10000;
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

  //printf("Task Medium done in %fms\n", duracion_ms);
  
}





int main(int argc, char *argv[]){
  srand(time(NULL));
  JobSystem job;

  //Easy();
  //std::function<void()> func1{Easy};
  //std::function<void()> func2{Medium};
  /*
  {
    auto inicio = std::chrono::high_resolution_clock::now();
    CalculePrim(0);
    CalculePrim(10000);
    CalculePrim(20000);
    CalculePrim(30000);
    CalculePrim(40000);
    CalculePrim(50000);
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    double duracion_ms = duracion.count() * 1000.0;

    printf("Duration prims in range 0 - 60.000 single thread done in %f\n", duracion_ms);
  }

  {
    auto inicio = std::chrono::high_resolution_clock::now();
    double duration = 0.0f;
    job.add_task(CalculePrim, 0);
    job.add_task(CalculePrim,10000);
    job.add_task(CalculePrim,20000);
    job.add_task(CalculePrim,30000);
    job.add_task(CalculePrim,40000);
    job.add_task(CalculePrim,50000);
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    double duracion_ms = duracion.count() * 1000.0;

    printf("Duration prims in range 0 - 60.000 multithreading done in %f\n", duracion_ms);
  }
  */






  for (int i = 0; i < 0; i++){

    job.add_task(Easy);
    job.add_task(Medium);
    std::future<int> future = job.add_task(Num);
    int return_num = future.get();
    //printf("Num-> %d\n", return_num);
    
    std::future<int> futureRange = job.add_task(NumRange, 5);
    int return_num_range = futureRange.get();
    //printf("Num con range-> %d\n", return_num_range);
  }


  auto inicio = std::chrono::high_resolution_clock::now();

  for(int i = 0; i < 1000; i++){
    Medium();
  }
  
  
  auto fin = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duracion = fin - inicio;
  double duracion_ms = duracion.count() * 1000.0;

  printf("Duration single thread: %f\n", duracion_ms);


  
  inicio = std::chrono::high_resolution_clock::now();

  for(int i = 0; i < 1000; i++){
    job.add_task(Medium);
  }
  job.wait_until_finish();
  
  fin = std::chrono::high_resolution_clock::now();
  duracion = fin - inicio;
  duracion_ms = duracion.count() * 1000.0;

  printf("Duration multi thread: %f\n", duracion_ms);
  //job.add_task(Medium);



  // No hace las 30 porque llamo al destructor cuando aun siguen habiendo tareas en la cola
  return 0;
}