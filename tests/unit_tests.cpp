#include <iostream>
#include "node.h"
#include "unit_tests.h"
#include "utils.h"

using namespace std;
using namespace utillib;
using namespace nodelib;

status_t utilityTests(uint8_t* test_num){
  printf("Running Test %d: Utility Tests\n",*test_num);
  uint8_t val1 = 0;
  uint8_t val2 = 1;
  uint32_t id1 = getId(&val1);
  uint32_t id2 = getId(&val2);
  status_t result = SUCCESS;

  if(id1 == id2){
    printf("Test %d Failed: Objects returned identical hashes\n",*test_num);
    result = ERR_UNSPECIFIED;
  }
  test_num++;
  if(SUCCESS == result){
    id2 = getId(&val1);
    if(id1 != id2){
      printf("Test %d Failed: Same object has multiple hashes\n",*test_num);
      result = ERR_UNSPECIFIED;
    }
  }
  test_num++;
  return result;
}

status_t interactionTests(uint8_t* test_num){
  printf("Running Test %d: Interaction Tests\n",*test_num);
  LabelNode* node1 = new LabelNode();
  LabelNode* node2 = new LabelNode();
  status_t result = SUCCESS;
  uint32_t test_id = 0;

  result = node1->addConnection(node2);
  /*
   * Map: (1)<->(2)
   */
  if(result != SUCCESS){
    printf("Test %d Failed with code %d: Node1 returned bad status when connecting Node2\n",*test_num, result);
  }
  test_num++;

  if(SUCCESS == result){
    test_id = ((LabelNode*)(node1->connections->head->node))->id;
    printf("Connecting Node 1 to Node 2\n");
    if(test_id != node2->id){
      printf("Test %d Failed: Node1 Connection 1 ID should be %d but was %d\n",*test_num, node2->id, test_id);
      result = ERR_UNSPECIFIED;
    }
  }
  test_num++;

  if(SUCCESS == result){
    test_id = ((LabelNode*)(node2->connections->head->node))->id;
    if(test_id != node1->id){
      printf("Test %d Failed: Node2 Connection 1 ID should be %d but was %d\n",*test_num, node2->id, test_id);
      result = ERR_UNSPECIFIED;
    }
  }
  test_num++;

  if(SUCCESS == result){
    if(node1->connections->size != 1u){
      printf("Test %d Failed: Node1 reported a size of %ld. 1 was expected\n",*test_num,node1->connections->size);
      result = ERR_UNSPECIFIED;
    }
  }
  test_num++;

  if(node2->connections->size != 1u){
    printf("Test %d Failed: Node2 reported a size of %ld. 1 was expected\n",*test_num,node2->connections->size);
  }
  test_num++;

  LabelNode* node3 = new LabelNode();
  result = node1->addConnection(node3);
  /*
   * Map: (3)<->(1)<->(2)
   */
  if(result != SUCCESS){
    printf("Test %d Failed with code %d: Node1 returned bad status when connecting Node3\n",*test_num, result);
    return result;
  }
  test_num++;

  test_id = ((Node*)(node1->connections->head->next->node))->id;
  printf("Connecting Node 1 to Node 3\n");
  if(test_id != node3->id){
    printf("Test %d Failed: Node1 Connection 2 ID should be %d but was %d\n",*test_num, node3->id, test_id);
    return result;
  }
  test_num++;

  test_id = ((Node*)(node3->connections->head->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node3 Connection 1 ID should be %d but was %d\n",*test_num, node1->id, test_id);
    return result;
  }
  test_num++;

  if(node2->connections->size != 1u){
    printf("Test %d Failed: Node2 reported a size of %ld. 1 was expected\n",*test_num,node2->connections->size);
  }
  test_num++;

  if(node1->connections->size != 2u){
    printf("Test %d Failed: Node1 reported a size of %ld. 2 was expected\n",*test_num,node1->connections->size);
  }
  test_num++;

  if(node3->connections->size != 1u){
    printf("Test %d Failed: Node3 reported a size of %ld. 1 was expected\n",*test_num,node3->connections->size);
  }
  test_num++;

  printf("Disconnecting Node 2 from Node 1\n");
  result = node1->deleteConnection(node2->id);
  /*
   * Map: (3)<->(1)   (2)
   */
  if(result != SUCCESS){
    printf("Test %d Failed with code %d: Node1 returned bad status when disconnecting Node2\n",*test_num, result);
    return result;
  }
  test_num++;

  if(node2->connections->head != nullptr){
    printf("Test %d Failed: Node2 did not fully disconnect properly\n",*test_num);
    return result;
  }
  test_num++;

  test_id = ((Node*)(node1->connections->head->node))->id;
  if(test_id != node3->id){
    printf("Test %d Failed: Node1 Connection 1 ID should be %d but was %d\n",*test_num, node3->id, test_id);
    return result;
  }
  test_num++;

  test_id = ((Node*)(node3->connections->head->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node3 Connection 1 ID should be %d but was %d\n",*test_num, node1->id, test_id);
    return result;
  }
  test_num++;

  if(node2->connections->size != 0u){
    printf("Test %d Failed: Node2 reported a size of %ld. 0 was expected\n",*test_num,node2->connections->size);
  }
  test_num++;

  if(node1->connections->size != 1u){
    printf("Test %d Failed: Node1 reported a size of %ld. 1 was expected\n",*test_num,node1->connections->size);
  }
  test_num++;

  if(node3->connections->size != 1u){
    printf("Test %d Failed: Node3 reported a size of %ld. 1 was expected\n",*test_num,node3->connections->size);
  }
  test_num++;

  printf("Disconnecting Node 1 from Node 3\n");
  result = node3->deleteConnection(node1->id);
  /*
   * Map: (3)   (1)   (2)
   */
  if(result != SUCCESS){
    printf("Test %d Failed: Node3 returned bad status when disconnecting Node1\n",*test_num);
    return result;
  }
  test_num++;

  if(node1->connections->head != nullptr){
    printf("Test %d Failed: Node1 did not fully disconnect properly\n",*test_num);
    return result;
  }
  test_num++;

  if(node3->connections->head != nullptr){
    printf("Test %d Failed: Node3 did not fully disconnect properly\n",*test_num);
    return result;
  }
  test_num++;

  if(node2->connections->size != 0u){
    printf("Test %d Failed: Node2 reported a size of %ld. 0 was expected\n",*test_num,node2->connections->size);
  }
  test_num++;

  if(node1->connections->size != 0u){
    printf("Test %d Failed: Node1 reported a size of %ld. 0 was expected\n",*test_num,node1->connections->size);
  }
  test_num++;

  if(node3->connections->size != 0u){
    printf("Test %d Failed: Node3 reported a size of %ld. 0 was expected\n",*test_num,node3->connections->size);
  }
  test_num++;

  printf("Connecting Node 2 to Node 3\n");
  node2->addConnection(node3);
  /*
   * Map: (1)   (2)<->(3)
   */
  test_id = ((Node*)(node2->connections->head->node))->id;
  if(test_id != node3->id){
    printf("Test %d Failed: Node2 Connection 1 ID should be %d but was %d\n",*test_num, node3->id, test_id);
    return result;
  }
  test_num++;

  test_id = ((Node*)(node3->connections->head->node))->id;
  if(test_id != node2->id){
    printf("Test %d Failed: Node3 Connection 1 ID should be %d but was %d\n",*test_num, node2->id, test_id);
    return result;
  }
  test_num++;

  if(node2->connections->size != 1u){
    printf("Test %d Failed: Node2 reported a size of %ld. 1 was expected\n",*test_num,node2->connections->size);
  }
  test_num++;

  if(node1->connections->size != 0u){
    printf("Test %d Failed: Node1 reported a size of %ld. 0 was expected\n",*test_num,node1->connections->size);
  }
  test_num++;

  if(node3->connections->size != 1u){
    printf("Test %d Failed: Node3 reported a size of %ld. 1 was expected\n",*test_num,node3->connections->size);
  }
  test_num++;

  printf("Connecting Node 1 to Node 2\n");
  node2->addConnection(node1);
  /*
   * Map: (1)<->(2)<->(3)
   */
  test_id = ((Node*)(node2->connections->head->next->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node2 Connection 2 ID should be %d but was %d\n",*test_num, node1->id, test_id);
    return result;
  }
  test_num++;

  test_id = ((Node*)(node1->connections->head->node))->id;
  if(test_id != node2->id){
    printf("Test %d Failed: Node1 Connection 1 ID should be %d but was %d\n",*test_num, node2->id, test_id);
    return result;
  }
  test_num++;

  if(node2->connections->size != 2u){
    printf("Test %d Failed: Node2 reported a size of %ld. 2 was expected\n",*test_num,node2->connections->size);
  }
  test_num++;

  if(node1->connections->size != 1u){
    printf("Test %d Failed: Node1 reported a size of %ld. 1 was expected\n",*test_num,node1->connections->size);
  }
  test_num++;

  if(node3->connections->size != 1u){
    printf("Test %d Failed: Node3 reported a size of %ld. 1 was expected\n",*test_num,node3->connections->size);
  }
  test_num++;

  printf("Connecting Node 1 to Node 3\n");
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
    printf("Test %d Failed: Node2 Connection 2 ID should be %d but was %d\n",*test_num, node3->id, test_id);
    return result;
  }
  test_num++;

  test_id = ((Node*)(node3->connections->head->next->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node2 Connection 2 ID should be %d but was %d\n",*test_num, node1->id, test_id);
    return result;
  }
  test_num++;

  if(node2->connections->size != 2u){
    printf("Test %d Failed: Node2 reported a size of %ld. 2 was expected\n",*test_num,node2->connections->size);
  }
  test_num++;

  if(node1->connections->size != 2u){
    printf("Test %d Failed: Node1 reported a size of %ld. 2 was expected\n",*test_num,node1->connections->size);
  }
  test_num++;

  if(node3->connections->size != 2u){
    printf("Test %d Failed: Node3 reported a size of %ld. 2 was expected\n",*test_num,node3->connections->size);
  }
  test_num++;

  printf("Running Test %d: Deletion Tests\n",*test_num);
  printf("Deleting Node 2\n");
  delete node2;
  /*
   * Map: (1)<->(3)
   */
  if(node3->connections->head->next != nullptr){
    printf("Test %d Failed: Node2 did not fully disconnect properly\n",*test_num);
    return result;
  }
  *test_num++;

  if(node1->connections->head->next != nullptr){
    printf("Test %d Failed: Node2 did not fully disconnect properly\n",*test_num);
    return result;
  }
  *test_num++;

  test_id = ((Node*)(node3->connections->head->node))->id;
  if(test_id != node1->id){
    printf("Test %d Failed: Node3 Connection 1 ID should be %d but was %d\n",*test_num, node1->id, test_id);
    return result;
  }
  *test_num++;

  test_id = ((Node*)(node1->connections->head->node))->id;
  if(test_id != node3->id){
    printf("Test %d Failed: Node1 Connection 1 ID should be %d but was %d\n",*test_num, node3->id, test_id);
    return result;
  }
  *test_num++;

  printf("Deleting Node 1\n");
  delete node1;
  /*
   * Map: (3)
   */
  if(node3->connections->head != nullptr){
    printf("Test %d Failed: Node1 did not fully disconnect properly\n",*test_num);
    return result;
  }
  delete node3;
  *test_num++;

  return result;
}
