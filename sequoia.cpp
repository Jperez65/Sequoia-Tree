#include "sequoia.h"

//Returns a pointer to the first node in this subtree containing x
//Returns null pointer if it can't find x
SequoiaNode* SequoiaNode::search(int x)
{
  if (x == value)
    return this;
  else if (x < value && left != nullptr)
    return left->search(x);
  else if (x > value && right != nullptr)
    return right->search(x);
  else
    return nullptr;  
}

//Inserts a new node into this Sequoia
//Updates root if necessary
//Does *not* update height or ensure tallness
void Sequoia::insert(int x)
{
  if (root != nullptr)
    root->insert(x);
  else
    root = new SequoiaNode(x);
  size++;

  while (root->parent != nullptr)
    root = root->parent;
}

//Removes a node from this Sequoia
//Updates root if necessary
//No effect if the tree doesn't contain the given value
//Does *not* update height or enforce tallness
void Sequoia::remove(int x)
{
  if (root == nullptr)
    return;
  SequoiaNode* victim = root->search(x);
  if (victim == nullptr)
    return;
  else
  {
    if (victim == root)
      if (root->left != nullptr)
        root = root->left;
      else
        root = root->right;
    victim = victim->remove();
    delete victim;
  }
}

//Basic BST insertion function
//Does *not* update height or ensure tallness
void SequoiaNode::insert(int x)
{
  if (x < value)
  {
    if (left != nullptr)
      left->insert(x);
    else
    {
      left = new SequoiaNode(x);
      left->parent = this;
      updateheight(this);
    }
  }
  else
  {
    if (right != nullptr)
      right->insert(x);
    else
    {
      right = new SequoiaNode(x);
      right->parent = this;
      updateheight(this);
    }
  }
}

// Function will update the height of the tree 
// by going up the root until reaching the top
//Its start from the parent node on the recently inserted node
void SequoiaNode::updateheight(SequoiaNode* cur)
{
  if(cur == nullptr)   //Function will stop when it hits the root of the parent which is a nullptr
      return;

  else if(cur->right != nullptr && cur->left !=nullptr) 
  {
    if( (cur->left->height) >= (cur->right->height) && (cur->left->height < 2*cur->right->height) ) //test for case 1 
      fixBalanceInsert(cur->right, true);

    else if( !(cur->left->height >= cur->right->height*2 ) && !(cur->right->height >= 2*cur->left->height) )  //test for case 2
      fixBalanceInsert(cur->left, false);

    else if(cur->right->height==cur->height || cur->left->height==cur->height)
      cur->height++;    //check if either children heigt is the same as the parent.

    else return; 
  } 
  else if(cur->right == nullptr || cur->left ==nullptr )
    verifyHeight(cur);  //Statement that would check the height again and adjust it accordingly

  updateheight(cur->parent);
}

//Basic BST removal function
//Does *not* update height or ensure tallness
//Returns pointer to the node removed (2 child case)
//Sets children to null but does not delete node
//(see Sequoia::remove(x))
SequoiaNode* SequoiaNode::remove()
{
  if (left == nullptr && right == nullptr)
  {
    if (parent != nullptr)
    {
      if (parent->left == this)
        parent->left = nullptr;  
      else                        
        parent->right = nullptr;
      updateheightRemoval(parent);
    }

  }
  else if (left != nullptr && right == nullptr)
  {
    left->parent = parent;
    if (parent->left == this)  
      parent->left = left;  
    else                      
      parent->right = left;
    updateheightRemoval(parent);
  }
  else if (left == nullptr && right != nullptr)
  {
    right->parent = parent;
    if (parent->left == this)   //Same as previous section but test if left side of the node is a null
      parent->left = right;
    else
      parent->right = right;
    updateheightRemoval(parent);
  }
  else
  {
    SequoiaNode* swap = left;   //test when both left and right node exist
    int temp = value;
    while (swap->right != nullptr)
      swap = swap->right;
    value = swap->value;
    swap->value = temp;
    return swap->remove();
  }
  left = right = nullptr;
  return this;  
}

