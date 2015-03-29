<a href='Hidden comment: =====================================================================================
#
#  Wiki page for vector operations
#
#  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the Blaze library. You can redistribute it and/or modify it under
#  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
#  forms, with or without modification, are permitted provided that the following conditions
#  are met:
#
#  1. Redistributions of source code must retain the above copyright notice, this list of
#     conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright notice, this list
#     of conditions and the following disclaimer in the documentation and/or other materials
#     provided with the distribution.
#  3. Neither the names of the Blaze development group nor the names of its contributors
#     may be used to endorse or promote products derived from this software without specific
#     prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
#  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
#  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
#  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
#  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
#  DAMAGE.
#
#==================================================================================='></a>


## Constructors ##

Instantiating and setting up a vector is very easy and intuitive. However, there are a few rules to take care of:

  * In case the last template parameter (the transpose flag) is omitted, the vector is per default a column vector.
  * The elements of a `StaticVector` or `HybridVector` are default initialized (i.e. built-in data types are initialized to 0, class types are initialized via the default constructor).
  * Newly allocated elements of a `DynamicVector` or `CompressedVector` remain uninitialized if they are of built-in type and are default constructed if they are of class type.


#### Default Construction ####

```
using blaze::StaticVector;
using blaze::DynamicVector;
using blaze::CompressedVector;

// All vectors can be default constructed. Whereas the size of StaticVectors is fixed via the second template
// parameter, the initial size of a default constructed DynamicVector or CompressedVector is 0.
StaticVector<int,2UL> v1;                // Instantiation of a 2D integer column vector.
                                         // All elements are initialized to 0.
StaticVector<long,3UL,columnVector> v2;  // Instantiation of a 3D long integer column vector.
                                         // Again, all elements are initialized to 0L.
DynamicVector<float> v3;                 // Instantiation of a dynamic single precision column
                                         // vector of size 0.
DynamicVector<double,rowVector> v4;      // Instantiation of a dynamic double precision row
                                         // vector of size 0.
CompressedVector<int> v5;                // Instantiation of a compressed integer column
                                         // vector of size 0.
CompressedVector<double,rowVector> v6;   // Instantiation of a compressed double precision row
                                         // vector of size 0.
```


#### Construction with Specific Size ####

The `DynamicVector`, `HybridVector` and `CompressedVector` classes offer a constructor that allows to immediately give the vector the required size. Whereas both dense vectors (i.e. `DynamicVector` and `HybridVector`) use this information to allocate memory for all vector elements, `CompressedVector` merely acquires the size but remains empty.

```
DynamicVector<int,columnVector> v7( 9UL );      // Instantiation of an integer dynamic column vector
                                                // of size 9. The elements are NOT initialized!
HybridVector< complex<float>, 5UL > v8( 2UL );  // Instantiation of a column vector with two single precision
                                                // complex values. The elements are default constructed.
CompressedVector<int,rowVector> v9( 10UL );     // Instantiation of a compressed row vector with size 10.
                                                // Initially, the vector provides no capacity for non-zero elements.
```


#### Initialization Constructors ####

All dense vector classes offer a constructor that allows for a direct, homogeneous initialization of all vector elements. In contrast, for sparse vectors the predicted number of non-zero elements can be specified:

```
StaticVector<int,3UL,rowVector> v10( 2 );            // Instantiation of a 3D integer row vector.
                                                     // All elements are initialized to 2.
DynamicVector<float> v11( 3UL, 7.0F );               // Instantiation of a dynamic single precision column vector
                                                     // of size 3. All elements are set to 7.0F.
CompressedVector<float,rowVector> v12( 15UL, 3UL );  // Instantiation of a single precision column vector of size 15,
                                                     // which provides enough space for at least 3 non-zero elements.
```

The `StaticVector` class offers a special initialization constructor. For `StaticVectors` of up to 6 elements (i.e. 6D vectors) the vector elements can be individually specified in the constructor:

