<a href='Hidden comment: =====================================================================================
#
#  Wiki page for matrix operations
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

Matrices are just as easy and intuitive to create as vectors. Still, there are a few rules to be aware of:

  * In case the last template parameter (the storage order) is omitted, the matrix is per default stored in row-major order.
  * The elements of a `StaticMatrix` or `HybridMatrix` are default initialized (i.e. built-in data types are initialized to 0, class types are initialized via the default constructor).
  * Newly allocated elements of a `DynamicMatrix` or `CompressedMatrix` remain uninitialized if they are of built-in type and are default constructed if they are of class type.


#### Default Construction ####

```
using blaze::StaticMatrix;
using blaze::DynamicMatrix;
using blaze::CompressedMatrix;

// All matrices can be default constructed. Whereas the size of a StaticMatrix is fixed via the second and
// third template parameter, the initial size of a constructed DynamicMatrix or CompressedMatrix is 0.
StaticMatrix<int,2UL,2UL> M1;             // Instantiation of a 2x2 integer row-major
                                          // matrix. All elements are initialized to 0.
DynamicMatrix<float> M2;                  // Instantiation of a single precision dynamic
                                          // row-major matrix with 0 rows and 0 columns.
DynamicMatrix<double,columnMajor> M3;     // Instantiation of a double precision dynamic
                                          // column-major matrix with 0 rows and 0 columns.
CompressedMatrix<int> M4;                 // Instantiation of a compressed integer
                                          // row-major matrix of size 0x0.
CompressedMatrix<double,columnMajor> M5;  // Instantiation of a compressed double precision
                                          // column-major matrix of size 0x0.
```


#### Construction with Specific Size ####

The `DynamicMatrix`, `HybridMatrix` and `CompressedMatrix` classes offer a constructor that allows to immediately give the matrices a specific number of rows and columns:

```
DynamicMatrix<int> M6( 5UL, 4UL );                   // Instantiation of a 5x4 dynamic row-major
                                                     // matrix. The elements are not initialized.
HybridMatrix<double,5UL,9UL> M7( 3UL, 7UL );         // Instantiation of a 3x7 hybrid row-major
                                                     // matrix. The elements are not initialized.
CompressedMatrix<float,columnMajor> M8( 8UL, 6UL );  // Instantiation of an empty 8x6 compressed
                                                     // column-major matrix.
```

Note that dense matrices (in this case `DynamicMatrix` and `HybridMatrix`) immediately allocate enough capacity for all matrix elements. Sparse matrices on the other hand (in this example `CompressedMatrix`) merely acquire the size, but don't necessarily allocate memory.


#### Initialization Constructors ####

All dense matrix classes offer a constructor for a direct, homogeneous initialization of all matrix elements. In contrast, for sparse matrices the predicted number of non-zero elements can be specified.

```
StaticMatrix<int,4UL,3UL,columnMajor> M9( 7 );  // Instantiation of a 4x3 integer column-major
                                                // matrix. All elements are initialized to 7.
DynamicMatrix<float> M10( 2UL, 5UL, 2.0F );     // Instantiation of a 2x5 single precision row-major
                                                // matrix. All elements are initialized to 2.0F.
CompressedMatrix<int> M11( 3UL, 4UL, 4 );       // Instantiation of a 3x4 integer row-major
                                                // matrix with capacity for 4 non-zero elements.
```

The `StaticMatrix` class offers a special initialization constructor. For `StaticMatrix` of up to 10 elements the matrix elements can be individually specified in the constructor:

```
using blaze::StaticMatrix;

StaticMatrix<int,3UL,1UL> M12( 2, 5, -1 );
StaticMatrix<float,2UL,3UL,columnMajor> M13( -0.1F, 4.2F, -7.1F,
                                             -0.8F, 1.3F, 4.2F );
StaticMatrix<double,3UL,3UL,rowVector> M14( 1.3, -0.4, 8.3,
                                            0.2, -1.5, -2.6,
                                            1.3, 9.3, -7.1 );

```


#### Array Construction ####

Alternatively, all dense matrix classes offer a constructor for an initialization with a dynamic or static array. If the matrix is initialized from a dynamic array, the constructor expects the dimensions of values provided by the array as first and second argument, the array as third argument. In case of a static array, the fixed size of the array is used:

