#include <iostream>
#include "unit_tests.h"

int main(){
  uint8_t test_num = 0;
  status_t status;

  status = utilityTests(&test_num);
  if(SUCCESS == status){
    status = interactionTests(&test_num);
  }

  if(SUCCESS != status){
    printf("Test %d Failed with status: %d\n",test_num, status);
  }
  else{
    printf("All tests passed successfully!\n");
  }
  return status;
}