```
using blaze::StaticVector;

StaticVector<int,1UL> v13( 4 );
StaticVector<long,2UL> v14( 1L, -2L );
StaticVector<float,3UL,columnVector> v15( -0.1F, 4.2F, -7.1F );
StaticVector<double,4UL,rowVector> v16( 1.3, -0.4, 8.3, -1.2 );
StaticVector<size_t,5UL> v17( 3UL, 4UL, 1UL, 9UL, 4UL );
StaticVector<long,6UL> v18( 1L, 3L, -2L, 9L, 4L, -3L );
```


#### Array Construction ####

Alternatively, all dense vector classes offer a constructor for an initialization with a dynamic or static array. If the vector is initialized from a dynamic array, the constructor expects the actual size of the array as first argument, the array as second argument. In case of a static array, the fixed size of the array is used:

```
const double array1* = new double[2];
// ... Initialization of the dynamic array

float array2[4] = { 1.0F, 2.0F, 3.0F, 4.0F };

blaze::StaticVector<double,2UL> v1( 2UL, array1 );
blaze::DynamicVector<float>     v2( array2 );

delete[] array1;
```


#### Copy Construction ####

All dense and sparse vectors can be created as the copy of any other dense or sparse vector with the same transpose flag (i.e. `blaze::rowVector` or `blaze::columnVector`).

```
 StaticVector<int,9UL,columnVector> v19( v7 );  // Instantiation of the dense column vector v19
                                                // as copy of the dense column vector v7.
DynamicVector<int,rowVector> v20( v9 );         // Instantiation of the dense row vector v20 as
                                                // copy of the sparse row vector v9.
CompressedVector<int,columnVector> v21( v1 );   // Instantiation of the sparse column vector v21
                                                // as copy of the dense column vector v1.
CompressedVector<float,rowVector> v22( v12 );   // Instantiation of the sparse row vector v22 as
                                                // copy of the row vector v12.
```

Note that it is not possible to create a `StaticVector` as a copy of a vector with a different size:

```
StaticVector<int,5UL,columnVector> v23( v7 );  // Runtime error: Size does not match!
StaticVector<int,4UL,rowVector> v24( v10 );    // Compile time error: Size does not match!

```





---

## Assignment ##

There are several types of assignment to dense and sparse vectors: Homogeneous Assignment, Array Assignment, Copy Assignment, and Compound Assignment.


#### Homogeneous Assignment ####

Sometimes it may be necessary to assign the same value to all elements of a dense vector. For this purpose, the assignment operator can be used:

```
blaze::StaticVector<int,3UL> v1;
blaze::DynamicVector<double> v2;

// Setting all integer elements of the StaticVector to 2
v1 = 2;

// Setting all double precision elements of the DynamicVector to 5.0
v2 = 5.0;
```


#### Array Assignment ####

Dense vectors can also be assigned a static array:

```
blaze::StaticVector<float,2UL> v1;
blaze::DynamicVector<double,rowVector> v2;

float array1[2] = { 1.0F, 2.0F };
double array2[5] = { 2.1, 4.0, -1.7, 8.6, -7.2 };

v1 = array1;
v2 = array2;
```


#### Copy Assignment ####

For all vector types it is generally possible to assign another vector with the same transpose flag (i.e. blaze::columnVector or blaze::rowVector). Note that in case of StaticVectors, the assigned vector is required to have the same size as the StaticVector since the size of a StaticVector cannot be adapted!

```
blaze::StaticVector<int,3UL,columnVector> v1;
blaze::DynamicVector<int,columnVector> v2( 3UL );
blaze::DynamicVector<float,columnVector> v3( 5UL );
blaze::CompressedVector<int,columnVector> v4( 3UL );
blaze::CompressedVector<float,rowVector> v5( 3UL );

// ... Initialization of the vectors

v1 = v2;  // OK: Assignment of a 3D dense column vector to another 3D dense column vector
v1 = v4;  // OK: Assignment of a 3D sparse column vector to a 3D dense column vector
v1 = v3;  // Runtime error: Cannot assign a 5D vector to a 3D static vector
v1 = v5;  // Compilation error: Cannot assign a row vector to a column vector
```


