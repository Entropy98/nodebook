#include <iostream>
#include "node.h"
#include "status.h"
#include "utils.h"

using namespace std;
using namespace utillib;
using namespace nodelib;

int main(){
  uint8_t test_num = 0;
  status_t status;
  printf("Running Test %d: Utility Tests\n",test_num);
  uint8_t val1 = 0;
  uint8_t val2 = 1;
  uint32_t id1 = getId(&val1);
  uint32_t id2 = getId(&val2);
  if(id1 == id2){
    printf("Test %d Failed: Objects returned identical hashes\n",test_num);
    return test_num;
  }
  id2 = getId(&val1);
  if(id1 != id2){
    printf("Test %d Failed: Same object has multiple hashes\n",test_num);
    return test_num;
  }
  test_num++;

  printf("Running Test %d: Interaction Tests\n",test_num);
  LabelNode* node1 = new LabelNode();
  LabelNode* node2 = new LabelNode();
  status = node1->addConnection(node2);
  /*
   * Map: (1)<->(2)
   */
  if(status != SUCCESS){
    printf("Test %d Failed: Node1 returned bad status when connecting Node2\n",test_num);
    return test_num;
  }
  uint32_t test_id = ((Node*)(node1->connections->head->node))->id;
  printf("Connecting Node 1 to Node 2");
  if(test_id != node2->id){
    printf("Test %d Failed: Node1 Connection 1 ID should be %d but was %d\n",test_num, node2->id, test_id);
    return test_num;
  }
  test_id = ((Node*)(node2->connections->head->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node2 Connection 1 ID should be %d but was %d\n",test_num, node2->id, test_id);
    return test_num;
  }
  LabelNode* node3 = new LabelNode();
  status = node1->addConnection(node3);
  /*
   * Map: (3)<->(1)<->(2)
   */
  if(status != SUCCESS){
    printf("Test %d Failed: Node1 returned bad status when connecting Node3\n",test_num);
    return test_num;
  }
  test_id = ((Node*)(node1->connections->head->next->node))->id;
  printf("Connecting Node 1 to Node 3");
  if(test_id != node3->id){
    printf("Test %d Failed: Node1 Connection 2 ID should be %d but was %d\n",test_num, node3->id, test_id);
    return test_num;
  }
  test_id = ((Node*)(node3->connections->head->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node3 Connection 1 ID should be %d but was %d\n",test_num, node1->id, test_id);
    return test_num;
  }
  printf("Disconnecting Node 2 from Node 1");
  status = node1->deleteConnection(node2->id);
  /*
   * Map: (3)<->(1)   (2)
   */
  if(status != SUCCESS){
    printf("Test %d Failed: Node1 returned bad status when disconnecting Node2\n",test_num);
    return test_num;
  }
  if(node2->connections->head != nullptr){
    printf("Test %d Failed: Node2 did not fully disconnect properly\n",test_num);
    return test_num;
  }
  test_id = ((Node*)(node1->connections->head->node))->id;
  if(test_id != node3->id){
    printf("Test %d Failed: Node1 Connection 1 ID should be %d but was %d\n",test_num, node3->id, test_id);
    return test_num;
  }
  test_id = ((Node*)(node3->connections->head->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node3 Connection 1 ID should be %d but was %d\n",test_num, node1->id, test_id);
    return test_num;
  }
  printf("Disconnecting Node 1 from Node 3");
  status = node3->deleteConnection(node1->id);
  /*
   * Map: (3)   (1)   (2)
   */
  if(status != SUCCESS){
    printf("Test %d Failed: Node3 returned bad status when disconnecting Node1\n",test_num);
    return test_num;
  }
  if(node1->connections->head != nullptr){
    printf("Test %d Failed: Node1 did not fully disconnect properly\n",test_num);
    return test_num;
  }
  if(node3->connections->head != nullptr){
    printf("Test %d Failed: Node3 did not fully disconnect properly\n",test_num);
    return test_num;
  }
  printf("Connecting Node 2 to Node 3");
  node2->addConnection(node3);
  /*
   * Map: (1)   (2)<->(3)
   */
  test_id = ((Node*)(node2->connections->head->node))->id;
  if(test_id != node3->id){
    printf("Test %d Failed: Node2 Connection 1 ID should be %d but was %d\n",test_num, node3->id, test_id);
    return test_num;
  }
  test_id = ((Node*)(node3->connections->head->node))->id;
  if(test_id != node2->id){
    printf("Test %d Failed: Node3 Connection 1 ID should be %d but was %d\n",test_num, node2->id, test_id);
    return test_num;
  }
  printf("Connecting Node 1 to Node 2");
  node2->addConnection(node1);
  /*
   * Map: (1)<->(2)<->(3)
   */
  test_id = ((Node*)(node2->connections->head->next->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node2 Connection 2 ID should be %d but was %d\n",test_num, node1->id, test_id);
    return test_num;
  }
  test_id = ((Node*)(node1->connections->head->node))->id;
  if(test_id != node2->id){
    printf("Test %d Failed: Node1 Connection 1 ID should be %d but was %d\n",test_num, node2->id, test_id);
    return test_num;
  }
  printf("Connecting Node 1 to Node 3");
  node3->addConnection(node1);
  /*
   * Map: (2)<->(3)
   *       ^     ^
   *        \   /
   *         v v
   *         (1)
   */
  test_id = ((Node*)(node1->connections->head->next->node))->id;
  if(test_id != node3->id){
    printf("Test %d Failed: Node2 Connection 2 ID should be %d but was %d\n",test_num, node3->id, test_id);
    return test_num;
  }
  test_id = ((Node*)(node3->connections->head->next->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node2 Connection 2 ID should be %d but was %d\n",test_num, node1->id, test_id);
    return test_num;
  }
  test_num++;

  printf("Running Test %d: Deletion Tests\n",test_num);
  printf("Deleteing Node 2");
  delete node2;
  /*
   * Map: (1)<->(3)
   */
  if(node3->connections->head->next != nullptr){
    printf("Test %d Failed: Node2 did not fully disconnect properly\n",test_num);
    return test_num;
  }
  if(node1->connections->head->next != nullptr){
    printf("Test %d Failed: Node2 did not fully disconnect properly\n",test_num);
    return test_num;
  }
  test_id = ((Node*)(node3->connections->head->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node3 Connection 1 ID should be %d but was %d\n",test_num, node1->id, test_id);
    return test_num;
  }
  test_id = ((Node*)(node1->connections->head->node))->id;
  if(test_id != node3->id){
    printf("Test %d Failed: Node1 Connection 1 ID should be %d but was %d\n",test_num, node3->id, test_id);
    return test_num;
  }
  printf("Deleteing Node 1");
  delete node1;
  /*
   * Map: (3)
   */
  if(node3->connections->head != nullptr){
    printf("Test %d Failed: Node1 did not fully disconnect properly\n",test_num);
    return test_num;
  }

  printf("All Tests Passed\n");
  return 0;
}