```
const double array1* = new double[6];
// ... Initialization of the dynamic array

float array2[3][2] = { { 3.1F, 6.4F }, { -0.9F, -1.2F }, { 4.8F, 0.6F } };

blaze::StaticMatrix<double,2UL,3UL> v1( 2UL, 3UL, array1 );
blaze::DynamicMatrix<float>         v2( array2 );

delete[] array1;
```


#### Copy Construction ####

All dense and sparse matrices can be created as a copy of another dense or sparse matrix.

```
StaticMatrix<int,5UL,4UL,rowMajor> M15( M6 );    // Instantiation of the dense row-major matrix M15
                                                 // as copy of the dense row-major matrix M6.
DynamicMatrix<float,columnMajor> M16( M8 );      // Instantiation of the dense column-major matrix M16
                                                 // as copy of the sparse column-major matrix M8.
CompressedMatrix<double,columnMajor> M17( M7 );  // Instantiation of the compressed column-major matrix
                                                 // M17 as copy of the dense row-major matrix M7.
CompressedMatrix<float,rowMajor> M18( M8 );      // Instantiation of the compressed row-major matrix
                                                 // M18 as copy of the compressed column-major matrix M8.
```

Note that it is not possible to create a `StaticMatrix` as a copy of a matrix with a different number of rows and/or columns:

```
StaticMatrix<int,4UL,5UL,rowMajor> M19( M6 );     // Runtime error: Number of rows and columns does not match!
StaticMatrix<int,4UL,4UL,columnMajor> M20( M9 );  // Compile time error: Number of columns does not match!
```





---

## Assignment ##

There are several types of assignment to dense and sparse matrices: Homogeneous Assignment, Array Assignment, Copy Assignment, and Compound Assignment.


#### Homogeneous Assignment ####

It is possible to assign the same value to all elements of a dense matrix. All dense matrix classes provide an according assignment operator:

```
blaze::StaticMatrix<int,3UL,2UL> M1;
blaze::DynamicMatrix<double> M2;

// Setting all integer elements of the StaticMatrix to 4
M1 = 4;

// Setting all double precision elements of the DynamicMatrix to 3.5
M2 = 3.5
```


#### Array Assignment ####

Dense matrices can also be assigned a static array:

```
blaze::StaticMatrix<int,2UL,2UL,rowMajor> M1;
blaze::StaticMatrix<int,2UL,2UL,columnMajor> M2;
blaze::DynamicMatrix<double> M3;

int array1[2][2] = { { 1, 2 }, { 3, 4 } };
double array2[3][2] = { { 3.1, 6.4 }, { -0.9, -1.2 }, { 4.8, 0.6 } };

M1 = array1;
M2 = array1;
M3 = array2;
```

Note that due to the different storage order, the matrix M1 is initialized differently than matrix M2:

```
M1 = ( 1 2 )     M2 = ( 1 3 )
     ( 3 4 )          ( 2 4 )
```

Also note that the dimensions of the static array have to match the size of a `StaticMatrix`, whereas a `DynamicMatrix` is resized according to the array dimensions:

```
     (  3.1  6.4 )
M3 = ( -0.9 -1.2 )
     (  4.8  0.6 )
```


#### Copy Assignment ####

All kinds of matrices can be assigned to each other. The only restriction is that since a `StaticMatrix` cannot change its size, the assigned matrix must match both in the number of rows and in the number of columns.

```
blaze::StaticMatrix<int,3UL,2UL,rowMajor> M1;
blaze::DynamicMatrix<int,rowMajor> M2( 3UL, 2UL );
blaze::DynamicMatrix<float,rowMajor> M3( 5UL, 2UL );
blaze::CompressedMatrix<int,rowMajor> M4( 3UL, 2UL );
blaze::CompressedMatrix<float,columnMajor> M5( 3UL, 2UL );

// ... Initialization of the matrices

M1 = M2;  // OK: Assignment of a 3x2 dense row-major matrix to another 3x2 dense row-major matrix
M1 = M4;  // OK: Assignment of a 3x2 sparse row-major matrix to a 3x2 dense row-major matrix
M1 = M3;  // Runtime error: Cannot assign a 5x2 matrix to a 3x2 static matrix
M1 = M5;  // OK: Assignment of a 3x2 sparse column-major matrix to a 3x2 dense row-major matrix
```


