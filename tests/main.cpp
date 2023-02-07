#include "unit_tests.h"

int main(){
  uint8_t test_num = 0;
  status_t status;

  status = utilityTests(&test_num);
  if(SUCCESS == status){
    status = interactionTests(&test_num);
  }

  printf("Test %d Failed with status: \n",*test_num, status);
  return status;
}
