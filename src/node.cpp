/*
 * @file    node.cpp
 * @author  Harper Weigle
 * @date    4/3/2022
 * @brief   Contains Node class information
 */

namespace nodelib{

status_t ConnectionHub::addConnection(Node* node){
  conn = new Connection();
  conn.node = (void*)node;
  if(this.head == nullptr){
    this.head = (void*)&conn;
  }
  else{
    void* ptr = this.head;
    while(ptr->next != nullptr){
      ptr = ptr->next;
    }
    ptr->next = (void*)&conn;
  }
  this.size++;
  return SUCCESS;
}

status_t ConnectionHub::deleteConnection(uint32_t id){
  status_t status;
  if(this.head == nullptr){
    status = ERR_NODE_NOT_FOUND;
  }
  else{
    void* ptr = this.head;
    void* prev_ptr = nullptr;
    while(ptr->next != nullptr){
      if(ptr->node->id == id){
        prev_ptr->next = ptr->next;
        delete *ptr;
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
  status_t status;
  if(node == nullptr){
    status = ERR_BAD_PTR;
  }
  else{
    status = this.connections::addConnection(node);
    if(status == SUCCESS){
      status = node->connections::addConnection(&this);
    }
    if(status != SUCCESS){
      status = this.connections::deleteConnection(node->id);
    }
  }
  return status;
}

status_t Node::deleteConnection(uint32_t id){
  status_t status;
  if(id == 0){
    status == ERR_NO_ID;
  }
  else{
    status = this.connections.deleteConnection(id);
  }
  return status;
}

}//nodelib