#### Compound Assignment ####

Compound assignment is also available for matrices: addition assignment, subtraction assignment, and multiplication assignment. In contrast to plain assignment, however, the number of rows and columns of the two operands have to match according to the arithmetic operation.

```
blaze::StaticMatrix<int,2UL,3UL,rowMajor> M1;
blaze::DynamicMatrix<int,rowMajor> M2( 2UL, 3UL );
blaze::CompressedMatrix<float,columnMajor> M3( 2UL, 3UL );
blaze::CompressedMatrix<float,rowMajor> M4( 2UL, 4UL );
blaze::StaticMatrix<float,2UL,4UL,rowMajor> M5;
blaze::CompressedMatrix<float,rowMajor> M6( 3UL, 2UL );

// ... Initialization of the matrices

M1 += M2 ; // OK: Addition assignment between two row-major matrices of the same dimensions
M1 -= M3;  // OK: Subtraction assignment between between a row-major and a column-major matrix
M1 += M4 ; // Runtime error: No compound assignment between matrices of different size
M1 -= M5;  // Compilation error: No compound assignment between matrices of different size
M2 *= M6;  // OK: Multiplication assignment between two row-major matrices
```

Note that the multiplication assignment potentially changes the number of columns of the target matrix:

```
( 2 0 1 )     ( 4 0 )     ( 8 3 )
( 0 3 2 )  *  ( 1 0 )  =  ( 3 6 )
              ( 0 3 )
```

Since a `StaticMatrix` cannot change its size, only a square `StaticMatrix` can be used in a multiplication assignment with other square matrices of the same dimensions.





---

## Element Access ##

The easiest way to access a specific dense or sparse matrix element is via the function call operator. The indices to access a matrix are zero-based:

```
blaze::DynamicMatrix<int> M1( 4UL, 6UL );
M1(0,0) = 1;
M1(0,1) = 3;
// ...

blaze::CompressedMatrix<double> M2( 5UL, 3UL );
M2(0,2) =  4.1;
M2(1,1) = -6.3;
```

Since dense matrices allocate enough memory for all contained elements, using the function call operator on a dense matrix directly returns a reference to the accessed value. In case of a sparse matrix, if the accessed value is currently not contained in the matrix, the value is inserted into the matrix prior to returning a reference to the value, which can be much more expensive than the direct access to a dense matrix. Consider the following example:

```
blaze::CompressedMatrix<int> M1( 4UL, 4UL );

for( size_t i=0UL; i<M1.rows(); ++i ) {
   for( size_t j=0UL; j<M1.columns(); ++j ) {
      ... = M1(i,j);
   }
}
```

Although the compressed matrix is only used for read access within the for loop, using the function call operator temporarily inserts 16 non-zero elements into the matrix. Therefore, all matrices (sparse as well as dense) offer an alternate way via the `begin()`, `cbegin()`, `end()` and `cend()` functions to traverse all contained elements by iterator. Note that it is not possible to traverse all elements of the matrix, but that it is only possible to traverse elements in a row/column-wise fashion. In case of a non-const matrix, `begin()` and `end()` return an `Iterator`, which allows a manipulation of the non-zero value, in case of a constant matrix or in case `cbegin()` or `cend()` are used a `ConstIterator` is returned:

```
using blaze::CompressedMatrix;

CompressedMatrix<int,rowMajor> M1( 4UL, 6UL );

// Traversing the matrix by Iterator
for( size_t i=0UL; i<A.rows(); ++i ) {
   for( CompressedMatrix<int,rowMajor>::Iterator it=A.begin(i); it!=A.end(i); ++it ) {
      it->value() = ...;  // OK: Write access to the value of the non-zero element.
      ... = it->value();  // OK: Read access to the value of the non-zero element.
      it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
      ... = it->index();  // OK: Read access to the index of the non-zero element.
   }
}

// Traversing the matrix by ConstIterator
for( size_t i=0UL; i<A.rows(); ++i ) {
   for( CompressedMatrix<int,rowMajor>::ConstIterator it=A.cbegin(i); it!=A.cend(i); ++it ) {
      it->value() = ...;  // Compilation error: Assignment to the value via a ConstIterator is invalid.
      ... = it->value();  // OK: Read access to the value of the non-zero element.
      it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
      ... = it->index();  // OK: Read access to the index of the non-zero element.
   }
}
```

