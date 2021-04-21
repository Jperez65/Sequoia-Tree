# Database Project 2: Sequoia Tree  Author:Josue Perez

## Objective
The main objective for this project will be to create a BST tree that extends its branches lengths. In this case, the bst is will imitate a sequoia tree branch by having the highest length branch.

## Overview
The project contains two classes: *sequioa and sequioaNode*. The sequoia class represent the tree that contains functions that will alter the shape of of it with highest branch. While sequoiaNode represent a single node leaf in the bst and its functions dictate wether or not the branch is at the highest length.

## Compiling 
This program is compile with c

>

## Sequoia Class Functions 

### insert()
/Inserts a new node into this Sequoia. Updates root if necessary. Does *not* update height or ensure tallness

### remove()
Removes a node from this Sequoia. Updates root if necessary. No effect if the tree doesn't contain the given value. Does *not* update height or enforce tallness

## SequoiaNode Class Functions

### search(int x)
Function recurse through the tree to find a specific node. Returns a pointer to the first node in this subtree containing x. Returns null pointer if it can't find x

### insert(int x)
Basic BST insertion function. however it does *not* update height or ensure tallness

### updateheight(SequoiaNode* cur)
Function will update the height of the tree by going up the root until reaching the top. Its start from the parent node on the recently inserted node

### remove()
Basic BST removal function. Does *not* update height or ensure tallness. Returns pointer to the node removed (2 child case). Sets children to null but does not delete node

### fixBalanceInsert(SequoiaNode* pivot, bool flag)
Function for updating the nodes of a Sequoia. following an insertion to maintain "tallness"

### verifyHeight( SequoiaNode* cur)
Function that test height of it current node to its children

### rotateleft()
Function that follow standard BSt rotation to the left.

### rotateright()
Function that would follow a standard BST rotation to the right.

### updateheightRemoval(SequoiaNode* cur)
Function that will update the height of the tree when deleting a node.  The function would start on the parent node from the deleted node.

### fixBalanceRemove(SequoiaNode* pivot, bool flag)
Function for adjusting the height of a Sequoia following a deletion to maintain "tallness" takes in the pivot node and a boolean to flag if it Case#1 (True) or Case#2 (False)
>