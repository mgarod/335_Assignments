/***************************************************************
Title:        LeftistNode.h
Author:       Michael Garod
Date Created: 11/15/2015
Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:    Ioannis Stamos
Purpose:      Assignment #4
Description:  Node to be used for the Mutable Priority Queue. Functionality
              was added for parent pointers. This struct was removed from
              within the LeftistHeap.h in order to better interact with the
              Hash Table and PQPair classes.
Note:         This code was primarily taken from Data Structures and
              Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
              http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/
***************************************************************/
#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <iostream>
using namespace std;

template <typename Comparable>
struct LeftistNode
    {
        Comparable   element;
        LeftistNode<Comparable>* left;
        LeftistNode<Comparable>* right;
        LeftistNode<Comparable>* parent;
        int          npl;

        LeftistNode( const Comparable & e, LeftistNode<Comparable> *lt = nullptr, LeftistNode<Comparable> *rt = nullptr, LeftistNode<Comparable> *p = nullptr, int np = 0 )
          : element{ e }, left{ lt }, right{ rt }, parent{ p }, npl{ np }
          { }
        
        LeftistNode( Comparable && e, LeftistNode<Comparable> *lt = nullptr, LeftistNode<Comparable> *rt = nullptr, LeftistNode<Comparable> *p = nullptr, int np = 0 )
          : element{ std::move( e ) }, left{ lt }, right{ rt }, parent{ p }, npl{ np }
          { }
    };

#endif