Note that `begin()`, `cbegin()`, `end()`, and `cend()` are also available as free functions:

```
for( size_t i=0UL; i<A.rows(); ++i ) {
   for( CompressedMatrix<int,rowMajor>::Iterator it=begin( A, i ); it!=end( A, i ); ++it ) {
      // ...
   }
}

for( size_t i=0UL; i<A.rows(); ++i ) {
   for( CompressedMatrix<int,rowMajor>::ConstIterator it=cbegin( A, i ); it!=cend( A, i ); ++it ) {
      // ...
   }
}
```





---

## Element Insertion ##

Whereas a dense matrix always provides enough capacity to store all matrix elements, a sparse matrix only stores the non-zero elements. Therefore it is necessary to explicitly add elements to the matrix. The first possibility to add elements to a sparse matrix is the function call operator:

```
using blaze::CompressedMatrix;

CompressedMatrix<int> M1( 3UL, 4UL );
M1(1,2) = 9;
```

In case the element at the given position is not yet contained in the sparse matrix, it is automatically inserted. Otherwise the old value is replaced by the new value 2. The operator returns a reference to the sparse vector element.

An alternative is the `set()` function: In case the element is not yet contained in the matrix the element is inserted, else the element's value is modified:

```
// Insert or modify the value at position (2,0)
M1.set( 2, 0, 1 );
```

However, insertion of elements can be better controlled via the `insert()` function. In contrast to the function call operator and the `set() function t emits an exception in case the element is already contained in the matrix. In order to check for this case, the `find()` function can be used:

```
// In case the element at position (2,3) is not yet contained in the matrix it is inserted with a value of 4.
if( M1.find( 2, 3 ) == M1.end( 2 ) )
   M1.insert( 2, 3, 4 );
```

Although the `insert()` function is very flexible, due to performance reasons it is not suited for the setup of large sparse matrices. A very efficient, yet also very low-level way to fill a sparse matrix is the `append()` function. It requires the sparse matrix to provide enough capacity to insert a new element in the specified row. Additionally, the index of the new element must be larger than the index of the previous element in the same row. Violating these conditions results in undefined behavior!

```
M1.reserve( 0, 3 );     // Reserving space for three non-zero elements in row 0
M1.append( 0, 1, 2 );   // Appending the element 2 in row 0 at column index 1
M1.append( 0, 2, -4 );  // Appending the element -4 in row 0 at column index 2
// ...

```

The most efficient way to fill a sparse matrix with elements, however, is a combination of `reserve()`, `append()`, and the `finalize()` function:

```
blaze::CompressedMatrix<int> M1( 3UL, 5UL );
M1.reserve( 3 );       // Reserving enough space for 3 non-zero elements
M1.append( 0, 1, 1 );  // Appending the value 1 in row 0 with column index 1
M1.finalize( 0 );      // Finalizing row 0
M1.append( 1, 1, 2 );  // Appending the value 2 in row 1 with column index 1
M1.finalize( 1 );      // Finalizing row 1
M1.append( 2, 0, 3 );  // Appending the value 3 in row 2 with column index 0
M1.finalize( 2 );      // Finalizing row 2
```





---

## Member Functions ##

#### Number of Rows of a Matrix ####

The current number of rows of a matrix can be acquired via the `rows()` member function:

```
// Instantiating a dynamic matrix with 10 rows and 8 columns
blaze::DynamicMatrix<int> M1( 10UL, 8UL );
M1.rows();  // Returns 10

// Instantiating a compressed matrix with 8 rows and 12 columns
blaze::CompressedMatrix<double> M2( 8UL, 12UL );
M2.rows();  // Returns 8
```

Alternatively, the free functions `rows()` can be used to query the current number of rows of a matrix. In contrast to the member function, the free function can also be used to query the number of rows of a matrix expression:

```
rows( M1 );  // Returns 10, i.e. has the same effect as the member function
rows( M2 );  // Returns 8, i.e. has the same effect as the member function