#### Compound Assignment ####

Next to plain assignment, it is also possible to use addition assignment, subtraction assignment, and multiplication assignment. Note however, that in contrast to plain assignment the size and the transpose flag of the vectors has be to equal in order to able to perform a compound assignment.

```
blaze::StaticVector<int,5UL,columnVector> v1;
blaze::DynamicVector<int,columnVector> v2( 5UL );
blaze::CompressedVector<float,columnVector> v3( 7UL );
blaze::DynamicVector<float,rowVector> v4( 7UL );
blaze::CompressedVector<float,rowVector> v5( 7UL );

// ... Initialization of the vectors

v1 += v2;  // OK: Addition assignment between two column vectors of the same size
v1 += v3;  // Runtime error: No compound assignment between vectors of different size
v1 -= v4;  // Compilation error: No compound assignment between vectors of different transpose flag
v4 *= v5;  // OK: Multiplication assignment between two row vectors of the same size
```





---

## Element Access ##

The easiest and most intuitive way to access a dense or sparse vector is via the subscript operator. The indices to access a vector are zero-based:

```
blaze::DynamicVector<int> v1( 5UL );
v1[0] = 1;
v1[1] = 3;
// ...

blaze::CompressedVector<float> v2( 5UL );
v2[2] = 7.3F;
v2[4] = -1.4F;
```

Whereas using the subscript operator on a dense vector only accesses the already existing element, accessing an element of a sparse vector via the subscript operator potentially inserts the element into the vector and may therefore be more expensive. Consider the following example:

```
blaze::CompressedVector<int> v1( 10UL );

for( size_t i=0UL; i<v1.size(); ++i ) {
   ... = v1[i];  // Inserts the element at index i
}
```

Although the compressed vector is only used for read access within the for loop, using the subscript operator temporarily inserts 10 non-zero elements into the vector. Therefore, all vectors (sparse as well as dense) offer an alternate way via the `begin()`, `cbegin()`, `end()`, and `cend()` functions to traverse the currently contained elements by iterators. In case of non-const vectors, `begin()` and `end()` return an `Iterator`, which allows a manipulation of the non-zero value, in case of a constant vector or in case `cbegin()` or `cend()` are used a `ConstIterator` is returned:

```
using blaze::CompressedVector;

CompressedVector<int> v1( 10UL );

// ... Initialization of the vector

// Traversing the vector via Iterator
for( CompressedVector<int>::Iterator it=v1.begin(); it!=v1.end(); ++it ) {
   it->value() = ...;  // OK: Write access to the value of the non-zero element.
   ... = it->value();  // OK: Read access to the value of the non-zero element.
   it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
   ... = it->index();  // OK: Read access to the index of the non-zero element.
}

// Traversing the vector via ConstIterator
for( CompressedVector<int>::ConstIterator it=v1.cbegin(); it!=v1.cend(); ++it ) {
   it->value() = ...;  // Compilation error: Assignment to the value via a ConstIterator is invalid.
   ... = it->value();  // OK: Read access to the value of the non-zero element.
   it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
   ... = it->index();  // OK: Read access to the index of the non-zero element.
}
```

Note that `begin()`, `cbegin()`, `end()`, and `cend()` are also available as free functions:

```
for( CompressedVector<int>::Iterator it=begin( v1 ); it!=end( v1 ); ++it ) {
   // ...
}

for( CompressedVector<int>::ConstIterator it=cbegin( v1 ); it!=cend( v1 ); ++it ) {
   // ...
}
```





---

## Element Insertion ##

In contrast to dense vectors, that store all elements independent of their value and that offer direct access to all elements, spares vectors only store the non-zero elements contained in the vector. Therefore it is necessary to explicitly add elements to the vector. The first option to add elements to a sparse vector is the subscript operator:

```
using blaze::CompressedVector;

CompressedVector<int> v1( 3UL );
v1[1] = 2;
```

