//
// Created by Zane Dunnings on 1/25/18.
//

#pragma once

#include <iostream>

template< typename T >
class Vector
{
public:
    Vector( );
    Vector( size_t size );
    ~Vector( );
    size_t size( );
    const T & operator [] ( size_t loc ) const;
    T &operator[ ]( size_t index );
    Vector& operator=( const Vector &rhs);
    T &at( size_t index);
    void push_back( T );
    void reserve( size_t );
    void resize( size_t size );

    class Iterator
    {
    public:
        Iterator()
                :currentIndex( nullptr ){ }
        Iterator( T* inputIndex )
                :currentIndex( inputIndex ){ }

        T &operator*(  )
        {

            return *currentIndex;

        }

        Iterator &operator++( )
        {
            ++this->currentIndex;
            return *this;
        }

        Iterator &operator--( )
        {
            --this->currentIndex;
            return *this;
        }

        bool operator==( const Iterator &rhs ) const
        {
            return this->currentIndex == rhs.currentIndex;
        }

        bool operator!=(const Iterator &rhs) const
        {
            return this->currentIndex != rhs.currentIndex;
        }

    private:

        T* currentIndex;
        friend class Vector;
    };

    Iterator begin( )
    {
        if( this->start == nullptr )
        {
            return  Iterator( );
        }
        return Iterator( this->start );
    }

    Iterator end( )
    {

        return Iterator( &start[ numberOfItems ] );
    }

private:

    //points to the beginning of the array
    T* start;
    //the number of objects in the array and its "size" to the user
    size_t totalSize;
    //the actual size of the array in memory
    size_t numberOfItems;
    //The standard starting size of the array
    const size_t defaultSize;

};

template< typename T>
///Default constructor array size is 16
Vector<T>::Vector(): defaultSize(16)
{
    this->start = new T[ this->defaultSize ];
    this->totalSize = defaultSize;
    this->numberOfItems = 0;
}

template< typename T>
/// creates an Vector thats 'size' big
Vector<T>::Vector( size_t size ): defaultSize( size )
{
    this->start = new T[ this->defaultSize ];
    this->totalSize = defaultSize;
    this->numberOfItems = 0;
}

template< typename T>
/// Destructor deletes the array
/// \tparam T
Vector<T>::~Vector()
{
    delete [ ] this->start;
}

template< typename T>
/// \tparam T
/// \param item : item to be pushed to the back of the array
void Vector<T>::push_back(T item)
{
    //extend the size of the array cuz you dont have enough space
    if( ( this->numberOfItems + 1 ) >= this->totalSize )
        this->reserve( totalSize * 2);

    this->start[ this->numberOfItems ] = item;
    ++this->numberOfItems;
}

template< typename T>
/// \tparam T
/// \param loc : index to be accessed
/// \return : reference to the index, arr[ loc ]
T &Vector<T>::operator[ ]( size_t loc)
{
    return this->start[ loc ];
}


template< typename T >
/// \tparam T
/// \param loc : index to be accessed
/// \return : reference to the index, arr[ loc ]
const T & Vector< T >::operator [] ( size_t loc ) const
{
    return this->start[ loc ];
}


template< typename T>
/// \tparam T
/// \param loc : index to be accessed
/// \return : reference to the index, arr[ loc ]
T &Vector<T>::at( size_t loc)
{
    if( loc >= this->totalSize )
    {
        std::cerr << "Index out of Range";
        exit(1);
    }
    else
    {
        return this->start[ loc ];
    }
}

template< typename T>
/// \tparam T
/// \return the amount of elements in the array
size_t Vector<T>::size() {
    return this->numberOfItems;
}

template< typename T>
/// Reserves the space by allocating 'size' amount of containers, but doesn't change the number of objects,
/// or give default values
/// \tparam T
/// \param size : new size of the arr
void Vector<T>::reserve( size_t size )
{
    if( size < this->numberOfItems )
    {
        std::cerr << "Vector.reserve( size ) :: 'size' must be larger than the previous size of the array\n";
        exit(1);
    }
    totalSize = size;
    T* newArr = new T[totalSize];

    for( int i = 0; i < numberOfItems ; ++i )
    {
        newArr[ i ] = this->start[ i ];
    }
    delete [ ] this->start;
    this->start = newArr;
}

template< typename T>
/// Will resize the array to be 'size', and fill the new spots with default values. Can access these,
/// and push_back will push to arr[ size ]
/// \tparam T
/// \param size : new size of the arr
void Vector<T>::resize( size_t size )
{
    if( size < this->numberOfItems )
    {
        std::cerr << "Vector.reserve( size ) :: 'size' must be larger than the previous size of the array\n";
        exit( 1 );
    }

    this->totalSize  = size;
    T* newArr = new T[ this->totalSize ];

    for( int i = 0; i < this->numberOfItems; ++i )
    {
        newArr[ i ] = this->start[ i ];
    }

    for( int i = this->numberOfItems; i < size; ++i )
    {
        newArr[ i ] = T( );
    }

    this->numberOfItems = size;
    delete [ ] this->start;
    this->start = newArr;
}

template< typename T>
///Default constructor array size is 16
Vector<T>& Vector<T>::operator=( const Vector<T> &copy )
{
    delete[] start;
    this->numberOfItems = copy.numberOfItems;
    this->totalSize = copy.totalSize;
    this->start = new T[ this->totalSize ];

    for(int i = 0; i < totalSize; ++i)
    {
        this->start[ i ] = copy.start[ i ];
    }

    return *this;
}