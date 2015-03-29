<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the column views of the Blaze library
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


Just as rows provide a view on a specific row of a matrix, columns provide views on a specific column of a dense or sparse matrix. As such, columns act as a reference to a specific column. This reference is valid an can be used in every way any other column vector can be used as long as the matrix containing the column is not resized or entirely destroyed. Changes made to the elements (e.g. modifying values, inserting or erasing elements) are immediately visible in the matrix and changes made via the matrix are immediately visible in the column. **Blaze** provides two column types: [DenseColumn](Columns#DenseColumn.md) and [SparseColumn](Columns#SparseColumn.md).





---

## DenseColumn ##

The `blaze::DenseColumn` class template represents a reference to a specific column of a dense matrix primitive. It can be included via the header file

```
#include <blaze/math/DenseColumn.h>
```

The type of the dense matrix is specified via template parameter:

```
template< typename MT >
class DenseColumn;
```

`MT` specifies the type of the dense matrix primitive. `DenseColumn` can be used with every dense matrix primitive, but does not work with any matrix expression type.





---

## SparseColumn ##

The `blaze::SparseColumn` class template represents a reference to a specific column of a sparse matrix primitive. It can be included via the header file

```
#include <blaze/math/SparseColumn.h>
```

The type of the sparse matrix is specified via template parameter:

```
template< typename MT >
class SparseColumn;
```

`MT` specifies the type of the sparse matrix primitive. `SparseColumn` can be used with every sparse matrix primitive, but does not work with any matrix expression type.





---

## Setup of Columns ##

Similar to the setup of a row, a reference to a dense or sparse column can be created very conveniently via the `column()` function. This reference can be treated as any other column vector, i.e. it can be assigned to, copied from, and be used in arithmetic operations. The column can either be used as an alias to grant write access to a specific column of a matrix primitive on the left-hand side of an assignment or to grant read-access to a specific column of a matrix primitive or expression on the right-hand side of an assignment. The following two examples demonstrate this for dense and sparse matrices:

```
typedef blaze::DynamicVector<double,columnVector>     DenseVectorType;
typedef blaze::CompressedVector<double,columnVector>  SparseVectorType;
typedef blaze::DynamicMatrix<double,columnMajor>      DenseMatrixType;
typedef blaze::CompressedMatrix<double,columnMajor>   SparseMatrixType;

DenseVectorType  x;
SparseVectorType y;
DenseMatrixType  A, B;
SparseMatrixType C, D;
// ... Resizing and initialization

// Setting the 1st column of matrix A to x
blaze::DenseColumn<DenseMatrixType> col1 = column( A, 1UL );
col1 = x;

// Setting the 4th column of matrix B to y
column( B, 4UL ) = y;

// Setting x to the 2nd column of the result of the matrix multiplication
x = column( A * B, 2UL );

// Setting y to the 2nd column of the result of the sparse matrix multiplication
y = column( C * D, 2UL );
```

The `column()` function can be used on any dense or sparse matrix, including expressions, as illustrated by the source code example. However, both [DenseColumn](Columns#DenseColumn.md) and [SparseColumn](Columns#SparseColumn.md) cannot be instantiated for expression types, but only for dense and sparse matrix primitives, respectively, i.e. for matrix types that offer write access.





---

## Common Operations ##

A column view can be used like any other column vector. For instance, the current number of elements can be obtained via the `size()` function, the current capacity via the `capacity()` function, and the number of non-zero elements via the `nonZeros()` function. However, since columns are references to specific columns of a matrix, several operations are not possible on views, such as resizing and swapping. The following example shows this by means of a dense column view:

```
typedef blaze::DynamicMatrix<int,columnMajor>  MatrixType;
typedef blaze::DenseColumn<MatrixType>         ColumnType;

MatrixType A( 42UL, 42UL );
// ... Resizing and initialization

// Creating a reference to the 2nd column of matrix A
ColumnType col2 = column( A, 2UL );

col2.size();          // Returns the number of elements in the column
col2.capacity();      // Returns the capacity of the column
col2.nonZeros();      // Returns the number of non-zero elements contained in the column

col2.resize( 84UL );  // Compilation error: Cannot resize a single column of a matrix

ColumnType col3 = column( A, 3UL );
swap( col2, col3 );   // Compilation error: Swap operation not allowed
```





---

## Element Access ##

The elements of the column can be directly accessed with the subscript operator. The indices to access a column are zero-based:

```
typedef blaze::DynamicMatrix<int,rowMajor>   DenseMatrixType;
typedef blaze::DenseColumn<DenseMatrixType>  DenseColumnType;

DenseMatrixType A( 42UL, 42UL );
DenseColumnType col2 = column( A, 2UL );

col2[0] = 1;
col2[1] = 3;
// ...

typedef blaze::CompressedMatrix<double,rowMajor>  SparseMatrixType;
typedef blaze::SparseColumn<SparseMatrixType>     SparseColumnType;

SparseMatrixType B( 42UL, 42UL );
SparseColumnType col4 = column( B, 4UL );

col4[2] =  4.1;
col4[1] = -6.3;
```

Alternatively, the elements of a column can be traversed via iterators. Just as with vectors, in case of non-const columns, `begin()` and `end()` return an `Iterator`, which allows a manipulation of the non-zero value, in case of a constant column a `ConstIterator` is returned:

```
typedef blaze::DynamicMatrix<int,columnMajor>  MatrixType;
typedef blaze::DenseColumn<MatrixType>         ColumnType;

MatrixType A( 128UL, 256UL );
// ... Resizing and initialization

// Creating a reference to the 31st column of matrix A
ColumnType col31 = column( A, 31UL );

for( ColumnType::Iterator it=col31.begin(); it!=col31.end(); ++it ) {
   *it = ...;  // OK; Write access to the dense column value
   ... = *it;  // OK: Read access to the dense column value.
}

for( ColumnType::ConstIterator it=col31.begin(); it!=col31.end(); ++it ) {
   *it = ...;  // Compilation error: Assignment to the value via a ConstIterator is invalid.
   ... = *it;  // OK: Read access to the dense column value.
}
```

```
typedef blaze::CompressedMatrix<int,columnMajor>  MatrixType;
typedef blaze::SparseColumn<MatrixType>           ColumnType;

MatrixType A( 128UL, 256UL );
// ... Resizing and initialization

// Creating a reference to the 31st column of matrix A
ColumnType col31 = column( A, 31UL );

for( ColumnType::Iterator it=col31.begin(); it!=col31.end(); ++it ) {
   it->value() = ...;  // OK: Write access to the value of the non-zero element.
   ... = it->value();  // OK: Read access to the value of the non-zero element.
   it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
   ... = it->index();  // OK: Read access to the index of the sparse element.
}

for( ColumnType::Iterator it=col31.begin(); it!=col31.end(); ++it ) {
   it->value() = ...;  // Compilation error: Assignment to the value via a ConstIterator is invalid.
   ... = it->value();  // OK: Read access to the value of the non-zero element.
   it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
   ... = it->index();  // OK: Read access to the index of the sparse element.
}
```





---

## Element Insertion ##

Inserting/accessing elements in a sparse column can be done by several alternative functions. The following example demonstrates all options:

```
typedef blaze::CompressedMatrix<double,blaze::columnMajor>  MatrixType;
MatrixType A( 100UL, 10UL );  // Non-initialized 10x100 matrix

typedef blaze::SparseColumn<MatrixType>  ColumnType;
ColumnType col0( column( A, 0UL ) );  // Reference to the 0th column of A

// The subscript operator provides access to all possible elements of the sparse column,
// including the zero elements. In case the subscript operator is used to access an element
// that is currently not stored in the sparse column, the element is inserted into the column.
col0[42] = 2.0;

// The second operation for inserting elements is the set() function. In case the element
// is not contained in the column it is inserted into the column, if it is already contained
// in the column its value is modified.
col0.set( 45UL, -1.2 );

// An alternative for inserting elements into the column is the insert() function. However,
// it inserts the element only in case the element is not already contained in the column.
col0.insert( 50UL, 3.7 );

// A very efficient way to add new elements to a sparse column is the append() function.
// Note that append() requires that the appended element's index is strictly larger than
// the currently largest non-zero index of the column and that the column's capacity is
// large enough to hold the new element.
col0.reserve( 10UL );
col0.append( 51UL, -2.1 );
```





---

## Arithmetic Operations ##

Both dense and sparse columns can be used in all arithmetic operations that any other dense or sparse column vector can be used in. The following example gives an impression of the use of dense columns within arithmetic operations. All operations (addition, subtraction, multiplication, scaling, ...) can be performed on all possible combinations of dense and sparse columns with fitting element types:

```
blaze::DynamicVector<double,blaze::columnVector> a( 2UL, 2.0 ), b;
blaze::CompressedVector<double,blaze::columnVector> c( 2UL );
c[1] = 3.0;

typedef blaze::DynamicMatrix<double,blaze::columnMajor>  MatrixType;
MatrixType A( 2UL, 4UL );  // Non-initialized 2x4 matrix

typedef blaze::DenseColumn<DenseMatrix>  RowType;
RowType col0( column( A, 0UL ) );  // Reference to the 0th column of A

col0[0] = 0.0;           // Manual initialization of the 0th column of A
col0[1] = 0.0;
column( A, 1UL ) = 1.0;  // Homogeneous initialization of the 1st column of A
column( A, 2UL ) = a;    // Dense vector initialization of the 2nd column of A
column( A, 3UL ) = c;    // Sparse vector initialization of the 3rd column of A

b = col0 + a;                 // Dense vector/dense vector addition
b = c + column( A, 1UL );     // Sparse vector/dense vector addition
b = col0 * column( A, 2UL );  // Component-wise vector multiplication

column( A, 1UL ) *= 2.0;     // In-place scaling of the 1st column
b = column( A, 1UL ) * 2.0;  // Scaling of the 1st column
b = 2.0 * column( A, 1UL );  // Scaling of the 1st column

column( A, 2UL ) += a;                 // Addition assignment
column( A, 2UL ) -= c;                 // Subtraction assignment
column( A, 2UL ) *= column( A, 0UL );  // Multiplication assignment

double scalar = trans( c ) * column( A, 1UL );  // Scalar/dot/inner product between two vectors

A = column( A, 1UL ) * trans( c );  // Outer product between two vectors
```





---

## Views on Matrices with Non-Fitting Storage Order ##

Especially noteworthy is that column views can be created for both row-major and column-major matrices. Whereas the interface of a row-major matrix only allows to traverse a row directly and the interface of a column-major matrix only allows to traverse a column, via views it is possible to traverse a row of a column-major matrix or a column of a row-major matrix. For instance:

```
typedef blaze::CompressedMatrix<int,rowMajor>  MatrixType;
typedef blaze::SparseColumn<MatrixType>        ColumnType;

MatrixType A( 64UL, 32UL );
// ... Resizing and initialization

// Creating a reference to the 31st column of a row-major matrix A
ColumnType col1 = column( A, 1UL );

for( ColumnType::Iterator it=col1.begin(); it!=col1.end(); ++it ) {
   // ...
}
```

However, please note that creating a column view on a matrix stored in a row-major fashion can result in a considerable performance decrease in comparison to a view on a matrix with a fitting storage orientation. This is due to the non-contiguous storage of the matrix elements. Therefore care has to be taken in the choice of the most suitable storage order:

```
// Setup of two row-major matrices
CompressedMatrix<double,rowMajor> A( 128UL, 128UL );
CompressedMatrix<double,rowMajor> B( 128UL, 128UL );
// ... Resizing and initialization

// The computation of the 15th column of the multiplication between A and B ...
CompressedVector<double,columnVector> x = column( A * B, 15UL );

// ... is essentially the same as the following computation, which multiplies
// the 15th column of the row-major matrix B with A.
CompressedVector<double,columnVector> x = A * column( B, 15UL );
```

Although **Blaze** performs the resulting matrix/vector multiplication as efficiently as possible using a column-major storage order for matrix `B` would result in a more efficient evaluation.



---

Previous: [Rows](Rows.md)  ----  Next: [Addition](Addition.md)