In case the element at the given index is not yet contained in the vector, it is automatically inserted. Otherwise the old value is replaced by the new value 2. The operator returns a reference to the sparse vector element.

An alternative is the `set()` function: In case the element is not yet contained in the vector the element is inserted, else the element's value is modified:

```
// Insert or modify the value at index 3
v1.set( 3, 1 );
```

However, insertion of elements can be better controlled via the `insert()` function. In contrast to the subscript operator and the `set()` function it emits an exception in case the element is already contained in the matrix. In order to check for this case, the `find()` function can be used:

```
// In case the element at index 4 is not yet contained in the matrix it is inserted with a value of 6.
if( v1.find( 4 ) == v1.end() )
   v1.insert( 4, 6 );
```

Although the `insert()` function is very flexible, due to performance reasons it is not suited for the setup of large sparse vectors. A very efficient, yet also very low-level way to fill a sparse vector is the `append()` function. It requires the sparse vector to provide enough capacity to insert a new element. Additionally, the index of the new element must be larger than the index of the previous element. Violating these conditions results in undefined behavior!

```
v1.reserve( 5 );     // Reserving space for 5 non-zero elements
v1.append( 5, -2 );  // Appending the element -2 at index 5
v1.append( 6, 4 );   // Appending the element 4 at index 6
// ...
```





---

## Member functions ##

#### Size of a Vector ####

Via the `size()` member function, the current size of a dense or sparse vector can be queried:

```
// Instantiating a dynamic vector with size 10
blaze::DynamicVector<int> v1( 10UL );
v1.size();  // Returns 10

// Instantiating a compressed vector with size 12 and capacity for 3 non-zero elements
blaze::CompressedVector<double> v2( 12UL, 3UL );
v2.size();  // Returns 12
```

Alternatively, the free function `size()` can be used to query to current size of a vector. In contrast to the member function, the free function can also be used to query the size of vector expressions:

```
size( v1 );  // Returns 10, i.e. has the same effect as the member function
size( v2 );  // Returns 12, i.e. has the same effect as the member function

blaze::DynamicMatrix<int> A( 15UL, 12UL );
size( A * v2 );  // Returns 15, i.e. the size of the resulting vector
```


#### Capacity of a Vector ####

Via the `capacity()` (member) function the internal capacity of a dense or sparse vector can be queried. Note that the capacity of a vector doesn't have to be equal to the size of a vector. In case of a dense vector the capacity will always be greater or equal than the size of the vector, in case of a sparse vector the capacity may even be less than the size.

```
v1.capacity();   // Returns at least 10
```

For symmetry reasons, there is also a free function `capacity()` available that can be used to query the capacity:

```
capacity( v1 );  // Returns at least 10, i.e. has the same effect as the member function
```

Note, however, that it is not possible to query the capacity of a vector expression:

```
capacity( A * v1 );  // Compilation error!
```


#### Number of Non-Zero Elements ####

For both dense and sparse vectors the number of non-zero elements can be determined via the `nonZeros()` member function. Sparse vectors directly return their number of non-zero elements, dense vectors traverse their elements and count the number of non-zero elements.

```
v1.nonZeros();  // Returns the number of non-zero elements in the dense vector
v2.nonZeros();  // Returns the number of non-zero elements in the sparse vector
```

There is also a free function `nonZeros()` available to query the current number of non-zero elements:

```
nonZeros( v1 );  // Returns the number of non-zero elements in the dense vector
nonZeros( v2 );  // Returns the number of non-zero elements in the sparse vector
```

The free `nonZeros()` function can also be used to query the number of non-zero elements in a vector expression. However, the result is not the exact number of non-zero elements, but may be a rough estimation:

```
nonZeros( A * v1 );  // Estimates the number of non-zero elements in the vector expression
```


#### Resize/Reserve ####

The size of a `StaticVector` is fixed by the second template parameter. In contrast, the size of `DynamicVectors`, `HybridVectors` as well as `CompressedVectors` can be changed via the `resize()` function:

