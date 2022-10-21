/*
 * @file    status.h
 * @author  Harper Weigle
 * @date    4/3/2022
 * @brief   Contains Node class information
 */
#ifndef INC_STATUS_H
#define INC_STATUS_H

#include <cstdint>

typedef enum{
  SUCCESS             = 0,
  ERR_OUT_OF_MEMORY   = 1,
  ERR_BAD_PTR         = 2,
  ERR_NODE_TYPE       = 3,
  ERR_NO_ID           = 4,
  ERR_NODE_NOT_FOUND  = 5,
  ERR_ID_CHANGE       = 6,
  ERR_UNSPECIFIED     = 99,
}status_t;

#endif //INC_STATUS_H
