//
//  hashTable.hpp
//  hw2
//
//  Created by Jake Close on 1/23/18.
//  Copyright © 2018 Jake Close. All rights reserved.
//

#pragma once

#include <string>
#include <stdio.h>
#include <cassert>
#include <cmath>
#include "../Vector/Vector.h"

template<typename K, typename V>
class Node
	{
public:

	Node(K key_in, V val_in) : key(key_in), val(val_in), next(nullptr)
		{ }

	Node(K key_in) : key(key_in), val(V()), next(nullptr)
		{ }

	~Node()
		{ }

	K key;
	Node<K, V> *next;
	V val;
	};


//Implementation of a Hash Table
template<typename K, typename V>
class HashTable
	{
private:

	Vector<Node<K, V> *> array;

	size_t sizeVector;
	int numElements;
	int numBuckets;

	const double LOAD_FACTOR = 0.5;


	//(djb2) hash function
	int hash(K key)
		{
		long long hash = 5381;
		int c;

		for (int i = 0; i < key.size( ); ++i)
			{
			c = key[ i ];
			hash = (( hash << 5 ) + hash ) + c; /* hash * 33 + c */

			}


		return llabs( hash ) % ( int ) sizeVector;
		}

	void rehash( ) {
		if (this->exceedsLoadFactor()) {
			Vector<Node<K, V> *> *newArray = new Vector<Node<K, V> *>;
			sizeVector *= 2;
			newArray->resize(sizeVector);
			numBuckets = 0;

			for (auto bucket : array) {
				//used to delete old linked list
				auto iterBucket = bucket;
				while (iterBucket != nullptr) {
					Node<K, V> *newNode = new Node<K, V>(iterBucket->key);
					newNode->val = iterBucket->val;

					int rehash = hash(iterBucket->key);
					//if collision
					if (newArray->at(rehash) != nullptr) {
						auto current = newArray->at(rehash);
						while (current->next != nullptr) {
							current = current->next;
						}
						current->next = newNode;
					} else {
						numBuckets++;
						newArray->at(rehash) = newNode;
					}
					iterBucket = iterBucket->next;
					//Delete linked list
					while (bucket != nullptr) {
						auto next = bucket->next;
						delete bucket;
						bucket = next;
					}
				}
				array = *newArray;
			}
		}
	}

	bool exceedsLoadFactor()
		{
		return ((double) this->numElements / (double) this->sizeVector >= LOAD_FACTOR);
		}

public:

	HashTable()
		{
		numElements = 0;
		numBuckets = 0;
		sizeVector = 16;
		array.resize(sizeVector);
		}

	HashTable ( const HashTable & copy )
		{
		this->numElements = copy.numElements;
		this->numBuckets = copy.numBuckets;
		this->sizeVector = copy.sizeVector;
		array.resize ( sizeVector );
		int size = sizeof ( array );

		for ( size_t i = 0; i < sizeVector; ++i )
			{
			auto iter = copy.array[ i ];
			while ( iter != nullptr )
				{
				this->operator [] ( iter->key ) = iter->val;
				iter = iter->next;
				}
			}
		}


	V &operator[](const K &key)
	{
		if (this->exceedsLoadFactor( ))
			this->rehash();
		//return seek( key )->val;
		Node<K, V> *value = find( key );
		if ( value == nullptr )
			value = insert(key);

		return value->val;

	}

	Node<K, V> *insert(K key)
		{

		if ( this->exceedsLoadFactor( ) )
			this->rehash( );

		int hash_val = hash( key );
		Node<K, V> *current = array[ hash_val ];
		if ( !current )
			{
			array[ hash_val ] = new Node<K, V>( key );
			current = array[ hash_val ];
			++numBuckets;
			++numElements;
			return current;
			}

		while ( current->next != nullptr && current->key != key )
			{
			current = current->next;
			}

		if ( current->key == key )
			{
			return current;
			}


		numBuckets++;
		//gets to end of chain, creates new element
		current->next = new Node<K, V>( key );
		numElements++;
		return current->next;
		}

	/*
	 * Returns Pointer to Node if found at Key
	 * Otherwise node pointer
	 */
	Node<K, V> *find( K key )
		{
		int hash_val = hash( key );
		Node<K, V> *current = array[ hash_val ];

		while ( current != nullptr && current->key != key )
			current = current->next;

		return current;

		}

	//returns the number of keys
	int size()
		{
		return numElements;
		}

	//returns the size of the underlying array
	int capacity()
		{
		return sizeVector;
		}

	int buckets()
		{
		return numBuckets;
		}

};


