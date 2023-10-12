#include <stdio.h>
#include <iostream>
#include "JobSystem.h"


void Easy(){

  printf("yeeeee");
  // 5 millones
  const int max = 5;
  for(int i = 0; i < max; i++){
    std::cout << " num: " << i;
  }
}


void Medium(){

  const int max = 128;
  
  char caracteres[max];

  for (int i = 0; i < max; ++i) {
    caracteres[i] = static_cast<char>(i);
  }

  for(int i = 0 ; i < max; i++){
    std::cout << "char = " << caracteres[i];
  }
}


int main(){

  JobSystem job;

  //Easy();
  //job.add_task(Easy);
  //job.add_task(Medium);

  return 0;
}