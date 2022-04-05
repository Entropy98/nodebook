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
  SUCCESS,
  ERR_OUT_OF_MEMORY,
  ERR_BAD_PTR,
  ERR_NODE_TYPE,
  ERR_NO_ID,
  ERR_NODE_NOT_FOUND,
}status_t;

#endif //INC_STATUS_H