```
using blaze::DynamicVector;
using blaze::CompressedVector;

DynamicVector<int,columnVector> v1;
CompressedVector<int,rowVector> v2( 4 );
v2[1] = -2;
v2[3] = 11;

// Adapting the size of the dynamic and compressed vectors. The (optional) second parameter
// specifies whether the existing elements should be preserved. Per default, the existing
// elements are not preserved.
v1.resize( 5UL );         // Resizing vector v1 to 5 elements. Elements of built-in type remain
                          // uninitialized, elements of class type are default constructed.
v1.resize( 3UL, false );  // Resizing vector v1 to 3 elements. The old elements are lost, the
                          // new elements are NOT initialized!
v2.resize( 8UL, true );   // Resizing vector v2 to 8 elements. The old elements are preserved.
v2.resize( 5UL, false );  // Resizing vector v2 to 5 elements. The old elements are lost.
```

Note that resizing a vector invalidates all existing views (see e.g. [Subvectors](Subvectors.md)) on the vector:

```
typedef blaze::DynamicVector<int,rowVector>  VectorType;
typedef blaze::DenseSubvector<VectorType>    SubvectorType;

VectorType v1( 10UL );                         // Creating a dynamic vector of size 10
SubvectorType sv = subvector( v1, 2UL, 5UL );  // Creating a view on the range [2..6]
v1.resize( 6UL );                              // Resizing the vector invalidates the view
```

When the internal capacity of a vector is no longer sufficient, the allocation of a larger junk of memory is triggered. In order to avoid frequent reallocations, the `reserve()` function can be used up front to set the internal capacity:

```
blaze::DynamicVector<int> v1;
v1.reserve( 100 );
v1.size();      // Returns 0
v1.capacity();  // Returns at least 100
```

Note that the size of the vector remains unchanged, but only the internal capacity is set according to the specified value!





---

## Free Functions ##

#### Reset/Clear ####

In order to reset all elements of a vector, the `reset()` function can be used:

```
// Setup of a single precision column vector, whose elements are initialized with 2.0F.
blaze::DynamicVector<float> v1( 3UL, 2.0F );

// Resetting all elements to 0.0F. Only the elements are reset, the size of the vector is unchanged.
reset( v1 );  // Resetting all elements
v1.size();    // Returns 3: size and capacity remain unchanged
```

In order to return a vector to its default state (i.e. the state of a default constructed vector), the `clear()` function can be used:

```
// Setup of a single precision column vector, whose elements are initialized with -1.0F.
blaze::DynamicVector<float> v1( 5, -1.0F );

// Resetting the entire vector.
clear( v1 );  // Resetting the entire vector
v1.size();    // Returns 0: size is reset, but capacity remains unchanged
```

Note that resetting or clearing both dense and sparse vectors does not change the capacity of the vectors.


#### isnan ####

The `isnan()` function provides the means to check a dense or sparse vector for non-a-number elements:

```
blaze::DynamicVector<double> a;
// ... Resizing and initialization
if( isnan( a ) ) { ... }
\endcode

\code
blaze::CompressedVector<double> a;
// ... Resizing and initialization
if( isnan( a ) ) { ... }
```

If at least one element of the vector is not-a-number, the function returns `true`, otherwise it returns `false`. Please note that this function only works for vectors with floating point elements. The attempt to use it for a vector with a non-floating point element type results in a compile time error.


#### isDefault ####

The `isDefault()` function returns whether the given dense or sparse vector is in default state:

```
blaze::HybridVector<int,20UL> a;
// ... Resizing and initialization
if( isDefault( a ) ) { ... }
```

A vector is in default state if it appears to just have been default constructed. A resizable vector (`HybridVector`, `DynamicVector`, or `CompressedVector`) is in default state if its size is equal to zero. A non-resizable vector (`StaticVector`, all subvectors, rows, and columns) is in default state if all its elements are in default state. For instance, in case the vector is instantiated for a built-in integral or floating point data type, the function returns `true` in case all vector elements are 0 and `false` in case any vector element is not 0.


