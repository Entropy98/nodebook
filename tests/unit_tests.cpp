#include <iostream>
#include "utils.h"

using namespace std;
using namespace utillib;

int main(){
  uint8_t test_num = 0;
  printf("Running Test %d: Utility Tests\n",test_num);
  uint8_t val1 = 0;
  uint8_t val2 = 1;
  uint32_t id1 = getId(&val1);
  uint32_t id2 = getId(&val2);
  if(id1 == id2){
    printf("Test %d Failed: Objects returned identical hashes\n",test_num);
    return test_num;
  }

  printf("All Tests Passed\n");
  return 0;
}
