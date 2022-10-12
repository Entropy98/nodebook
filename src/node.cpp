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

status_t ConnectionHub::deleteConnection(uint32_t my_id, uint32_t their_id){
  bool found = false;
  Connection* prev_ptr = nullptr;
  Connection* ptr = this->head;
  status_t recip_del_status = SUCCESS;
  status_t status = SUCCESS;

  if(this->head == nullptr){
    status = ERR_NODE_NOT_FOUND;
  }

  if(status == SUCCESS){

    while(ptr->next != nullptr){
      if(((Node*)ptr->node)->id == their_id){
        found = true;
        break;
      }
      prev_ptr = ptr;
      ptr = ptr->next;
    }

    if(found == true){
      prev_ptr = ptr->next;
      this->head = prev_ptr;
      recip_del_status = ((Node*)ptr->node)->connections->deleteConnection(((Node*)ptr->node)->id, my_id);
      if(recip_del_status != ERR_NODE_NOT_FOUND){
        status = //TODO create new status for changing IDs or smthn
      }
    }
    else{
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

  if(status == SUCCESS){
    status = this->connections->addConnection(node);
    if(status == SUCCESS){
      status = node->connections->addConnection(this);
      if(status != SUCCESS){
        status = this->connections->deleteConnection(this->id, node->id);
      }
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
    status = this->connections->deleteConnection(this->id, id);
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
