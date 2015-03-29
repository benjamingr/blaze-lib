<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the symmetric matrices of the Blaze library
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


In contrast to plain matrices, which have no restriction in their number of rows and columns and whose elements can have any value, symmetric matrices provide the compile time guarantee to be square matrices with pair-wise identical values. Mathematically, this means that a symmetric matrix is always equal to its transpose (A = A<sup>T</sup>) and that all non-diagonal values have an identical counterpart (a<sub>ij</sub> == a<sub>ji</sub>). This symmetry property can be exploited to provide higher efficiency and/or lower memory consumption. Within the **Blaze** library, symmetric matrices are realized by the [SymmetricMatrix](Symmetric_Matrices#SymmetricMatrix.md) class template.





---

## SymmetricMatrix ##

The `blaze::SymmetricMatrix` class template is an adapter for existing dense and sparse matrix types. It inherits the properties and the interface of the given matrix type `MT` and extends it by enforcing the additional invariant of symmetry (i.e. the matrix is always equal to its transpose A = A<sup>T</sup>). It can be included via the header file

```
#include <blaze/math/SymmetricMatrix.h>
```

The type of the adapted matrix can be specified via template parameter:

```
template< typename MT >
class SymmetricMatrix;
```

`MT` specifies the type of the matrix to be adapted. `SymmetricMatrix` can be used with any non-cv-qualified, non-reference, non-pointer, non-expression dense or sparse matrix type. Note that the given matrix type must be either resizable (as for instance `blaze::HybridMatrix` or `blaze::DynamicMatrix`) or must be square at compile time (as for instance `blaze::StaticMatrix`).

The following examples give an impression of several possible symmetric matrices:

```
// Definition of a 3x3 row-major dense symmetric matrix with static memory
blaze::SymmetricMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > A;

// Definition of a resizable column-major dense symmetric matrix based on HybridMatrix
blaze::SymmetricMatrix< blaze::HybridMatrix<float,4UL,4UL,blaze::columnMajor> B;

// Definition of a resizable row-major dense symmetric matrix based on DynamicMatrix
blaze::SymmetricMatrix< blaze::DynamicMatrix<double,blaze::rowMajor> > C;

// Definition of a compressed row-major single precision symmetric matrix
blaze::SymmetricMatrix< blaze::CompressedMatrix<float,blaze::rowMajor> > D;
```

The storage order of a symmetric matrix is depending on the storage order of the adapted matrix type `MT`. In case the adapted matrix is stored in a row-wise fashion (i.e. is specified as `blaze::rowMajor`), the symmetric matrix will also be a row-major matrix. Otherwise, if the adapted matrix is column-major (i.e. is specified as `blaze::columnMajor`), the symmetric matrix will also be a column-major matrix.





---

## Special Properties of Symmetric Matrices ##

A symmetric matrix is used exactly like a matrix of the underlying, adapted matrix type `MT`. It also provides (nearly) the same interface as the underlying matrix type. However, there are some important exceptions resulting from the symmetry constraint:

  * [Symmetric Matrices Must Always be Square](Symmetric_Matrices#Symmetric_Matrices_Must_Always_be_Square.md)
  * [The Symmetry Property is Always Enforced](Symmetric_Matrices#The_Symmetry_Property_is_Always_Enforced.md)
  * [The Elements of a Dense Symmetric Matrix are Always Default Initialized](Symmetric_Matrices#The_Elements_of_a_Dense_Symmetric_Matrix_are_Always_Default_Initialized.md)


#### Symmetric Matrices Must Always be Square ####

In case a resizable matrix is used (as for instance `blaze::HybridMatrix`, `blaze::DynamicMatrix`, or `blaze::CompressedMatrix`), this means that the according constructors, the `resize()` and the `extend()` functions only expect a single parameter, which specifies both the number of rows and columns, instead of two (one for the number of rows and one for the number of columns):

```
using blaze::DynamicMatrix;
using blaze::SymmetricMatrix;
using blaze::rowMajor;

// Default constructed, default initialized, row-major 3x3 symmetric dynamic matrix
SymmetricMatrix< DynamicMatrix<double,rowMajor> > A( 3 );

// Resizing the matrix to 5x5
A.resize( 5 );

// Extending the number of rows and columns by 2, resulting in a 7x7 matrix
A.extend( 2 );
```

In case a matrix with a fixed size is used (as for instance `blaze::StaticMatrix`), the number of rows and number of columns must be specified equally:

```
using blaze::StaticMatrix;
using blaze::SymmetricMatrix;
using blaze::columnMajor;

// Correct setup of a fixed size column-major 3x3 symmetric static matrix
SymmetricMatrix< StaticMatrix<int,3UL,3UL,columnMajor> > A;

// Compilation error: the provided matrix type is not a square matrix type
SymmetricMatrix< StaticMatrix<int,3UL,4UL,columnMajor> > B;
```


#### The Symmetry Property is Always Enforced ####

This means that modifying the element a<sub>ij</sub> of a symmetric matrix also modifies its counterpart element a<sub>ji</sub>. Also, it is only possible to assign matrices that are symmetric themselves:

```
using blaze::CompressedMatrix;
using blaze::DynamicMatrix;
using blaze::StaticMatrix;
using blaze::SymmetricMatrix;
using blaze::rowMajor;

// Default constructed, row-major 3x3 symmetric compressed matrix
SymmetricMatrix< CompressedMatrix<double,rowMajor> > A( 3 );

// Initializing three elements via the function call operator
A(0,0) = 1.0;  // Initialization of the diagonal element (0,0)
A(0,2) = 2.0;  // Initialization of the elements (0,2) and (2,0)

// Inserting three more elements via the insert() function
A.insert( 1, 1, 3.0 );  // Inserting the diagonal element (1,1)
A.insert( 1, 2, 4.0 );  // Inserting the elements (1,2) and (2,1)

// Access via a non-const iterator
*A.begin(1UL) = 10.0;  // Modifies both elements (1,0) and (0,1)

// Erasing elements via the erase() function
A.erase( 0, 0 );  // Erasing the diagonal element (0,0)
A.erase( 0, 2 );  // Erasing the elements (0,2) and (2,0)

// Construction from a symmetric dense matrix
StaticMatrix<double,3UL,3UL> B(  3.0,  8.0, -2.0,
                                 8.0,  0.0, -1.0,
                                -2.0, -1.0,  4.0 );

SymmetricMatrix< DynamicMatrix<double,rowMajor> > C( B );  // OK

// Assignment of a non-symmetric dense matrix
StaticMatrix<double,3UL,3UL> D(  3.0,  8.0, -2.0,
                                 8.0,  0.0, -1.0,
                                -2.0, -1.0,  4.0 );

C = D;  // Throws an exception; symmetric invariant would be violated!
```

The same restriction also applies to the `append()` function for sparse matrices: Appending the element a<sub>ij</sub> additionally inserts the element a<sub>ji</sub> into the matrix. Despite the additional insertion, the `append()` function still provides the most efficient way to set up a symmetric sparse matrix. In order to achieve the maximum efficiency, the capacity of the individual rows/columns of the matrix should to be specifically prepared with `reserve()` calls:

```
using blaze::CompressedMatrix;
using blaze::SymmetricMatrix;
using blaze::rowMajor;

// Setup of the symmetric matrix
//
//       ( 0 1 3 )
//   A = ( 1 2 0 )
//       ( 3 0 0 )

SymmetricMatrix< CompressedMatrix<double,rowMajor> > A( 3 );

A.reserve( 5 );         // Reserving enough space for 5 non-zero elements
A.reserve( 0, 2 );      // Reserving two non-zero elements in the first row
A.reserve( 1, 2 );      // Reserving two non-zero elements in the second row
A.reserve( 2, 1 );      // Reserving a single non-zero element in the third row
A.append( 0, 1, 1.0 );  // Appending the value 1 at position (0,1) and (1,0)
A.append( 1, 1, 2.0 );  // Appending the value 2 at position (1,1)
A.append( 2, 0, 3.0 );  // Appending the value 3 at position (2,0) and (0,2)
```

The symmetry property is also enforced for views (rows, columns, submatrices, ...) on the symmetric matrix. The following example demonstrates that modifying the elements of an entire row of the symmetric matrix also affects the counterpart elements in the according column of the matrix:

```
using blaze::DynamicMatrix;
using blaze::SymmetricMatrix;

// Setup of the symmetric matrix
//
//       ( 0 1 0 2 )
//   A = ( 1 3 4 0 )
//       ( 0 4 0 5 )
//       ( 2 0 5 0 )
//
SymmetricMatrix< DynamicMatrix<int> > A( 4 );
A(0,1) = 1;
A(0,3) = 2;
A(1,1) = 3;
A(1,2) = 4;
A(2,3) = 5;

// Setting all elements in the 1st row to 0 results in the matrix
//
//       ( 0 0 0 2 )
//   A = ( 0 0 0 0 )
//       ( 0 0 0 5 )
//       ( 2 0 5 0 )
//
row( A, 1 ) = 0;
```

The next example demonstrates the (compound) assignment to submatrices of symmetric matrices. Since the modification of element a<sub>ij</sub> of a symmetric matrix also modifies the element a<sub>ji</sub>, the matrix to be assigned must be structured such that the symmetry of the symmetric matrix is preserved. Otherwise an exception is thrown:

```
using blaze::DynamicMatrix;
using blaze::SymmetricMatrix;

// Setup of two default 4x4 symmetric matrices
SymmetricMatrix< DynamicMatrix<int> > A1( 4 ), A2( 4 );

// Setup of the 3x2 dynamic matrix
//
//       ( 1 2 )
//   B = ( 3 4 )
//       ( 5 6 )
//
DynamicMatrix<int> B( 3UL, 2UL );
B(0,0) = 1;
B(0,1) = 2;
B(1,0) = 3;
B(1,1) = 4;
B(2,1) = 5;
B(2,2) = 6;

// OK: Assigning B to a submatrix of A1 such that the symmetry can be preserved
//
//        ( 0 0 1 2 )
//   A1 = ( 0 0 3 4 )
//        ( 1 3 5 6 )
//        ( 2 4 6 0 )
//
submatrix( A1, 0UL, 2UL, 3UL, 2UL ) = B;  // OK

// Error: Assigning B to a submatrix of A2 such that the symmetry cannot be preserved!
//   The elements marked with X cannot be assigned unambiguously!
//
//        ( 0 1 2 0 )
//   A2 = ( 1 3 X 0 )
//        ( 2 X 6 0 )
//        ( 0 0 0 0 )
//
submatrix( A2, 0UL, 1UL, 3UL, 2UL ) = B;  // Assignment throws an exception!
```


#### The Elements of a Dense Symmetric Matrix are Always Default Initialized ####

Although this results in a small loss of efficiency (especially in case all default values are overridden afterwards), this property is important since otherwise the symmetric property of dense symmetric matrices could not be guaranteed:

```
using blaze::DynamicMatrix;
using blaze::SymmetricMatrix;

// Uninitialized, 5x5 row-major dynamic matrix
DynamicMatrix<int,rowMajor> A( 5, 5 );

// Default initialized, 5x5 row-major symmetric dynamic matrix
SymmetricMatrix< DynamicMatrix<int,rowMajor> > B( 5 );
```





---

## Arithmetic Operations ##

A `SymmetricMatrix` matrix can participate in numerical operations in any way any other dense or sparse matrix can participate. It can also be combined with any other dense or sparse vector or matrix. The following code example gives an impression of the use of `SymmetricMatrix` within arithmetic operations:

```
using blaze::SymmetricMatrix;
using blaze::DynamicMatrix;
using blaze::HybridMatrix;
using blaze::StaticMatrix;
using blaze::CompressedMatrix;
using blaze::rowMajor;
using blaze::columnMajor;

DynamicMatrix<double,rowMajor> A( 3, 3 );
CompressedMatrix<double,rowMajor> B( 3, 3 );

SymmetricMatrix< DynamicMatrix<double,rowMajor> > C( 3 );
SymmetricMatrix< CompressedMatrix<double,rowMajor> > D( 3 );

SymmetricMatrix< HybridMatrix<float,3UL,3UL,rowMajor> > E;
SymmetricMatrix< StaticMatrix<float,3UL,3UL,columnMajor> > F;

E = A + B;     // Matrix addition and assignment to a row-major symmetric matrix
F = C - D;     // Matrix subtraction and assignment to a column-major symmetric matrix
F = A * D;     // Matrix multiplication between a dense and a sparse matrix

C *= 2.0;      // In-place scaling of matrix C
E  = 2.0 * B;  // Scaling of matrix B
F  = C * 2.0;  // Scaling of matrix C

E += A - B;    // Addition assignment
F -= C + D;    // Subtraction assignment
F *= A * D;    // Multiplication assignment
```





---

## Block-Structured Symmetric Matrices ##

It is also possible to use block-structured symmetric matrices:

```
using blaze::CompressedMatrix;
using blaze::StaticMatrix;
using blaze::SymmetricMatrix;

// Definition of a 5x5 block-structured symmetric matrix based on CompressedMatrix
SymmetricMatrix< CompressedMatrix< StaticMatrix<int,3UL,3UL> > > A( 5 );
```

Also in this case, the `SymmetricMatrix` class template enforces the invariant of symmetry and guarantees that a modifications of element a<sub>ij</sub> of the adapted matrix is also applied to element a<sub>ji</sub>:

```
// Inserting the elements (2,4) and (4,2)
A.insert( 2, 4, StaticMatrix<int,3UL,3UL>( 1, -4,  5,
                                           6,  8, -3,
                                           2, -1,  2 ) );

// Manipulating the elements (2,4) and (4,2)
A(2,4)(1,1) = -5;
```





---

## Performance Considerations ##

When the symmetric property of a matrix is know beforehands using the `SymmetricMatrix` adaptor instead of a general matrix can be a considerable performance advantage. The **Blaze** library tries to exploit the properties of symmetric matrices whenever possible. However, there are also situations when using a symmetric matrix introduces some overhead. The following examples demonstrate several situations where symmetric matrices can positively or negatively impact performance.


#### Positive Impact: Matrix/Matrix Multiplication ####

When multiplying two matrices, at least one of which is symmetric, **Blaze** can exploit the fact that A = A<sup>T</sup> and choose the fastest and most suited combination of storage orders for the multiplication. The following example demonstrates this by means of a dense matrix/sparse matrix multiplication:

```
using blaze::DynamicMatrix;
using blaze::SymmetricMatrix;
using blaze::rowMajor;
using blaze::columnMajor;

SymmetricMatrix< DynamicMatrix<double,rowMajor> > A;
SymmetricMatrix< CompressedMatrix<double,columnMajor> > B;
DynamicMatrix<double,columnMajor> C;

// ... Resizing and initialization

C = A * B;
```

Intuitively, the chosen combination of a row-major and a column-major matrix is the most suited for maximum performance. However, **Blaze** evaluates the multiplication as

```
C = A * trans( B );
```

which significantly increases the performance since in contrast to the original formulation the optimized form can be vectorized. Therefore, in the context of matrix multiplications, using the `SymmetricMatrix` adapter is obviously an advantage.


#### Positive Impact: Matrix/Vector Multiplication ####

A similar optimization is possible in case of matrix/vector multiplications:

```
using blaze::DynamicMatrix;
using blaze::DynamicVector;
using blaze::CompressedVector;
using blaze::rowMajor;
using blaze::columnVector;

SymmetricMatrix< DynamicMatrix<double,rowMajor> > A;
CompressedVector<double,columnVector> x;
DynamicVector<double,columnVector> y;

// ... Resizing and initialization

y = A * x;
```

In this example it is not intuitively apparent that using a row-major matrix is not the best possible choice in terms of performance since the computation cannot be vectorized. Choosing a column-major matrix instead, however, would enable a vectorized computation. Therefore **Blaze** exploits the fact that `A` is symmetric, selects the best suited storage order and evaluates the multiplication as

```
y = trans( A ) * x;
```

which also significantly increases the performance.


#### Positive Impact: Row/Column Views on Column/Row-Major Matrices ####

Another example is the optimization of a row view on a column-major symmetric matrix:

```
using blaze::DynamicMatrix;
using blaze::SymmetricMatrix;
using blaze::rowMajor;
using blaze::columnMajor;

typedef SymmetricMatrix< DynamicMatrix<double,columnMajor> >  DynamicSymmetric;

DynamicSymmetric A( 10UL );
DenseRow<DynamicSymmetric> row5 = row( A, 5UL );
```

Usually, a row view on a column-major matrix results in a considerable performance decrease in comparison to a row view on a row-major matrix due to the non-contiguous storage of the matrix elements. However, in case of symmetric matrices, **Blaze** instead uses the according column of the matrix, which provides the same performance as if the matrix would be row-major. Note that this also works for column views on row-major matrices, where **Blaze** can use the according row instead of a column in order to provide maximum performance.


#### Negative Impact: Assignment of a General Matrix ####

In contrast to using a symmetric matrix on the right-hand side of an assignment (i.e. for read access), which introduces absolutely no performance penalty, using a symmetric matrix on the left-hand side of an assignment (i.e. for write access) may introduce additional overhead when it is assigned a general matrix, which is not symmetric at compile time:

```
using blaze::DynamicMatrix;
using blaze::SymmetricMatrix;

SymmetricMatrix< DynamicMatrix<double> > A, C;
DynamicMatrix<double> B;

B = A;  // Only read-access to the symmetric matrix; no performance penalty
C = A;  // Assignment of a symmetric matrix to another symmetric matrix; no runtime overhead
C = B;  // Assignment of a general matrix to a symmetric matrix; some runtime overhead
```

When assigning a general, potentially not symmetric matrix to a symmetric matrix it is necessary to check whether the matrix is symmetric at runtime in order to guarantee the symmetry property of the symmetric matrix. In case it turns out to be symmetric, it is assigned as efficiently as possible, if it is not, an exception is thrown. In order to prevent this runtime overhead it is therefore generally advisable to assign symmetric matrices to other symmetric matrices.

In this context it is especially noteworthy that in contrast to additions and subtractions the multiplication of two symmetric matrices does not necessarily result in another symmetric matrix:

```
SymmetricMatrix< DynamicMatrix<double> > A, B, C;

C = A + B;  // Results in a symmetric matrix; no runtime overhead
C = A - B;  // Results in a symmetric matrix; no runtime overhead
C = A * B;  // Is not guaranteed to result in a symmetric matrix; some runtime overhead
```



---

Previous: [Matrix Operations](Matrix_Operations.md)  ----  Next: [Triangular Matrices](Triangular_Matrices.md)