#### Absolute Values ####

The `abs()` function can be used to compute the absolute values of each element of a vector. For instance, the following computation

```
blaze::StaticVector<int,3UL,rowVector> a( -1, 2, -3 );
blaze::StaticVector<int,3UL,rowVector> b( abs( a ) );
```

results in the vector

```
    ( 1 )
b = ( 2 )
    ( 3 )
```


#### Minimum/Maximum Values ####

The `min()` and the `max()` functions return the smallest and largest element of the given dense or sparse vector, respectively:

```
blaze::StaticVector<int,4UL,rowVector> a( -5, 2,  7,  4 );
blaze::StaticVector<int,4UL,rowVector> b( -5, 2, -7, -4 );

min( a );  // Returns -5
min( b );  // Returns -7

max( a );  // Returns 7
max( b );  // Returns 2
```

In case the vector currently has a size of 0, both functions return 0. Additionally, in case a given sparse vector is not completely filled, the zero elements are taken into account. For example: the following compressed vector has only 2 non-zero elements. However, the minimum of this vector is 0:

```
blaze::CompressedVector<int> c( 4UL, 2UL );
c[0] = 1;
c[2] = 3;

min( c );  // Returns 0
```

Also note that the `min()` and `max()` functions can be used to compute the smallest and largest element of a vector expression:

```
min( a + b + c );  // Returns -9, i.e. the smallest value of the resulting vector
max( a - b - c );  // Returns 14, i.e. the largest value of the resulting vector
```


#### Vector Length ####

In order to calculate the length of a vector, both the `length()` and `sqrLength()` function can be used:

```
blaze::StaticVector<float,3UL,rowVector> v( -1.2F, 2.7F, -2.3F );

const float len    = length   ( v );  // Computes the current length of the vector
const float sqrlen = sqrLength( v );  // Computes the square length of the vector
```

Note that both functions can only be used for vectors with built-in or complex element type.


#### Vector Transpose ####

As already mentioned, vectors can be either column vectors (`blaze::columnVector`) or row vectors (`blaze::rowVector`). A column vector cannot be assigned to a row vector and vice versa. However, vectors can be transposed via the `trans()` function:

```
blaze::DynamicVector<int,columnVector> v1( 4UL );
blaze::CompressedVector<int,rowVector> v2( 6UL );

v1 = v2;            // Compilation error: Cannot assign a row vector to a column vector
v1 = trans( v2 );   // OK: Transposing the row vector to a column vector and assigning it to the column vector v1
v2 = trans( v1 );   // OK: Transposing the column vector v1 and assigning it to the row vector v2
v1 += trans( v2 );  // OK: Addition assignment of two column vectors
```


#### Normalize ####

The `normalize()` function can be used to scale any non-zero vector to a length of 1. In case the vector does not contain a single non-zero element (i.e. is a zero vector), the `normalize()` function returns a zero vector.

```
blaze::DynamicVector<float,columnVector>     v1( 10UL );
blaze::CompressedVector<double,columnVector> v2( 12UL );

v1 = normalize( v1 );  // Normalizing the dense vector v1
length( v1 );          // Returns 1 (or 0 in case of a zero vector)
v1 = normalize( v2 );  // Assigning v1 the normalized vector v2
length( v1 );          // Returns 1 (or 0 in case of a zero vector)
```

Note that the `normalize()` function only works for floating point vectors. The attempt to use it for an integral vector results in a compile time error.


#### Swap ####

Via the `swap()` function it is possible to completely swap the contents of two vectors of the same type:

```
blaze::DynamicVector<int,columnVector> v1( 10UL );
blaze::DynamicVector<int,columnVector> v2( 20UL );

swap( v1, v2 );  // Swapping the contents of v1 and v2
```



---

Previous: [Vector Types](Vector_Types.md) ---- Next: [Matrix Types](Matrix_Types.md)