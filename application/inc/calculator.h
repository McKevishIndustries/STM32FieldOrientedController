//
// Created by Kevin McElligott on 29/01/2025.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdint.h>

uint64_t factorial(uint32_t value){
  if(value >= 1){
    return value * factorial(value - 1);
  }
  else{
    return 1;
  }
}

#endif //CALCULATOR_H
