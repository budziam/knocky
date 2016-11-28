#define MAX_NODES 100

typedef struct Node {
  uint32_t millis;
  int x;
  int y;
  int z;
  Node* previousNode;
  Node* nextNode;
} Node;

Node *firstNode;
Node *lastNode;
int nodesCount = 0;

void knockDetectorPushValues(uint32_t millis, int x, int y, int z)
{
  createAndPushNode(millis, x, y, z);
  
  seekKnock();
}

/**
 * Seek knock basing on nodes
 */
void seekKnock()
{
  
}

void createAndPushNode(uint32_t millis, int x, int y, int z)
{
  Node *node = (Node*)malloc(sizeof(Node));
  node->millis = millis;
  node->x = x;
  node->y = y;
  node->z = z;
  node->nextNode = NULL;
  node->previousNode = lastNode;
  
  lastNode->nextNode = node;
  
  lastNode = node;
  
  nodesCount += 1;
  if (nodesCount > MAX_NODES) {
    removeFirstNode();
  }
}

void removeFirstNode()
{
  Node *newFirstNode = firstNode->nextNode;
  free(firstNode);
  
  newFirstNode->previousNode = NULL;
  firstNode = newFirstNode;
  
  nodesCount -= 0;
}