rows( M1 * M2 );  // Returns 10, i.e. the number of rows of the resulting matrix
```


#### Number of Columns of a Matrix ####

The current number of columns of a matrix can be acquired via the `columns()` member function:

```
// Instantiating a dynamic matrix with 6 rows and 8 columns
blaze::DynamicMatrix<int> M1( 6UL, 8UL );
M1.columns();   // Returns 8

// Instantiating a compressed matrix with 8 rows and 7 columns
blaze::CompressedMatrix<double> M2( 8UL, 7UL );
M2.columns();   // Returns 7
```

There is also a free function `columns()` available, which can also be used to query the number of columns of a matrix expression:

```
columns( M1 );  // Returns 8, i.e. has the same effect as the member function
columns( M2 );  // Returns 7, i.e. has the same effect as the member function

columns( M1 * M2 );  // Returns 7, i.e. the number of columns of the resulting matrix
```


#### Capacity of a Matrix ####

The `capacity()` member function returns the internal capacity of a dense or sparse matrix. Note that the capacity of a matrix doesn't have to be equal to the size of a matrix. In case of a dense matrix the capacity will always be greater or equal than the total number of elements of the matrix. In case of a sparse matrix, the capacity will usually be much less than the total number of elements.

```
blaze::DynamicMatrix<float> M1( 5UL, 7UL );
blaze::StaticMatrix<float,7UL,4UL> M2;
M1.capacity();  // Returns at least 35
M2.capacity();  // Returns at least 28
```

There is also a free function `capacity()` available to query the capacity. However, please note that this function cannot be used to query the capacity of a matrix expression:

```
capacity( M1 );  // Returns at least 35, i.e. has the same effect as the member function
capacity( M2 );  // Returns at least 28, i.e. has the same effect as the member function

capacity( M1 * M2 );  // Compilation error!
```


#### Number of Non-Zero Elements ####

For both dense and sparse matrices the current number of non-zero elements can be queried via the `nonZeros()` member function. In case of matrices there are two flavors of the `nonZeros()` function: One returns the total number of non-zero elements in the matrix, the second returns the number of non-zero elements in a specific row (in case of a row-major matrix) or column (in case of a column-major matrix). Sparse matrices directly return their number of non-zero elements, dense matrices traverse their elements and count the number of non-zero elements.

```
blaze::DynamicMatrix<int,rowMajor> M1( 3UL, 5UL );

// ... Initializing the dense matrix

M1.nonZeros();     // Returns the total number of non-zero elements in the dense matrix
M1.nonZeros( 2 );  // Returns the number of non-zero elements in row 2
```

```
blaze::CompressedMatrix<double,columnMajor> M2( 4UL, 7UL );

// ... Initializing the sparse matrix

M2.nonZeros();     // Returns the total number of non-zero elements in the sparse matrix
M2.nonZeros( 3 );  // Returns the number of non-zero elements in column 3
```

The free `nonZeros()` function can also be used to query the number of non-zero elements in a matrix expression. However, the result is not the exact number of non-zero elements, but may be a rough estimation:

```
nonZeros( M1 );     // Has the same effect as the member function
nonZeros( M1, 2 );  // Has the same effect as the member function

nonZeros( M2 );     // Has the same effect as the member function
nonZeros( M2, 3 );  // Has the same effect as the member function

nonZeros( M1 * M2 );  // Estimates the number of non-zero elements in the matrix expression
```


#### Resize/Reserve ####

The dimensions of a `StaticMatrix` are fixed at compile time by the second and third template parameter. In contrast, the number or rows and/or columns of `DynamicMatrix` and `CompressedMatrix` can be changed at runtime:

```
using blaze::DynamicMatrix;
using blaze::CompressedMatrix;

DynamicMatrix<int,rowMajor> M1;
CompressedMatrix<int,columnMajor> M2( 3UL, 2UL );

// Adapting the number of rows and columns via the resize() function. The (optional)
// third parameter specifies whether the existing elements should be preserved.
M1.resize( 2UL, 2UL );         // Resizing matrix M1 to 2x2 elements. Elements of built-in type remain
                               // uninitialized, elements of class type are default constructed.
M1.resize( 3UL, 1UL, false );  // Resizing M1 to 3x1 elements. The old elements are lost, the
                               // new elements are NOT initialized!
