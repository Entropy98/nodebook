/*
 * @file    utils.cpp
 * @author  Harper Weigle
 * @date    4/3/2022
 * @brief   Contains utility functions
 */
#include "status.h"
#include "utils.h"

using namespace utillib;

uint32_t utillib::getId(void* data){
  uint32_t hash = 0;
  if(data != nullptr){
    void** dataptr = &data;//no hash function yet so just returning a chunked addr
    hash = *((uint32_t*)dataptr);
  }
  return hash;
}
