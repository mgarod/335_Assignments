/***************************************************************
Title:        MutablePQ.h
Author:       Michael Garod
Date Created: 11/15/2015
Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:    Ioannis Stamos
Purpose:      Assignment #4
Description:  MutablePQ is based on LeftistHeap.h taken from Weiss.
              Modifications include the addition of parent pointers, and the
              ability to query any item in MutablePQ (though you cannot
              directly manipulate the entry) and the ability to remove any
              item in the MutablePQ.
Note:         This code was primarily taken from Data Structures and
              Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
              http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/
***************************************************************/
#ifndef MUTABLEPQ_H
#define MUTABLEPQ_H

#include "dsexceptions.h"
#include <iostream>
#include "LeftistNode.h"
#include "QuadraticProbing.h"
#include "PQPair.h"
using namespace std;

// Leftist heap class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class MutablePQ
{
  public:
    /**
    * A simple testing method to print the entire tree
    */    
    void preOrderTraversal(){
        preOrderHelper(root);
    }

    /**
    * A simple testing method to print every active entry in the table
    * See QuadraticProbing.h to view definition of hash_table.printall()
    */
    void printhash(){
        if(!isEmpty())
            hash_table.printall();
        else
            cout << "Heap is Empty\n";
    }

    MutablePQ( ) : root{ nullptr }
      { }
    MutablePQ( const MutablePQ & rhs ) : root{ nullptr }
      { root = clone( rhs.root ); }
    
    MutablePQ( MutablePQ && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~MutablePQ( )
      { makeEmpty( ); }
    
    /**
     * Deep copy.
     */
    MutablePQ & operator=( const MutablePQ & rhs )
    {
        MutablePQ copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    MutablePQ & operator=( MutablePQ && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Returns true if empty, false otherwise.
     */
    bool isEmpty( ) const
      { return root == nullptr; }
    
    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return root->element;
    }

    /**
     * Inserts x; duplicates NOT allowed.
     */
    void insert( const Comparable & x )
	{
		LeftistNode<Comparable>* insert = new LeftistNode<Comparable>{ x };
        PQPair<Comparable, LeftistNode<Comparable>*> pqp(x, insert);

        if(hash_table.insert(std::move(pqp))) {
            root = merge( insert , root );
            root->parent = nullptr;
        }
        else{
            cout << "Cannot insert " << x << ", already in queue\n";
        }
	}

    /**
     * Inserts x; duplicates NOT allowed.
     */
    void insert( Comparable && x )
    {
        LeftistNode<Comparable>* insert = new LeftistNode<Comparable>{ x };
        PQPair<Comparable, LeftistNode<Comparable>*> pqp(x, insert);
        
        if(hash_table.insert(std::move(pqp))){
            root = merge( new LeftistNode<Comparable>{ std::move( x ) },root );
            root->parent = nullptr;
        }
        else{
            cout << "Cannot insert " << x << ", already in queue\n";
        }
    }

    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException{ };

        // Set HashEntry to Deleted
        PQPair<Comparable, LeftistNode<Comparable>*> pqp( findMin() );
        hash_table.remove(pqp);

        LeftistNode<Comparable> *oldRoot = root;
        root = merge( root->left, root->right );
        // Handle the new root's parent
        if(root != nullptr){
            root->parent = nullptr;
        }
        delete oldRoot;
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        minItem = findMin( );
        deleteMin( );
    }

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( )
    {
        reclaimMemory( root );
        root = nullptr;
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     */
    void merge( MutablePQ & rhs )
    {
        if( this == &rhs )    // Avoid aliasing problems
            return;

        root = merge( root, rhs.root );
        rhs.root = nullptr;
    }

    /**
     * Find any comparable in the heap by checking the hash table.
     */
    bool Find( const Comparable& x )
    {
        // Make a trivial PQPair <x, nullptr> since hash only works with 
        //  PQpairs and the pointer is not used for the hash or search
        PQPair<Comparable, LeftistNode<Comparable>*> pqp(x);

        if (hash_table.contains( pqp ))
            return true;
        else
            return false;
    }

    /**
    * Delete any entry in the heap by using the hash table for access.
    *  Note that this is in-place removal, instead of percolating up and then
    *  using deleteMin(). In-place removal can destroy the leftist heap
    *  property. See restoreAncestors() for restoration of the heap property.
    */
    bool Remove( const Comparable& x )
    {
        // If the item was never in the hash, return false
        // This is the only time that remove can ever fail
        if(hash_table.isEmpty( x )){
            return false;
        }

        // If the item has already been deleted, then return true
        if(hash_table.isDeleted( x )){
            return true;
        }
        
        // Get reference to the PQPair (containing x) in the hash.
        PQPair<Comparable, LeftistNode<Comparable>*> pqp;
        pqp = hash_table.Find( x );

        // Special Case: When you ask to delete the item which is the minimum
        //  This prevents messing around with the parent of the root (nullptr)
        if(root->element == (pqp.ptr)->element){
            deleteMin();
        }
        // Begin In-Place Remove Routine
        else{
            // Easy access aliases/synonyms
            auto &ptr = (pqp.ptr);
            auto &ptrparent = ptr->parent;

            // Are we deleting a left child or a right child?
            if( ptrparent->left == ptr ){
                ptrparent->left = merge( ptr->left, ptr->right );
                if( ptrparent->left != nullptr)
                    (ptrparent->left)->parent = ptrparent;
            }
            else{
                ptrparent->right = merge( ptr->left, ptr->right );
                if( ptrparent->right != nullptr)
                    (ptrparent->right)->parent = ptrparent;
            }
            
            // The node is now disconneted. Delete the node.
            // This also handles entries of the hash since ptr == pqp.ptr
            delete ptr;
            ptr = nullptr;

            // Set HashEntry DELETED
            hash_table.remove(pqp);

            // Correct any imbalanced NPLs, the only nodes affected will be
            // those along the ancestral path to the root
            restoreAncestors(ptrparent);
        }// END ELSE

        return true;
    }

    /**
    * Returns the number of edges connecting the right most vertices.
    * (|V| on the rightmost path minus 1 = |E| on the rightmost path)
    */
    int RightMostPath(){
        int counter = 0;
        for(auto currptr = root; currptr->right != nullptr; currptr = currptr->right)
        {
            ++counter;
        }
        return counter;
    }

  private:

    LeftistNode<Comparable> *root;
    HashTable<PQPair<Comparable, LeftistNode<Comparable>*>> hash_table;

    /**
     * Internal method to merge two roots.
     * Deals with deviant cases and calls recursive merge1.
     */
    LeftistNode<Comparable>* merge( LeftistNode<Comparable>* h1, LeftistNode<Comparable>* h2 )
    {
        if( h1 == nullptr )
            return h2;
        if( h2 == nullptr )
            return h1;
        if( h1->element < h2->element )
            return merge1( h1, h2 );
        else
            return merge1( h2, h1 );
    }

    /**
     * Internal method to merge two roots.
     * Assumes trees are not empty, and h1's root contains smallest item.
     */
    LeftistNode<Comparable>* merge1( LeftistNode<Comparable>* h1, LeftistNode<Comparable>* h2 )
    {
        if( h1->left == nullptr )   // Single node
        {
            h1->left = h2;       // Other fields in h1 already accurate
            
            // Added to implement parent pointer
            h2->parent = h1;
        }
        else
        {
            h1->right = merge( h1->right, h2 );

            // Added to implement parent pointer
            (h1->right)->parent = h1;

            if( h1->left->npl < h1->right->npl )
                swapChildren( h1 );
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }

    /**
     * Swaps t's two children.
     */
    void swapChildren( LeftistNode<Comparable>* t )
    {
        LeftistNode<Comparable>* tmp = t->left;
        t->left = t->right;
        t->right = tmp;
    }

    /**
     * Internal method to make the tree empty.
     * WARNING: This is prone to running out of stack space;
     *          exercises suggest a solution.
     */
    void reclaimMemory( LeftistNode<Comparable>* t )
    {
        if( t != nullptr )
        {
            reclaimMemory( t->left );
            reclaimMemory( t->right );
            delete t;
        }
    }
    
    /**
     * Internal method to clone subtree.
     * WARNING: This is prone to running out of stack space.
     *          exercises suggest a solution.
     */
    LeftistNode<Comparable>* clone( LeftistNode<Comparable>* t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new LeftistNode<Comparable>{ t->element, clone( t->left ), clone( t->right ), t->npl };
    }

    /**
    * Helper to the public function preOrderTraversal()
    */
    void preOrderHelper(LeftistNode<Comparable>* node){
        
        cout << node->element << endl;

        // Print NPL
        cout << "\tnpl: " << node->npl << endl;
        
        // Print left
        if(node->left != nullptr)
            cout << "\tleft: " << node->left->element << endl;
        else
            cout << "\tleft: --" << endl;

        // Print right
        if(node->right != nullptr)
            cout << "\tright: " << node->right->element << endl;
        else
            cout << "\tright: --" << endl;

        // Print parent
        if(node->parent != nullptr)
            cout << "\tparent: " << node->parent->element << endl;
        else
            cout << "\tparent: --" << endl;
        
        if(node->left != nullptr)
            preOrderHelper(node->left);
        if(node->right != nullptr)
            preOrderHelper(node->right);
    }

    /**
    * Restore the heap property that can be destroyed by in-place removal.
    */
    void restoreAncestors(LeftistNode<Comparable>* ptr){

        for( ; ptr != nullptr; ptr = ptr->parent){
            if ( (ptr->left == nullptr) ||
                 (ptr->right == nullptr) ){
                ptr->npl = 0;
            }
            else if ( ptr->left->npl < ptr->right->npl ){
                swapChildren( ptr );
                ptr->npl = ptr->right->npl + 1;
            }
            else{ // left child npl >= right child npl
                // do nothing since leftist heap property has not been violated
            }
        }
    }
};

#endif