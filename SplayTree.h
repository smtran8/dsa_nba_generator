//
// Created by cladu on 3/25/2026.
//
#pragma once
#include <iostream>
#include <vector>
#include "classes_and_functions.h"
#include <unordered_map>


//Create a Splay tree class
struct Node {
    //initalize the Node's attributes
    //FOR NOW, USE A BASIC DATA TO COMPARE
    Node* left;
    Node* right;
    Node* parent;
    float player_grade;

    //each node will store a player object
    Player thePlayer;

    //create function for the Node
    //constructor
    Node(Player& thisPlayer, Node* theParent) {
        //makeing testNum equal to the grade of the player, to making comparing easier
        thePlayer = thisPlayer;
        left = nullptr;
        right = nullptr;
        parent = theParent;
        player_grade = thePlayer.grade;
    }

};

struct SplayTree {

    //the splay tree will be composed of nodes, so it's needs a nested Node struct


    //the only attriubte the splay tree has is the root
    Node* theRoot;

    SplayTree() {
        theRoot = nullptr;
    }



    //need logic for splaying nodes up to the root
    //either we need to zig, zig zig, or zig zag

    //we use zig to rotate the Node up
    Node* Zig(Node* theNode) {
        Node* oldParent = theNode->parent;
        //see if current node is a left or right kid
        if (oldParent->left == theNode) {
            //it's on the left, so rotate right

            //we have to rotate the pointer (similar to AVL rotate)
            Node* grandparent = oldParent->parent;
            Node* grandchild = theNode->right;
            oldParent->left = grandchild;

            //update the parent if necssaary
            if (grandchild != nullptr) {
                grandchild->parent = oldParent;
            }


            //update the parent pointers
            theNode->right = oldParent;
            oldParent->parent = theNode;

            theNode->parent = grandparent;

            //check if the current node is now the root
            if (grandparent == nullptr) {
                theRoot = theNode;
            }
            else {
                //this means the grandparent wasn't the root,
                //and we have to make sure the tree stays connected
                //check which sid the old parent was on
                if (grandparent->left == oldParent) {
                    //attach it to the coorect side of the tree
                    grandparent->left = theNode;
                }
                else
                    grandparent->right = theNode;

            }


        }
        else {
            //it's on the right, so rotate left

            //we have to rotate the pointer (similar to AVL rotate)
            Node* grandparent = oldParent->parent;
            Node* grandchild = theNode->left;
            oldParent->right = grandchild;

            //update the parent if necssaary
            if (grandchild != nullptr) {
                grandchild->parent = oldParent;
            }

            //update the parent pointers
            theNode->left = oldParent;
            oldParent->parent = theNode;

            theNode->parent = grandparent;

            //check if the current node is now the root
            if (grandparent == nullptr) {
                theRoot = theNode;
            }
            else {
                //this means the grandparent wasn't the root,
                //and we have to make sure the tree stays connected
                //check which sid the old parent was on
                if (grandparent->right == oldParent) {
                    //attach it to the coorect side of the tree
                    grandparent->right = theNode;
                }
                else
                    grandparent->left = theNode;

            }
        }
        return theNode;

    }

    //we uses zig zag to rotate the the node up, as well as its parent up
    //so the node ends up being th new parent of old parent, and grandparent is the child of old parent
    Node* ZigZig(Node* theNode) {

        Node* oldParent = theNode->parent;
        Node* grandparent = oldParent->parent;

        //check if there's a grandparent, it not we can't do muitplie rotations
        if (grandparent == nullptr) {
            return theNode;
        }

        // we need to zig the old parent first, then zig the current node
        Zig(oldParent);
        Zig(theNode);

        return theNode;

    }

    //whne the parent and curr node on opposite sides, we're gonna rotate the curent
    //node up twice
    Node* ZigZag(Node* theNode) {

        Node* oldParent = theNode->parent;
        Node* grandparent = oldParent->parent;

        //check if there's a grandparent, it not we can't do muitplie rotations
        if (grandparent == nullptr) {
            return theNode;
        }

        //we're gonna zig up the current node twice. once with its parent, then again with the og grandparent
        Zig(theNode);
        Zig(theNode);

        return theNode;
    }



    //splay  function
    Node* Splay(Node* theNode) {

        while (theNode != theRoot) {

            //check if the node has grandparent, if not do a zig
            if (theNode->parent == nullptr) {
                break;
            }
            if (theNode->parent->parent == nullptr) {
                //USE A ZIG

                Zig(theNode);
            }
            //now we have to chekc if the nodes are on the same side
            //we use the parent pointers to work around the tree and check
            //if true, we needs a zig zig
            else if ((theNode->parent->left == theNode && theNode->parent->parent->left == theNode->parent) || (theNode->parent->right == theNode && theNode->parent->parent->right == theNode->parent)) {
                //USE A ZIG ZIG
                ZigZig(theNode);
            }
            //if not on the same side, we need a zig zag
            else {
                //USE A ZAG
                ZigZag(theNode);
            }

        }
        theRoot = theNode;
        return theNode;

    }

    //for this project, we will only need the insert and search methods
    //all of these are the same as a BST, but must splay accordiningly

    //create a helper for insert
    Node* inserHelper(Node* root, Player& thePlayer) {

        if (root == nullptr) {
            return new Node(thePlayer, nullptr);
            //return temp;
        }
        if (thePlayer.grade < root->player_grade) {
            if (root->left == nullptr) {
                root->left = new Node(thePlayer, root);
                return root->left;
            }
            return inserHelper(root->left, thePlayer);
        }
        else {
            if (root->right == nullptr) {
                root->right = new Node(thePlayer, root);
                return root->right;
            }
        }

        return inserHelper(root->right, thePlayer);

    }

    //insert
    void insert(Player& currentPlayer) {
        //check if the tree is empty
        if (theRoot == nullptr) {
            theRoot = new Node(currentPlayer, nullptr);
            return;
        }

        //call the helper
        Node* temp = inserHelper(theRoot, currentPlayer);

        //splay the node adn assign it to the root
        theRoot = Splay(temp);

    }



    //search for a splay tree is the same logic as a BST, just with splaying at the end
    Node* search(Node* root, float num) {

        //if the tree is empty
        if (root == nullptr) {
            return nullptr;
        }
        //if we found the id
        else if (num == root->player_grade) {
            //since we found it, splay it up in the tree
            theRoot = Splay(root);
            //now return the node
            return theRoot;
        }
        //if the id is less than
        else if (num < root->player_grade) {
            return search(root->left, num);
        }
        //if the id is greater than
        else {
            return search(root->right, num);
        }
    }


    //postorder traversal helper function for the destructor
    void postOrderHelper(Node* theNode) {

        if (theNode == nullptr) {
            return;
        }
        else {
            postOrderHelper(theNode->left);
            postOrderHelper(theNode->right);
            delete theNode;
        }

    }


    //Destructor for the tree, using post order traveslar, as we need to go through the dree and delte each node
    ~SplayTree() {

        //call the helper function
        postOrderHelper(theRoot);
        theRoot = nullptr;
    }



    public:
    //create a function to add the players to the tree, using the insert function
    void playersIntoTree(vector<Player>& players) {

        //use a for loop to insert each player into a node for the tree
        for (auto p : players) {
            insert(p);
        }



    }

    //this function will go through the rightside of the tree to return the pkayer with highest grade
    Player findHighestGrade() {

        Node* temp = theRoot;
        while (temp->right != nullptr) {
            temp = temp->right;
        }

        return temp->thePlayer;
    }



};

TeamResult getTheTeam(const vector<Player> &all_players, string team_code);