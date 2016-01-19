# MasterBinarySearchTree
Data Structures master binary search tree project 
This project is a program in C which builds a review-score list based on the user’s reviews collected from WWW. 
These reviews are in some basic categories according to the scores they have.
This program will let the user add, remove, list the review-score list.


In the program I kept the score entries in a binary search tree by their score number. 
Then, to keep the reviews of each score, I create a binary search tree in which the reviews are kept 
by their id s (e.g., if I have five scores in your binary search tree, I will have five more binary search trees: 
one for the review list of each score.). 
I define binary search tree such that for a node, smaller valued items are kept in the left 
subtree of the node and greater or equal valued items are kept in its right subtree.

FUNCTIONALITIES

1. Add a new score node into the master-BST .  
2. Add also some reviews into a specific review-score category. 
3. Show the average score of all of the reviews. 
4. List the id s of reviews which have a particular word.
5. Remove the reviews between in a specific score-scope. 
6. Display the tree.
