/*
 * @file    status.h
 * @author  Harper Weigle
 * @date    4/3/2022
 * @brief   Contains Node class information
 */
#ifndef INC_NODE_H
#define INC_NODE_H

#include "status.h"
#include "utils.h"
using namespace utillib;

namespace nodelib{

/*
 *  @brief  linked-list node for ConnectionHubs
 */
class Connection {
  public:
    Connection* next;
    void* node;
    Connection(){
      next = nullptr;
      node = nullptr;
    }
};

/*
 *  @brief  linked-list container for node connections
 */
class ConnectionHub {
  public:
    Connection* head;
    uint64_t size;
    ConnectionHub(){
      head = nullptr;
      size = 0;
    }

    /*
     *  @brief  adds a connection to the connection hub
     *  @param  node - node to add to the hub
     *  @return SUCCESS on successful operation
     */
    status_t addConnection(void* node);

    /*
     *  @brief  deletes a connection from the connection hub
     *  @param  my_id - id of the node deleting a connection
     *  @param  their_id - id of the node to delete
     *  @return SUCCESS on successful operation
     */
    status_t deleteConnection(uint32_t my_id, uint32_t their_id);
};

/*
 *  @brief  parent class for all nodes
 */
class Node {
  public:
    ConnectionHub* connections;
    void* data;
    uint32_t id;
    Node(){
      connections = new ConnectionHub();
      data = nullptr;
      id = getId(this);
    }
    virtual ~Node(){
      ConnectionHub hub = *connections;
      uint32_t conn_id;
      while(connections->head != nullptr){
        conn_id = ((Node*)(hub.head->node))->id;
        hub.deleteConnection(id, conn_id);
      }
      delete connections;
    }
    /*
     *  @brief  adds a connection to a node.
     *          If there were no connections, this.connections points
     *          to that connection.
     *          If there was already a connection, connections points
     *          to a list of pointers to connections
     *  @param  Node node - node to connect to
     *  @return SUCCESS on successful connection
     */
    status_t addConnection(Node* node);

    /*
     *  @brief  deletes connection to a node
     *  @param  uint32_t id - unique id of node to delete connection to
     *  @return SUCCESS on successful deletion
     */
    status_t deleteConnection(uint32_t id);

    /*
     *  @breif  forms connection between two nodes and breaks the
     *          connections between those nodes
     *  @param  uint32_t id1 - unique id for node1
     *  @param  uint32_t id2 - unique id for node2
     *  @return SUCCESS on successful operation
     */
    status_t injectConnection(uint32_t id1, uint32_t id2);

    virtual status_t store(uint32_t id) = 0;

    virtual status_t remove(uint32_t id) = 0;
};//Node

class LabelNode : public Node {
  public:
    LabelNode() : Node(){}
    /*
     *  @brief  Nothing This node is not meant to store data
     *  @param  uint32_t id - unique id for the data
     *  @return ERR_NODE_TYPE
     */
    status_t store(uint32_t id) override;

    /*
     *  @brief  Nothing This node is not meant to store data
     *  @param  uint32_t id - unique id for the data
     *  @return ERR_NODE_TYPE
     */
    status_t remove(uint32_t id) override;
};//LabelNode

}//nodelib

#endif //INC_NODE_H
