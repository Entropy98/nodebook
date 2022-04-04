/*
 * @file    status.h
 * @author  Harper Weigle
 * @date    4/3/2022
 * @brief   Contains Node class information
 */

#include <cstdint>

namespace utillib{

/*
 *  @brief  returns unique hash given data
 *  @param  data - pointer to data to create hash for
 *  @return hash for data 0 is *data=nullptr
 */
uint32_t getId(void* data);

}//utillib