M2.resize( 5UL, 7UL, true );   // Resizing M2 to 5x7 elements. The old elements are preserved.
M2.resize( 3UL, 2UL, false );  // Resizing M2 to 3x2 elements. The old elements are lost.
```

Note that resizing a matrix invalidates all existing views (see e.g. [Submatrices](Submatrices.md)) on the matrix:

```
typedef blaze::DynamicMatrix<int,rowMajor>  MatrixType;
typedef blaze::DenseRow<MatrixType>         RowType;

MatrixType M1( 10UL, 20UL );    // Creating a 10x20 matrix
RowType row8 = row( M1, 8UL );  // Creating a view on the 8th row of the matrix
M1.resize( 6UL, 20UL );         // Resizing the matrix invalidates the view
```

When the internal capacity of a matrix is no longer sufficient, the allocation of a larger junk of memory is triggered. In order to avoid frequent reallocations, the `reserve()` function can be used up front to set the internal capacity:

```
blaze::DynamicMatrix<int> M1;
M1.reserve( 100 );
M1.rows();      // Returns 0
M1.capacity();  // Returns at least 100
```

Additionally it is possible to reserve memory in a specific row (for a row-major matrix) or column (for a column-major matrix):

```
blaze::CompressedMatrix<int> M1( 4UL, 6UL );
M1.reserve( 1, 4 );  // Reserving enough space for four non-zero elements in row 4
```





---

## Free Functions ##

#### Reset/Clear ####

In order to reset all elements of a dense or sparse matrix, the `reset()` function can be used. The number of rows and columns of the matrix are preserved:

```
// Setting up a single precision row-major matrix, whose elements are initialized with 2.0F.
blaze::DynamicMatrix<float> M1( 4UL, 5UL, 2.0F );

// Resetting all elements to 0.0F.
reset( M1 );  // Resetting all elements
M1.rows();    // Returns 4: size and capacity remain unchanged
```

Alternatively, only a single row or column of the matrix can be resetted:

```
blaze::DynamicMatrix<int,blaze::rowMajor>    M1( 7UL, 6UL, 5 );  // Setup of a row-major matrix
blaze::DynamicMatrix<int,blaze::columnMajor> M2( 4UL, 5UL, 4 );  // Setup of a column-major matrix

reset( M1, 2UL );  // Resetting the 2nd row of the row-major matrix
reset( M2, 3UL );  // Resetting the 3rd column of the column-major matrix
```

In order to reset a row of a column-major matrix or a column of a row-major matrix, use a row or column view (see \ref views\_rows and views\_colums).

In order to return a matrix to its default state (i.e. the state of a default constructed matrix), the `clear()` function can be used:

```
// Setting up a single precision row-major matrix, whose elements are initialized with 2.0F.
blaze::DynamicMatrix<float> M1( 4UL, 5UL, 2.0F );

// Resetting all elements to 0.0F.
clear( M1 );  // Resetting the entire matrix
M1.rows();    // Returns 0: size is reset, but capacity remains unchanged
```


#### isnan ####

The `isnan()` function provides the means to check a dense or sparse matrix for non-a-number elements:

```
blaze::DynamicMatrix<double> A( 3UL, 4UL );
// ... Initialization
if( isnan( A ) ) { ... }
\endcode

