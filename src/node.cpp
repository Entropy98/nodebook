/*
 * @file    node.cpp
 * @author  Harper Weigle
 * @date    10/11/2022
 * @brief   Contains Node class information
 */
#include "node.h"
#include "status.h"

namespace nodelib{

status_t ConnectionHub::addConnection(void* node){
  Connection* conn = new Connection();
  conn->node = node;
  if(this->head == nullptr){
    this->head = conn;
  }
  else{
    Connection* ptr = this->head;
    while(ptr->next != nullptr){
      ptr = ptr->next;
    }
    ptr->next = conn;
  }
  this->size++;
  return SUCCESS;
}

status_t ConnectionHub::deleteConnection(uint32_t id){
  status_t status = SUCCESS;
  if(this->head == nullptr){
    status = ERR_NODE_NOT_FOUND;
  }
  else{
    Connection* ptr = this->head;
    Connection* prev_ptr = nullptr;
    while(ptr->next != nullptr){
      if(((Node*)ptr->node)->id == id){
        prev_ptr->next = ptr->next;
        delete ptr;
        status = SUCCESS;
        break;
      }
      ptr = ptr->next;
      prev_ptr = ptr;
      status = ERR_NODE_NOT_FOUND;
    }
  }
  return status;
}

status_t Node::addConnection(Node* node){
  status_t status = SUCCESS;
  if(node == nullptr){
    status = ERR_BAD_PTR;
  }
  else{
    status = this->connections->addConnection(node);
    if(status == SUCCESS){
      status = node->connections->addConnection(this);
    }
    if(status != SUCCESS){
      status = this->connections->deleteConnection(node->id);
    }
  }
  return status;
}

status_t Node::deleteConnection(uint32_t id){
  status_t status = SUCCESS;
  if(id == 0){
    status = ERR_NO_ID;
  }
  else{
    status = this->connections->deleteConnection(id);
  }
  return status;
}

status_t LabelNode::store(uint32_t id){
  return SUCCESS;
}

status_t LabelNode::remove(uint32_t id){
  return SUCCESS;
}

}//nodelib