// Function for updating the nodes of a Sequoia
// following an insertion to maintain "tallness"
// Not called in driver, so not required to be implemented
// If not implementing, must fix height and tallness elsewhere
void SequoiaNode::fixBalanceInsert(SequoiaNode* pivot, bool flag)
{
  if(flag) //flag is true for case 1 scenario
  {
    pivot->parent->height= pivot->parent->left->height + 1;
    pivot->height=pivot->parent->height;
    pivot->rotateleft();
  }
  else //else case 2 is true
  { 
    pivot->parent->height= pivot->parent->right->height + 1;
    pivot->height=pivot->parent->height;
    pivot->rotateright();
  }
}

//Function that test height of it current node to its children
void SequoiaNode::verifyHeight( SequoiaNode* cur)
{
  if(cur->left != nullptr && cur->right != nullptr)
  {
    if(cur->left->height >= cur->right->height)
      cur->height=cur->left->height+1;
    else
      cur->height=cur->right->height+1;
  }
  else if(cur->left != nullptr && cur->right == nullptr)
    cur->height=cur->left->height+1;
  else if(cur->left == nullptr && cur->right != nullptr)
    cur->height=cur->right->height+1;

  return;
}

//Function that follow standard BSt rotation to the left
void SequoiaNode::rotateleft()
{
  parent->right = left;
  if (left != nullptr)
    left->parent = parent;
  this->left = parent;
  if (parent->parent != nullptr)
  {
    if (parent == parent->parent->left)
      parent->parent->left = this;
    else
      parent->parent->right = this;
  }
  SequoiaNode* gp = parent->parent;
  parent->parent = this;
  this->parent = gp;

}

//Function that would follow a standard BST rotation to the right
void SequoiaNode::rotateright()
{
  parent->left = right;
  if (right != nullptr)
    right->parent = parent;
  this->right = parent;
  if (parent->parent != nullptr)
  {
    if (parent == parent->parent->left)
      parent->parent->left = this;
    else
      parent->parent->right = this;
  }
  SequoiaNode* gp = parent->parent;
  parent->parent = this;
  this->parent = gp;

}

//Function that will update the height of the tree when 
//deleting a node.  The function would start on 
//the parent node from the deleted node.
void SequoiaNode::updateheightRemoval(SequoiaNode* cur)
{
  if(cur == nullptr)   //Base case to stop the recursion
      return;

  else if(cur->right == nullptr && cur->left == nullptr)  //if its a leaf node it would subtract one corresponding after the deletion
    cur->height--;     
  
  else if(cur->right != nullptr && cur->left != nullptr)  //When it hits a node that has two children it would check first if the height is right 
  {                                                       //then start testing both test cases to fix its tallness
    if(cur->right->height > cur->left->height)
      cur->height= cur->right->height+1;
    else
      cur->height= cur->left->height+1;
      
    if( (cur->left->height) >= (cur->right->height) && (cur->left->height < 2*cur->right->height) )//test for Case 1
        fixBalanceRemove(cur->right, true);

    else if(  !(cur->left->height >= cur->right->height*2 ) && !(cur->right->height >= 2*cur->left->height) ) //test for Case 2
        fixBalanceRemove(cur->left, false);
  }
  else   //whe its hit a node that has a single child it would 
  {    
    if(cur->right == nullptr)
      cur->height= cur->left->height+1;
    else
      cur->height= cur->right->height+1;
  }

  verifyHeight(cur);  //Checks again to verify if the Height of the node is correct or not

  updateheightRemoval(cur->parent); //recursive call
}

// Function for adjusting the height of a Sequoia
// following a deletion to maintain "tallness"
// takes in the pivot node and a boolean to flag if it Case#1 (True)
//or Case#2 (False)
void SequoiaNode::fixBalanceRemove(SequoiaNode* pivot, bool flag)
{
  if(flag) //flag is true for case 1 scenario
  {
    pivot->parent->height= pivot->parent->left->height + 1;
    pivot->height=pivot->parent->height;
    pivot->rotateleft();
  }
  else //else case 2 is true
  { 
    pivot->parent->height= pivot->parent->right->height + 1;
    pivot->height=pivot->parent->height;
    pivot->rotateright();
  }
}