\code
blaze::CompressedMatrix<double> A( 3UL, 4UL );
// ... Initialization
if( isnan( A ) ) { ... }
```

If at least one element of the matrix is not-a-number, the function returns `true`, otherwise it returns `false`. Please note that this function only works for matrices with floating point elements. The attempt to use it for a matrix with a non-floating point element type results in a compile time error.


#### isDefault ####

The `isDefault()` function returns whether the given dense or sparse matrix is in default state:

```
blaze::HybridMatrix<int,5UL,4UL> A;
// ... Resizing and initialization
if( isDefault( A ) ) { ... }
```

A matrix is in default state if it appears to just have been default constructed. A resizable matrix (`HybridMatrix`, `DynamicMatrix`, or `CompressedMatrix`) is in default state if its size is equal to zero. A non-resizable matrix (`StaticMatrix` and all submatrices) is in default state if all its elements are in default state. For instance, in case the matrix is instantiated for a built-in integral or floating point data type, the function returns `true` in case all matrix elements are 0 and `false` in case any vector element is not 0.


#### isSquare ####

If a dense or sparse matrix is a square matrix (i.e. if the number of rows is equal to the number of columns) can be checked via the `isSquare()` function:

```
blaze::DynamicMatrix<double> A;
// ... Resizing and initialization
if( isSquare( A ) ) { ... }
```


#### isDiagonal ####

The `isDiagonal()` function checks if the given dense or sparse matrix is a diagonal matrix, i.e. if it has only elements on its diagonal and if the non-diagonal elements are default elements:

```
blaze::CompressedMatrix<float> A;
// ... Resizing and initialization
if( isDiagonal( A ) ) { ... }
```


#### isSymmetric ####

Via the `isSymmetric()` function it is possible to check whether a dense or sparse matrix is symmetric:

```
blaze::DynamicMatrix<float> A;
// ... Resizing and initialization
if( isSymmetric( A ) ) { ... }
```

Note that non-square matrices are never considered to be symmetric!


#### isLower ####

Via the `isLower()` function it is possible to check whether a dense or sparse matrix is lower triangular:

```
blaze::DynamicMatrix<float> A;
// ... Resizing and initialization
if( isLower( A ) ) { ... }
```

Note that non-square matrices are never considered to be lower triangular!


#### isUpper ####

Via the `isUpper()` function it is possible to check whether a dense or sparse matrix is upper triangular:

```
blaze::DynamicMatrix<float> A;
// ... Resizing and initialization
if( isUpper( A ) ) { ... }
```

Note that non-square matrices are never considered to be upper triangular!


#### Absolute Values ####

The `abs()` function can be used to compute the absolute values of each element of a matrix. For instance, the following computation

```
blaze::StaticMatrix<int,2UL,3UL,rowMajor> A( -1, 2, -3, 4, -5, 6 );
blaze::StaticMatrix<int,2UL,3UL,rowMajor> B( abs( A ) );
```

results in the matrix

```
B = ( 1 2 3 )
    ( 4 5 6 )
```


#### Minimum/Maximum Values ####

The `min()` and the `max()` functions return the smallest and largest element of the given dense or sparse matrix, respectively:

```
blaze::StaticMatrix<int,2UL,3UL,rowMajor> A( -5, 2,  7,
                                              4, 0,  1 );
blaze::StaticMatrix<int,2UL,3UL,rowMajor> B( -5, 2, -7,
                                             -4, 0, -1 );

min( A );  // Returns -5
min( B );  // Returns -7

max( A );  // Returns 7
max( B );  // Returns 2
```

In case the matrix currently has 0 rows or 0 columns, both functions return 0. Additionally, in case a given sparse matrix is not completely filled, the zero elements are taken into account. For example: the following compressed matrix has only 2 non-zero elements. However, the minimum of this matrix is 0:

```
blaze::CompressedMatrix<int> C( 2UL, 3UL );
C(0,0) = 1;
C(0,2) = 3;

min( C );  // Returns 0
```

Also note that the `min()` and `max()` functions can be used to compute the smallest and largest element of a matrix expression:

```
min( A + B + C );  // Returns -9, i.e. the smallest value of the resulting matrix
max( A - B - C );  // Returns 11, i.e. the largest value of the resulting matrix
```


#### Matrix Transpose ####

Matrices can be transposed via the `trans()` function. Row-major matrices are transposed into a column-major matrix and vice versa:

```
blaze::DynamicMatrix<int,rowMajor> M1( 5UL, 2UL );
blaze::CompressedMatrix<int,columnMajor> M2( 3UL, 7UL );

M1 = M2;            // Assigning a column-major matrix to a row-major matrix
M1 = trans( M2 );   // Assigning the transpose of M2 (i.e. a row-major matrix) to M1
M1 += trans( M2 );  // Addition assignment of two row-major matrices
```


#### Swap ####

Via the `swap()` function it is possible to completely swap the contents of two matrices of the same type:

```
blaze::DynamicMatrix<int,rowMajor> M1( 10UL, 15UL );
blaze::DynamicMatrix<int,rowMajor> M2( 20UL, 10UL );

swap( M1, M2 );  // Swapping the contents of M1 and M2
```



---

Previous: [Matrix Types](Matrix_Types.md) ---- Next: [Symmetric Matrices](Symmetric_Matrices.md)