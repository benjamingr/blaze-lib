<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the submatrix views of the Blaze library
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


Submatrices provide views on a specific part of a dense or sparse matrix just as subvectors provide views on specific parts of vectors. As such, submatrices act as a reference to a specific block within a matrix. This reference is valid and can be used in every way any other dense or sparse matrix can be used as long as the matrix containing the submatrix is not resized or entirely destroyed. The submatrix also acts as an alias to the matrix elements in the specified block: Changes made to the elements (e.g. modifying values, inserting or erasing elements) are immediately visible in the matrix and changes made via the matrix are immediately visible in the submatrix. **Blaze** provides two submatrix types: [DenseSubmatrix](Submatrices#DenseSubmatrix.md) and [SparseSubmatrix](Submatrices#SparseSubmatrix.md).





---

## DenseSubmatrix ##

The `blaze::DenseSubmatrix` template represents a view on a specific submatrix of a dense matrix primitive. It can be included via the header file

```
#include <blaze/math/DenseSubmatrix.h>
```

The type of the dense matrix is specified via two template parameters:

```
template< typename MT >
class DenseSubmatrix;
```

  * `MT`: specifies the type of the dense matrix primitive. `DenseSubmatrix` can be used with every dense matrix primitive, but does not work with any matrix expression type.
  * `AF`: the alignment flag specifies whether the submatrix is aligned (`blaze::aligned`) or unaligned (`blaze::unaligned`). The default value is `blaze::unaligned`.





---

## SparseSubmatrix ##

The `blaze::SparseSubmatrix` template represents a view on a specific submatrix of a sparse matrix primitive. It can be included via the header file

```
#include <blaze/math/SparseSubmatrix.h>
```

The type of the sparse matrix is specified via two template parameters:

```
template< typename MT >
class SparseSubmatrix;
```

  * `MT`: specifies the type of the sparse matrix primitive. `SparseSubmatrix` can be used with every sparse matrix primitive, but does not work with any matrix expression type.
  * `AF`: the alignment flag specifies whether the submatrix is aligned (`blaze::aligned`) or unaligned (`blaze::unaligned`). The default value is `blaze::unaligned`.





---

## Setup of Submatrices ##

A view on a submatrix can be created very conveniently via the `submatrix()` function. This view can be treated as any other matrix, i.e. it can be assigned to, it can be copied from, and it can be used in arithmetic operations. A submatrix created from a row-major matrix will itself be a row-major matrix, a submatrix created from a column-major matrix will be a column-major matrix. The view can also be used on both sides of an assignment: The submatrix can either be used as an alias to grant write access to a specific submatrix of a dense matrix primitive on the left-hand side of an assignment or to grant read-access to a specific submatrix of a matrix primitive or expression on the right-hand side of an assignment. The following example demonstrates this in detail:

```
typedef blaze::DynamicMatrix<double,blaze::rowMajor>     DenseMatrixType;
typedef blaze::CompressedVector<int,blaze::columnMajor>  SparseMatrixType;

DenseMatrixType  D1, D2;
SparseMatrixType S1, S2;
// ... Resizing and initialization

// Creating a view on the first 8x16 block of the dense matrix D1
blaze::DenseSubmatrix<DenseMatrixType> dsm = submatrix( D1, 0UL, 0UL, 8UL, 16UL );

// Creating a view on the second 8x16 block of the sparse matrix S1
blaze::SparseSubmatrix<SparseMatrixType> ssm = submatrix( S1, 0UL, 16UL, 8UL, 16UL );

// Creating a view on the addition of D2 and S2
dsm = submatrix( D2 + S2, 5UL, 10UL, 8UL, 16UL );

// Creating a view on the multiplication of D2 and S2
ssm = submatrix( D2 * S2, 7UL, 13UL, 8UL, 16UL );
```





---

## Common Operations ##

The current size of the matrix, i.e. the number of rows or columns can be obtained via the `rows()` and `columns()` functions, the current total capacity via the `capacity()` function, and the number of non-zero elements via the `nonZeros()` function. However, since submatrices are views on a specific submatrix of a matrix, several operations are not possible on views, such as resizing and swapping:

```
typedef blaze::DynamicMatrix<int,blaze::rowMajor>  MatrixType;
typedef blaze::DenseSubmatrix<MatrixType>          SubmatrixType;

MatrixType A;
// ... Resizing and initialization

// Creating a view on the a 8x12 submatrix of matrix A
SubmatrixType sm = submatrix( A, 0UL, 0UL, 8UL, 12UL );

sm.rows();      // Returns the number of rows of the submatrix
sm.columns();   // Returns the number of columns of the submatrix
sm.capacity();  // Returns the capacity of the submatrix
sm.nonZeros();  // Returns the number of non-zero elements contained in the submatrix

sm.resize( 10UL, 8UL );  // Compilation error: Cannot resize a submatrix of a matrix

SubmatrixType sm2 = submatrix( A, 8UL, 0UL, 12UL, 8UL );
swap( sm, sm2 );  // Compilation error: Swap operation not allowed
```





---

## Element Access ##

The elements of a submatrix can be directly accessed with the function call operator:

```
typedef blaze::DynamicMatrix<double,blaze::rowMajor>  MatrixType;
MatrixType A;
// ... Resizing and initialization

// Creating a 8x8 submatrix, starting from position (4,4)
blaze::DenseSubmatrix<MatrixType> sm = submatrix( A, 4UL, 4UL, 8UL, 8UL );

// Setting the element (0,0) of the submatrix, which corresponds to
// the element at position (4,4) in matrix A
sm(0,0) = 2.0;
```

```
typedef blaze::CompressedMatrix<double,blaze::rowMajor>  MatrixType;
MatrixType A;
// ... Resizing and initialization

// Creating a 8x8 submatrix, starting from position (4,4)
blaze::SparseSubmatrix<MatrixType> sm = submatrix( A, 4UL, 4UL, 8UL, 8UL );

// Setting the element (0,0) of the submatrix, which corresponds to
// the element at position (4,4) in matrix A
sm(0,0) = 2.0;
```

Alternatively, the elements of a submatrix can be traversed via (const) iterators. Just as with matrices, in case of non-const submatrices, `begin()` and `end()` return an `Iterator`, which allows a manipulation of the non-zero values, in case of constant submatrices a `ConstIterator` is returned:

```
typedef blaze::DynamicMatrix<int,blaze::rowMajor>  MatrixType;
typedef blaze::DenseSubmatrix<MatrixType>          SubmatrixType;

MatrixType A( 256UL, 512UL );
// ... Resizing and initialization

// Creating a reference to a specific submatrix of the dense matrix A
SubmatrixType sm = submatrix( A, 16UL, 16UL, 64UL, 128UL );

// Traversing the elements of the 0th row via iterators to non-const elements
for( SubmatrixType::Iterator it=sm.begin(0); it!=sm.end(0); ++it ) {
   *it = ...;  // OK: Write access to the dense submatrix value.
   ... = *it;  // OK: Read access to the dense submatrix value.
}

// Traversing the elements of the 1st row via iterators to const elements
for( SubmatrixType::ConstIterator it=sm.begin(1); it!=sm.end(1); ++it ) {
   *it = ...;  // Compilation error: Assignment to the value via a ConstIterator is invalid.
   ... = *it;  // OK: Read access to the dense submatrix value.
}
```

```
typedef blaze::CompressedMatrix<int,blaze::rowMajor>  MatrixType;
typedef blaze::SparseSubmatrix<MatrixType>            SubmatrixType;

MatrixType A( 256UL, 512UL );
// ... Resizing and initialization

// Creating a reference to a specific submatrix of the sparse matrix A
SubmatrixType sm = submatrix( A, 16UL, 16UL, 64UL, 128UL );

// Traversing the elements of the 0th row via iterators to non-const elements
for( SubmatrixType::Iterator it=sm.begin(0); it!=sm.end(0); ++it ) {
   it->value() = ...;  // OK: Write access to the value of the non-zero element.
   ... = it->value();  // OK: Read access to the value of the non-zero element.
   it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
   ... = it->index();  // OK: Read access to the index of the sparse element.
}

// Traversing the elements of the 1st row via iterators to const elements
for( SubmatrixType::ConstIterator it=sm.begin(1); it!=sm.end(1); ++it ) {
   it->value() = ...;  // Compilation error: Assignment to the value via a ConstIterator is invalid.
   ... = it->value();  // OK: Read access to the value of the non-zero element.
   it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
   ... = it->index();  // OK: Read access to the index of the sparse element.
}
```





---

## Element Insertion ##

Inserting/accessing elements in a sparse submatrix can be done by several alternative functions. The following example demonstrates all options:

```
typedef blaze::CompressedMatrix<double,blaze::rowMajor>  MatrixType;
MatrixType A( 256UL, 512UL );  // Non-initialized matrix of size 256x512

typedef blaze::SparseSubmatrix<MatrixType>  SubmatrixType;
SubmatrixType sm = submatrix( A, 10UL, 10UL, 16UL, 16UL );  // View on a 16x16 submatrix of A

// The function call operator provides access to all possible elements of the sparse submatrix,
// including the zero elements. In case the subscript operator is used to access an element
// that is currently not stored in the sparse submatrix, the element is inserted into the
// submatrix.
sm(2,4) = 2.0;

// The second operation for inserting elements is the set() function. In case the element is
// not contained in the submatrix it is inserted into the submatrix, if it is already contained
// in the submatrix its value is modified.
sm.set( 2UL, 5UL, -1.2 );

// An alternative for inserting elements into the submatrix is the insert() function. However,
// it inserts the element only in case the element is not already contained in the submatrix.
sm.insert( 2UL, 6UL, 3.7 );

// Just as in the case of sparse matrices, elements can also be inserted via the append()
// function. In case of submatrices, append() also requires that the appended element's
// index is strictly larger than the currently largest non-zero index in the according row
// or column of the submatrix and that the according row's or column's capacity is large enough
// to hold the new element. Note however that due to the nature of a submatrix, which may be an
// alias to the middle of a sparse matrix, the append() function does not work as efficiently
// for a submatrix as it does for a matrix.
sm.reserve( 2UL, 10UL );
sm.append( 2UL, 10UL, -2.1 );
```





---

## Arithmetic Operations ##

Both dense and sparse submatrices can be used in all arithmetic operations that any other dense or sparse matrix can be used in. The following example gives an impression of the use of dense submatrices within arithmetic operations. All operations (addition, subtraction, multiplication, scaling, ...) can be performed on all possible combinations of dense and sparse matrices with fitting element types:

```
typedef blaze::DynamicMatrix<double,blaze::rowMajor>     DenseMatrixType;
typedef blaze::CompressedMatrix<double,blaze::rowMajor>  SparseMatrixType;
DenseMatrixType D1, D2, D3;
SparseMatrixType S1, S2;

typedef blaze::CompressedVector<double,blaze::columnVector>  SparseVectorType;
SparseVectorType a, b;

// ... Resizing and initialization

typedef DenseSubmatrix<DenseMatrixType>  SubmatrixType;
SubmatrixType sm = submatrix( D1, 0UL, 0UL, 8UL, 8UL );  // View on the 8x8 submatrix of matrix D1
                                                         // starting from row 0 and column 0

submatrix( D1, 0UL, 8UL, 8UL, 8UL ) = D2;  // Dense matrix initialization of the 8x8 submatrix
                                           // starting in row 0 and column 8
sm = S1;                                   // Sparse matrix initialization of the second 8x8 submatrix

D3 = sm + D2;                                    // Dense matrix/dense matrix addition
S2 = S1  - submatrix( D1, 8UL, 0UL, 8UL, 8UL );  // Sparse matrix/dense matrix subtraction
D2 = sm * submatrix( D1, 8UL, 8UL, 8UL, 8UL );   // Dense matrix/dense matrix multiplication

submatrix( D1, 8UL, 0UL, 8UL, 8UL ) *= 2.0;      // In-place scaling of a submatrix of D1
D2 = submatrix( D1, 8UL, 8UL, 8UL, 8UL ) * 2.0;  // Scaling of the a submatrix of D1
D2 = 2.0 * sm;                                   // Scaling of the a submatrix of D1

submatrix( D1, 0UL, 8UL, 8UL, 8UL ) += D2;  // Addition assignment
submatrix( D1, 8UL, 0UL, 8UL, 8UL ) -= S1;  // Subtraction assignment
submatrix( D1, 8UL, 8UL, 8UL, 8UL ) *= sm;  // Multiplication assignment

a = submatrix( D1, 4UL, 4UL, 8UL, 8UL ) * b;  // Dense matrix/sparse vector multiplication
```





---

## Aligned Submatrices ##

Usually submatrices can be defined anywhere within a matrix. They may start at any position and may have an arbitrary extension (only restricted by the extension of the underlying matrix). However, in contrast to matrices themselves, which are always properly aligned in memory and therefore can provide maximum performance, this means that submatrices in general have to be considered to be unaligned. This can be made explicit by the `blaze::unaligned` flag:

```
using blaze::unaligned;

typedef blaze::DynamicMatrix<double,blaze::rowMajor>  DenseMatrixType;

DenseMatrixType A;
// ... Resizing and initialization

// Identical creations of an unaligned submatrix of size 8x8, starting in row 0 and column 0
blaze::DenseSubmatrix<DenseMatrixType>           sm1 = submatrix           ( A, 0UL, 0UL, 8UL, 8UL );
blaze::DenseSubmatrix<DenseMatrixType>           sm2 = submatrix<unaligned>( A, 0UL, 0UL, 8UL, 8UL );
blaze::DenseSubmatrix<DenseMatrixType,unaligned> sm3 = submatrix           ( A, 0UL, 0UL, 8UL, 8UL );
blaze::DenseSubmatrix<DenseMatrixType,unaligned> sm4 = submatrix<unaligned>( A, 0UL, 0UL, 8UL, 8UL );
```

All of these calls to the `submatrix()` function are identical. Whether the alignment flag is explicitly specified or not, it always returns an unaligned submatrix. Whereas this may provide full flexibility in the creation of submatrices, this might result in performance disadvantages in comparison to matrix primitives (even in case the specified submatrix could be aligned). Whereas matrix primitives are guaranteed to be properly aligned and therefore provide maximum performance in all operations, a general view on a matrix might not be properly aligned. This may cause a performance penalty on some platforms and/or for some operations.

However, it is also possible to create aligned submatrices. Aligned submatrices are identical to unaligned submatrices in all aspects, except that they may pose additional alignment restrictions and therefore have less flexibility during creation, but don't suffer from performance penalties and provide the same performance as the underlying matrix. Aligned submatrices are created by explicitly specifying the `blaze::aligned` flag:

```
using blaze::aligned;

// Creating an aligned submatrix of size 8x8, starting in row 0 and column 0
blaze::DenseSubmatrix<DenseMatrixType,aligned> sv = submatrix<aligned>( A, 0UL, 0UL, 8UL, 8UL );
```

The alignment restrictions refer to system dependent address restrictions for the used element type and the available vectorization mode (SSE, AVX, ...). The following source code gives some examples for a double precision dense matrix, assuming that AVX is available, which packs 4 `double` values into an intrinsic vector:

```
using blaze::rowMajor;

typedef blaze::DynamicMatrix<double,rowMajor>      MatrixType;
typedef blaze::DenseSubmatrix<MatrixType,aligned>  SubmatrixType;

MatrixType D( 13UL, 17UL );
// ... Resizing and initialization

// OK: Starts at position (0,0) and the number of rows and columns are a multiple of 4
SubmatrixType dsm1 = submatrix<aligned>( D, 0UL, 0UL, 8UL, 12UL );

// OK: First row and column and the number of rows and columns are all a multiple of 4
SubmatrixType dsm2 = submatrix<aligned>( D, 4UL, 12UL, 8UL, 16UL );

// OK: First row and column are a multiple of 4 and the submatrix includes the last row and column
SubmatrixType dsm3 = submatrix<aligned>( D, 4UL, 0UL, 9UL, 17UL );

// Error: First row is not a multiple of 4
SubmatrixType dsm4 = submatrix<aligned>( D, 2UL, 4UL, 12UL, 12UL );

// Error: First column is not a multiple of 4
SubmatrixType dsm5 = submatrix<aligned>( D, 0UL, 2UL, 8UL, 8UL );

// Error: The number of rows is not a multiple of 4 and the submatrix does not include the last row
SubmatrixType dsm6 = submatrix<aligned>( D, 0UL, 0UL, 7UL, 8UL );

// Error: The number of columns is not a multiple of 4 and the submatrix does not include the last column
SubmatrixType dsm6 = submatrix<aligned>( D, 0UL, 0UL, 8UL, 11UL );
```

Note that the discussed alignment restrictions are only valid for aligned dense submatrices. In contrast, aligned sparse submatrices at this time don't pose any additional restrictions. Therefore aligned and unaligned sparse submatrices are truly fully identical. Still, in case the `blaze::aligned` flag is specified during setup, an aligned submatrix is created:

```
using blaze::aligned;

typedef blaze::CompressedMatrix<double,blaze::rowMajor>  SparseMatrixType;

SparseMatrixType A;
// ... Resizing and initialization

// Creating an aligned submatrix of size 8x8, starting in row 0 and column 0
blaze::SparseSubmatrix<SparseMatrixType,aligned> sv = submatrix<aligned>( A, 0UL, 0UL, 8UL, 8UL );
```





---

## Submatrices on Submatrices ##

It is also possible to create a submatrix view on another submatrix. In this context it is important to remember that the type returned by the `submatrix()` function is the same type as the type of the given submatrix, since the view on a submatrix is just another view on the underlying matrix:

```
typedef blaze::DynamicMatrix<double,blaze::rowMajor>  MatrixType;
typedef blaze::DenseSubmatrix<MatrixType>             SubmatrixType;

MatrixType D1;

// ... Resizing and initialization

// Creating a submatrix view on the dense matrix D1
SubmatrixType sm1 = submatrix( D1, 4UL, 4UL, 8UL, 16UL );

// Creating a submatrix view on the dense submatrix sm1
SubmatrixType sm2 = submatrix( sm1, 1UL, 1UL, 4UL, 8UL );
```



---

Previous: [Subvectors](Subvectors.md)  ----  Next: [Rows](Rows.md)