<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the triangular matrices of the Blaze library
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


Triangular matrices come in two flavors: lower triangular matrices provide the compile time guarantee to be square matrices and that the upper part of the matrix contains only default elements that cannot be modified. Upper triangular matrices on the other hand provide the compile time guarantee to be square and that the lower part of the matrix contains only default elements that cannot be modified. These properties can be exploited to gain higher performance and/or to save memory. Within the **Blaze** library, lower and upper triangular matrices are realized by the [UpperMatrix](Triangular_Matrices#UpperMatrix.md) and [LowerMatrix](Triangular_Matrices#LowerMatrix.md) class templates.





---

## LowerMatrix ##

The `blaze::LowerMatrix` class template is an adapter for existing dense and sparse matrix types. It inherits the properties and the interface of the given matrix type `MT` and extends it by enforcing the additional invariant that all matrix elements above the diagonal are 0 (lower triangular matrix). It can be included via the header file

```
#include <blaze/math/LowerMatrix.h>
```

The type of the adapted matrix can be specified via the first template parameter:

```
template< typename MT >
class LowerMatrix;
```

`MT` specifies the type of the matrix to be adapted. `LowerMatrix` can be used with any non-cv-qualified, non-reference, non-pointer, non-expression dense or sparse matrix type. Note that the given matrix type must be either resizable (as for instance `blaze::HybridMatrix` or `blaze::DynamicMatrix`) or must be square at compile time (as for instance `blaze::StaticMatrix`).

The following examples give an impression of several possible lower matrices:

```
// Definition of a 3x3 row-major dense lower matrix with static memory
blaze::LowerMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > A;

// Definition of a resizable column-major dense lower matrix based on HybridMatrix
blaze::LowerMatrix< blaze::HybridMatrix<float,4UL,4UL,blaze::columnMajor> B;

// Definition of a resizable row-major dense lower matrix based on DynamicMatrix
blaze::LowerMatrix< blaze::DynamicMatrix<double,blaze::rowMajor> > C;

// Definition of a compressed row-major single precision lower matrix
blaze::LowerMatrix< blaze::CompressedMatrix<float,blaze::rowMajor> > D;
```

The storage order of a lower matrix is depending on the storage order of the adapted matrix type `MT`. In case the adapted matrix is stored in a row-wise fashion (i.e. is specified as `blaze::rowMajor`), the lower matrix will also be a row-major matrix. Otherwise, if the adapted matrix is column-major (i.e. is specified as `blaze::columnMajor`), the lower matrix will also be a column-major matrix.





---

## UpperMatrix ##

The `blaze::UpperMatrix` class template is an adapter for existing dense and sparse matrix types. It inherits the properties and the interface of the given matrix type `MT` and extends it by enforcing the additional invariant that all matrix elements below the diagonal are 0 (upper triangular matrix). It can be included via the header file

```
#include <blaze/math/UpperMatrix.h>
```

The type of the adapted matrix can be specified via the first template parameter:

```
template< typename MT >
class UpperMatrix;
```

`MT` specifies the type of the matrix to be adapted. `UpperMatrix` can be used with any non-cv-qualified, non-reference, non-pointer, non-expression dense or sparse matrix type. Note that the given matrix type must be either resizable (as for instance `blaze::HybridMatrix` or `blaze::DynamicMatrix`) or must be square at compile time (as for instance `blaze::StaticMatrix`).

The following examples give an impression of several possible upper matrices:

```
// Definition of a 3x3 row-major dense upper matrix with static memory
blaze::UpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > A;

// Definition of a resizable column-major dense upper matrix based on HybridMatrix
blaze::UpperMatrix< blaze::HybridMatrix<float,4UL,4UL,blaze::columnMajor> B;

// Definition of a resizable row-major dense upper matrix based on DynamicMatrix
blaze::UpperMatrix< blaze::DynamicMatrix<double,blaze::rowMajor> > C;

// Definition of a compressed row-major single precision upper matrix
blaze::UpperMatrix< blaze::CompressedMatrix<float,blaze::rowMajor> > D;
```

The storage order of an upper matrix is depending on the storage order of the adapted matrix type `MT`. In case the adapted matrix is stored in a row-wise fashion (i.e. is specified as `blaze::rowMajor`), the upper matrix will also be a row-major matrix. Otherwise, if the adapted matrix is column-major (i.e. is specified as `blaze::columnMajor`), the upper matrix will also be a column-major matrix.





---

## Special Properties of Triangular Matrices ##

A triangular matrix is used exactly like a matrix of the underlying, adapted matrix type `MT`. It also provides (nearly) the same interface as the underlying matrix type. However, there are some important exceptions resulting from the triangular matrix constraint:

  * [Triangular Matrices Must Always be Square](Triangular_Matrices#Triangular_Matrices_Must_Always_be_Square.md)
  * [The Triangular Property is Always Enforced](Triangular_Matrices#The_Triangular_Property_is_Always_Enforced.md)
  * [The Elements of a Dense Triangular Matrix are Always Default Initialized](Triangular_Matrices#The_Elements_of_a_Dense_Triangular_Matrix_are_Always_Default_Initialized.md)

#### Triangular Matrices Must Always be Square ####

In case a resizable matrix is used (as for instance `blaze::HybridMatrix`, `blaze::DynamicMatrix`, or `blaze::CompressedMatrix`), this means that the according constructors, the `resize()` and the `extend()` functions only expect a single parameter, which specifies both the number of rows and columns, instead of two (one for the number of rows and one for the number of columns):

```
using blaze::DynamicMatrix;
using blaze::LowerMatrix;
using blaze::rowMajor;

// Default constructed, default initialized, row-major 3x3 lower dynamic matrix
LowerMatrix< DynamicMatrix<double,rowMajor> > A( 3 );

// Resizing the matrix to 5x5
A.resize( 5 );

// Extending the number of rows and columns by 2, resulting in a 7x7 matrix
A.extend( 2 );
```

In case a matrix with a fixed size is used (as for instance `blaze::StaticMatrix`), the number of rows and number of columns must be specified equally:

```
using blaze::StaticMatrix;
using blaze::LowerMatrix;
using blaze::columnMajor;

// Correct setup of a fixed size column-major 3x3 lower static matrix
LowerMatrix< StaticMatrix<int,3UL,3UL,columnMajor> > A;

// Compilation error: the provided matrix type is not a square matrix type
LowerMatrix< StaticMatrix<int,3UL,4UL,columnMajor> > B;
```


#### The Triangular Property is Always Enforced ####

This means that it is only allowed to modify elements in the lower part or the diagonal of a lower triangular matrix and in the upper part or the diagonal of an upper triangular matrix. Also, it is only possible to assign lower matrices to lower triangular matrices and upper matrices to upper triangular matrices. The following example demonstrates this restriction by means of the `blaze::LowerMatrix` adaptor. For an example with upper triangular matrices see the `blaze::UpperMatrix` class documentation.

```
using blaze::CompressedMatrix;
using blaze::DynamicMatrix;
using blaze::StaticMatrix;
using blaze::LowerMatrix;
using blaze::rowMajor;

typedef LowerMatrix< CompressedMatrix<double,rowMajor> >  CompressedLower;

// Default constructed, row-major 3x3 lower compressed matrix
CompressedLower A( 3 );

// Initializing elements via the function call operator
A(0,0) = 1.0;  // Initialization of the diagonal element (0,0)
A(2,0) = 2.0;  // Initialization of the lower element (2,0)
A(1,2) = 9.0;  // Throws an exception; invalid modification of upper element

// Inserting two more elements via the insert() function
A.insert( 1, 0, 3.0 );  // Inserting the lower element (1,0)
A.insert( 2, 1, 4.0 );  // Inserting the lower element (2,1)
A.insert( 0, 2, 9.0 );  // Throws an exception; invalid insertion of upper element

// Appending an element via the append() function
A.reserve( 1, 3 );      // Reserving enough capacity in row 1
A.append( 1, 1, 5.0 );  // Appending the diagonal element (1,1)
A.append( 1, 2, 9.0 );  // Throws an exception; appending an element in the upper part

// Access via a non-const iterator
CompressedLower::Iterator it = A.begin(1);
*it = 6.0;  // Modifies the lower element (1,0)
++it;
*it = 9.0;  // Modifies the diagonal element (1,1)

// Erasing elements via the erase() function
A.erase( 0, 0 );  // Erasing the diagonal element (0,0)
A.erase( 2, 0 );  // Erasing the lower element (2,0)

// Construction from a lower dense matrix
StaticMatrix<double,3UL,3UL> B(  3.0,  0.0,  0.0,
                                 8.0,  0.0,  0.0,
                                -2.0, -1.0,  4.0 );

LowerMatrix< DynamicMatrix<double,rowMajor> > C( B );  // OK

// Assignment of a non-lower dense matrix
StaticMatrix<double,3UL,3UL> D(  3.0,  0.0, -2.0,
                                 8.0,  0.0,  0.0,
                                -2.0, -1.0,  4.0 );

C = D;  // Throws an exception; lower matrix invariant would be violated!
```

The lower/upper matrix property is also enforced for views (rows, columns, submatrices, ...) on the triangular matrix. The following example demonstrates that modifying the elements of an entire row and submatrix of a lower matrix only affects the lower and diagonal matrix elements. Again, this example uses `blaze::LowerMatrix`, for an example with upper triangular matrices, see the `blaze::UpperMatrix` class documentation.

```
using blaze::DynamicMatrix;
using blaze::LowerMatrix;

// Setup of the lower matrix
//
//       ( 0 0 0 0 )
//   A = ( 1 2 0 0 )
//       ( 0 3 0 0 )
//       ( 4 0 5 0 )
//
LowerMatrix< DynamicMatrix<int> > A( 4 );
A(1,0) = 1;
A(1,1) = 2;
A(2,1) = 3;
A(3,0) = 4;
A(3,2) = 5;

// Setting the lower and diagonal elements in the 2nd row to 9 results in the matrix
//
//       ( 0 0 0 0 )
//   A = ( 1 2 0 0 )
//       ( 9 9 9 0 )
//       ( 4 0 5 0 )
//
row( A, 2 ) = 9;

// Setting the lower and diagonal elements in the 1st and 2nd column to 7 results in
//
//       ( 0 0 0 0 )
//   A = ( 1 7 0 0 )
//       ( 9 7 7 0 )
//       ( 4 7 7 0 )
//
submatrix( A, 0, 1, 4, 2 ) = 7;
```

The next example demonstrates the (compound) assignment to rows/columns and submatrices of triangular matrices. Since only lower/upper and diagonal elements may be modified the matrix to be assigned must be structured such that the triangular matrix invariant of the matrix is preserved. Otherwise a `std::invalid_argument` exception is thrown:

```
using blaze::DynamicMatrix;
using blaze::DynamicVector;
using blaze::LowerMatrix;
using blaze::rowVector;

// Setup of two default 4x4 lower matrices
LowerMatrix< DynamicMatrix<int> > A1( 4 ), A2( 4 );

// Setup of a 4-dimensional vector
//
//   v = ( 1 2 3 0 )
//
DynamicVector<int,rowVector> v( 4, 0 );
v[0] = 1;
v[1] = 2;
v[2] = 3;

// OK: Assigning v to the 2nd row of A1 preserves the lower matrix invariant
//
//        ( 0 0 0 0 )
//   A1 = ( 0 0 0 0 )
//        ( 1 2 3 0 )
//        ( 0 0 0 0 )
//
row( A1, 2 ) = v;  // OK

// Error: Assigning v to the 1st row of A1 violates the lower matrix invariant! The element
//   marked with X cannot be assigned and triggers an exception.
//
//        ( 0 0 0 0 )
//   A1 = ( 1 2 X 0 )
//        ( 1 2 3 0 )
//        ( 0 0 0 0 )
//
row( A1, 1 ) = v;  // Assignment throws an exception!

// Setup of the 3x2 dynamic matrix
//
//       ( 0 0 )
//   B = ( 7 0 )
//       ( 8 9 )
//
DynamicMatrix<int> B( 3UL, 2UL, 0 );
B(1,0) = 7;
B(2,0) = 8;
B(2,1) = 9;

// OK: Assigning B to a submatrix of A2 such that the lower matrix invariant can be preserved
//
//        ( 0 0 0 0 )
//   A2 = ( 0 7 0 0 )
//        ( 0 8 9 0 )
//        ( 0 0 0 0 )
//
submatrix( A2, 0UL, 1UL, 3UL, 2UL ) = B;  // OK

// Error: Assigning B to a submatrix of A2 such that the lower matrix invariant cannot be
//   preserved! The elements marked with X cannot be assigned without violating the invariant!
//
//        ( 0 0 0 0 )
//   A2 = ( 0 7 X 0 )
//        ( 0 8 8 X )
//        ( 0 0 0 0 )
//
submatrix( A2, 0UL, 2UL, 3UL, 2UL ) = B;  // Assignment throws an exception!
```


#### The Elements of a Dense Triangular Matrix are Always Default Initialized ####

Although this results in a small loss of efficiency during the creation of a dense lower or upper matrix this initialization is important since otherwise the lower/upper matrix property of dense lower matrices would not be guaranteed:

```
using blaze::DynamicMatrix;
using blaze::LowerMatrix;
using blaze::UpperMatrix;

// Uninitialized, 5x5 row-major dynamic matrix
DynamicMatrix<int,rowMajor> A( 5, 5 );

// 5x5 row-major lower dynamic matrix with default initialized upper matrix
LowerMatrix< DynamicMatrix<int,rowMajor> > B( 5 );

// 7x7 column-major upper dynamic matrix with default initialized lower matrix
UpperMatrix< DynamicMatrix<int,columnMajor> > B( 7 );
```





---

## Arithmetic Operations ##

A lower and upper triangular matrix can participate in numerical operations in any way any other dense or sparse matrix can participate. It can also be combined with any other dense or sparse vector or matrix. The following code example gives an impression of the use of `blaze::LowerMatrix` and `blaze::UpperMatrix` within arithmetic operations:

```
using blaze::LowerMatrix;
using blaze::DynamicMatrix;
using blaze::HybridMatrix;
using blaze::StaticMatrix;
using blaze::CompressedMatrix;
using blaze::rowMajor;
using blaze::columnMajor;

DynamicMatrix<double,rowMajor> A( 3, 3 );
CompressedMatrix<double,rowMajor> B( 3, 3 );

LowerMatrix< DynamicMatrix<double,rowMajor> > C( 3 );
UpperMatrix< CompressedMatrix<double,rowMajor> > D( 3 );

LowerMatrix< HybridMatrix<float,3UL,3UL,rowMajor> > E;
UpperMatrix< StaticMatrix<float,3UL,3UL,columnMajor> > F;

E = A + B;     // Matrix addition and assignment to a row-major lower matrix
F = C - D;     // Matrix subtraction and assignment to a column-major upper matrix
F = A * D;     // Matrix multiplication between a dense and a sparse matrix

C *= 2.0;      // In-place scaling of matrix C
E  = 2.0 * B;  // Scaling of matrix B
F  = C * 2.0;  // Scaling of matrix C

E += A - B;    // Addition assignment
F -= C + D;    // Subtraction assignment
F *= A * D;    // Multiplication assignment
```





---

## Block-Structured Triangular Matrices ##

It is also possible to use block-structured triangular matrices:

```
using blaze::CompressedMatrix;
using blaze::StaticMatrix;
using blaze::LowerMatrix;
using blaze::UpperMatrix;

// Definition of a 5x5 block-structured lower matrix based on DynamicMatrix
LowerMatrix< DynamicMatrix< StaticMatrix<int,3UL,3UL> > > A( 5 );

// Definition of a 7x7 block-structured upper matrix based on CompressedMatrix
UpperMatrix< CompressedMatrix< StaticMatrix<int,3UL,3UL> > > B( 7 );
```

Also in this case the triangular matrix invariant is enforced, i.e. it is not possible to manipulate elements in the upper part (lower triangular matrix) or the lower part (upper triangular matrix) of the matrix:

```
const StaticMatrix<int,3UL,3UL> C( 1, -4,  5,
                                   6,  8, -3,
                                   2, -1,  2 )

A(2,4)(1,1) = -5;     // Invalid manipulation of upper matrix element; Results in an exception
B.insert( 4, 2, C );  // Invalid insertion of the elements (4,2); Results in an exception
```





---

## Performance Considerations ##

The **Blaze** library tries to exploit the properties of lower and upper triangular matrices whenever and wherever possible. Therefore using triangular matrices instead of a general matrices can result in a considerable performance improvement. However, there are also situations when using a triangular matrix introduces some overhead. The following examples demonstrate several common situations where triangular matrices can positively or negatively impact performance.


#### Positive Impact: Matrix/Matrix Multiplication ####

When multiplying two matrices, at least one of which is triangular, **Blaze** can exploit the fact that either the lower or upper part of the matrix contains only default elements and restrict the algorithm to the non-zero elements. The following example demonstrates this by means of a dense matrix/dense matrix multiplication with lower triangular matrices:

```
using blaze::DynamicMatrix;
using blaze::LowerMatrix;
using blaze::rowMajor;
using blaze::columnMajor;

LowerMatrix< DynamicMatrix<double,rowMajor> > A;
LowerMatrix< DynamicMatrix<double,columnMajor> > B;
DynamicMatrix<double,columnMajor> C;

// ... Resizing and initialization

C = A * B;
```

In comparison to a general matrix multiplication, the performance advantage is significant, especially for large matrices. Therefore is it highly recommended to use the `blaze::LowerMatrix` and `blaze::UpperMatrix` adaptors when a matrix is known to be lower or upper triangular, respectively. Note however that the performance advantage is most pronounced for dense matrices and much less so for sparse matrices.


#### Positive Impact: Matrix/Vector Multiplication ####

A similar performance improvement can be gained when using a triangular matrix in a matrix/vector multiplication:

```
using blaze::DynamicMatrix;
using blaze::DynamicVector;
using blaze::rowMajor;
using blaze::columnVector;

LowerMatrix< DynamicMatrix<double,rowMajor> > A;
DynamicVector<double,columnVector> x, y;

// ... Resizing and initialization

y = A * x;
```

In this example, **Blaze** also exploits the structure of the matrix and approx. halves the runtime of the multiplication. Also in case of matrix/vector multiplications the performance improvement is most pronounced for dense matrices and much less so for sparse matrices.


#### Negative Impact: Assignment of a General Matrix ####

In contrast to using a triangular matrix on the right-hand side of an assignment (i.e. for read access), which introduces absolutely no performance penalty, using a triangular matrix on the left-hand side of an assignment (i.e. for write access) may introduce additional overhead when it is assigned a general matrix, which is not triangular at compile time:

```
using blaze::DynamicMatrix;
using blaze::LowerMatrix;

LowerMatrix< DynamicMatrix<double> > A, C;
DynamicMatrix<double> B;

B = A;  // Only read-access to the lower matrix; no performance penalty
C = A;  // Assignment of a lower matrix to another lower matrix; no runtime overhead
C = B;  // Assignment of a general matrix to a lower matrix; some runtime overhead
```

When assigning a general (potentially not lower triangular) matrix to a lower matrix or a general (potentially not upper triangular) matrix to an upper matrix it is necessary to check whether the matrix is lower or upper at runtime in order to guarantee the triangular property of the matrix. In case it turns out to be lower or upper, respectively, it is assigned as efficiently as possible, if it is not, an exception is thrown. In order to prevent this runtime overhead it is therefore generally advisable to assign lower or upper triangular matrices to other lower or upper triangular matrices.

In this context it is especially noteworthy that the addition, subtraction, and multiplication of two triangular matrices of the same structure always results in another triangular matrix:

```
LowerMatrix< DynamicMatrix<double> > A, B, C;

C = A + B;  // Results in a lower matrix; no runtime overhead
C = A - B;  // Results in a lower matrix; no runtime overhead
C = A * B;  // Results in a lower matrix; no runtime overhead
```

```
UpperMatrix< DynamicMatrix<double> > A, B, C;

C = A + B;  // Results in a upper matrix; no runtime overhead
C = A - B;  // Results in a upper matrix; no runtime overhead
C = A * B;  // Results in a upper matrix; no runtime overhead
```



---

Previous: [Symmetric Matrices](Symmetric_Matrices.md)  ----  Next: [Subvectors](Subvectors.md)