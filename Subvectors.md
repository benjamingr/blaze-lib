<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the subvector views of the Blaze library
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


Subvectors provide views on a specific part of a dense or sparse vector. As such, subvectors act as a reference to a specific range within a vector. This reference is valid and can be used in every way any other dense or sparse vector can be used as long as the vector containing the subvector is not resized or entirely destroyed. The subvector also acts as an alias to the vector elements in the specified range: Changes made to the elements (e.g. modifying values, inserting or erasing elements) are immediately visible in the vector and changes made via the vector are immediately visible in the subvector. **Blaze** provides two subvector types: [DenseSubvector](Subvectors#DenseSubvector.md) and [SparseSubvector](Subvectors#SparseSubvector.md).





---

## DenseSubvector ##

The `blaze::DenseSubvector` template represents a view on a specific subvector of a dense vector primitive. It can be included via the header file

```
#include <blaze/math/DenseSubvector.h>
```

The type of the dense vector is specified via two template parameters:

```
template< typename VT >
class DenseSubvector;
```

  * `VT`: specifies the type of the dense vector primitive. `DenseSubvector` can be used with every dense vector primitive or view, but does not work with any vector expression type.
  * `AF`: the alignment flag specifies whether the subvector is aligned (`blaze::aligned) or unaligned (`blaze::unaligned`). The default value is `blaze::unaligned`.





---

## SparseSubvector ##

The `blaze::SparseSubvector` template represents a view on a specific subvector of a sparse vector primitive. It can be included via the header file

```
#include <blaze/math/SparseSubvector.h>
```

The type of the sparse vector is specified via two template parameters:

```
template< typename VT >
class SparseSubvector;
```

  * `VT`: specifies the type of the sparse vector primitive. As in case of `DenseSubvector`, a `SparseSubvector` can be used with every sparse vector primitive or view, but does not work with any vector expression type.
  * `AF`: the alignment flag specifies whether the subvector is aligned (`blaze::aligned`) or unaligned (`blaze::unaligned`). The default value is `blaze::unaligned`.





---

## Setup of Subvectors ##

A view on a dense or sparse subvector can be created very conveniently via the `subvector()` function. This view can be treated as any other vector, i.e. it can be assigned to, it can be copied from, and it can be used in arithmetic operations. A subvector created from a row vector can be used as any other row vector, a subvector created from a column vector can be used as any other column vector. The view can also be used on both sides of an assignment: The subvector can either be used as an alias to grant write access to a specific subvector of a dense vector primitive on the left-hand side of an assignment or to grant read-access to a specific subvector of a vector primitive or expression on the right-hand side of an assignment. The following example demonstrates this in detail:

```
typedef blaze::DynamicVector<double,blaze::rowVector>  DenseVectorType;
typedef blaze::CompressedVector<int,blaze::rowVector>  SparseVectorType;

DenseVectorType  d1, d2;
SparseVectorType s1, s2;
// ... Resizing and initialization

// Creating a view on the first ten elements of the dense vector d1
blaze::DenseSubvector<DenseVectorType> dsv = subvector( d1, 0UL, 10UL );

// Creating a view on the second ten elements of the sparse vector s1
blaze::SparseSubvector<SparseVectorType> ssv = subvector( s1, 10UL, 10UL );

// Creating a view on the addition of d2 and s2
dsv = subvector( d2 + s2, 5UL, 10UL );

// Creating a view on the multiplication of d2 and s2
ssv = subvector( d2 * s2, 2UL, 10UL );
```

The `subvector()` function can be used on any dense or sparse vector, including expressions, as demonstrated in the example. Note however that a [DenseSubvector](Subvectors#DenseSubvector.md) or [SparseSubvector](Subvectors#SparseSubvector.md) can only be instantiated with a dense or sparse vector primitive, respectively, i.e. with types that can be, written and not with an expression type.





---

## Common Operations ##

A subvector view can be used like any other dense or sparse vector. For instance, the current number of elements can be obtained via the `size()` function, the current capacity via the `capacity()` function, and the number of non-zero elements via the `nonZeros()` function. However, since subvectors are references to a specific range of a vector, several operations are not possible on views, such as resizing and swapping. The following example shows this by means of a dense subvector view:

```
typedef blaze::DynamicVector<int,blaze::rowVector>  VectorType;
typedef blaze::DenseSubvector<VectorType>           SubvectorType;

VectorType v( 42UL );
// ... Resizing and initialization

// Creating a view on the range [5..15] of vector v
SubvectorType sv = subvector( v, 5UL, 10UL );

sv.size();          // Returns the number of elements in the subvector
sv.capacity();      // Returns the capacity of the subvector
sv.nonZeros();      // Returns the number of non-zero elements contained in the subvector

sv.resize( 84UL );  // Compilation error: Cannot resize a subvector of a vector

SubvectorType sv2 = subvector( v, 15UL, 10UL );
swap( sv, sv2 );   // Compilation error: Swap operation not allowed
```





---

## Element Access ##

The elements of a subvector can be directly accessed via the subscript operator. The indices to access a subvector are zero-based:

```
typedef blaze::DynamicVector<double,blaze::rowVector>  VectorType;
VectorType v;
// ... Resizing and initialization

// Creating an 8-dimensional subvector, starting from index 4
blaze::DenseSubvector<VectorType> sv = subvector( v, 4UL, 8UL );

// Setting the 1st element of the subvector, which corresponds to
// the element at index 5 in vector v
sv[1] = 2.0;
```

```
typedef blaze::CompressedVector<double,blaze::rowVector>  VectorType;
VectorType v;
// ... Resizing and initialization

// Creating an 8-dimensional subvector, starting from index 4
blaze::SparseSubvector<VectorType> sv = subvector( v, 4UL, 8UL );

// Setting the 1st element of the subvector, which corresponds to
// the element at index 5 in vector v
sv[1] = 2.0;
```

Alternatively, the elements of a subvector can be traversed via iterators. Just as with vectors, in case of non-const subvectors, `begin()` and `end()` return an `Iterator`, which allows a manipulation of the non-zero values, in case of constant subvectors a `ConstIterator` is returned:

```
typedef blaze::DynamicVector<int,blaze::rowVector>  VectorType;
typedef blaze::DenseSubvector<VectorType>           SubvectorType;

VectorType v( 256UL );
// ... Resizing and initialization

// Creating a reference to a specific subvector of the dense vector v
SubvectorType sv = subvector( v, 16UL, 64UL );

for( SubvectorType::Iterator it=sv.begin(); it!=sv.end(); ++it ) {
   *it = ...;  // OK: Write access to the dense subvector value.
   ... = *it;  // OK: Read access to the dense subvector value.
}

for( SubvectorType::ConstIterator it=sv.begin(); it!=sv.end(); ++it ) {
   *it = ...;  // Compilation error: Assignment to the value via a ConstIterator is invalid.
   ... = *it;  // OK: Read access to the dense subvector value.
}
```

```
typedef blaze::CompressedVector<int,blaze::rowVector>  VectorType;
typedef blaze::SparseSubvector<VectorType>             SubvectorType;

VectorType v( 256UL );
// ... Resizing and initialization

// Creating a reference to a specific subvector of the sparse vector v
SubvectorType sv = subvector( v, 16UL, 64UL );

for( SubvectorType::Iterator it=sv.begin(); it!=sv.end(); ++it ) {
   it->value() = ...;  // OK: Write access to the value of the non-zero element.
   ... = it->value();  // OK: Read access to the value of the non-zero element.
   it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
   ... = it->index();  // OK: Read access to the index of the sparse element.
}

for( SubvectorType::ConstIterator it=sv.begin(); it!=sv.end(); ++it ) {
   it->value() = ...;  // Compilation error: Assignment to the value via a ConstIterator is invalid.
   ... = it->value();  // OK: Read access to the value of the non-zero element.
   it->index() = ...;  // Compilation error: The index of a non-zero element cannot be changed.
   ... = it->index();  // OK: Read access to the index of the sparse element.
}
```





---

## Element Insertion ##

Inserting/accessing elements in a sparse subvector can be done by several alternative functions. The following example demonstrates all options:

```
typedef blaze::CompressedVector<double,blaze::rowVector>  VectorType;
VectorType v( 256UL );  // Non-initialized vector of size 256

typedef blaze::SparseSubvector<VectorType>  SubvectorType;
SubvectorType sv( subvector( v, 10UL, 60UL ) );  // View on the range [10..69] of v

// The subscript operator provides access to all possible elements of the sparse subvector,
// including the zero elements. In case the subscript operator is used to access an element
// that is currently not stored in the sparse subvector, the element is inserted into the
// subvector.
sv[42] = 2.0;

// The second operation for inserting elements is the set() function. In case the element
// is not contained in the vector it is inserted into the vector, if it is already contained
// in the vector its value is modified.
sv.set( 45UL, -1.2 );

// An alternative for inserting elements into the subvector is the insert() function. However,
// it inserts the element only in case the element is not already contained in the subvector.
sv.insert( 50UL, 3.7 );

// Just as in case of vectors, elements can also be inserted via the append() function. In
// case of subvectors, append() also requires that the appended element's index is strictly
// larger than the currently largest non-zero index of the subvector and that the subvector's
// capacity is large enough to hold the new element. Note however that due to the nature of
// a subvector, which may be an alias to the middle of a sparse vector, the append() function
// does not work as efficiently for a subvector as it does for a vector.
sv.reserve( 10UL );
sv.append( 51UL, -2.1 );
```





---

## Arithmetic Operations ##

Both dense and sparse subvectors can be used in all arithmetic operations that any other dense or sparse vector can be used in. The following example gives an impression of the use of dense subvectors within arithmetic operations. All operations (addition, subtraction, multiplication, scaling, ...) can be performed on all possible combinations of dense and sparse subvectors with fitting element types:

```
typedef blaze::DynamicVector<double,blaze::rowVector>     DenseVectorType;
typedef blaze::CompressedVector<double,blaze::rowVector>  SparseVectorType;
DenseVectorType d1, d2, d3;
SparseVectorType s1, s2;

// ... Resizing and initialization

typedef blaze::DynamicMatrix<double,blaze::rowMajor>  DenseMatrixType;
DenseMatrixType A;

typedef blaze::DenseSubvector<DenseVectorType>  SubvectorType;
SubvectorType dsv( subvector( d1, 0UL, 10UL ) );  // View on the range [0..9] of vector d1

dsv = d2;                          // Dense vector initialization of the range [0..9]
subvector( d1, 10UL, 10UL ) = s1;  // Sparse vector initialization of the range [10..19]

d3 = dsv + d2;                           // Dense vector/dense vector addition
s2 = s1 + subvector( d1, 10UL, 10UL );   // Sparse vector/dense vector addition
d2 = dsv * subvector( d1, 20UL, 10UL );  // Component-wise vector multiplication

subvector( d1, 3UL, 4UL ) *= 2.0;      // In-place scaling of the range [3..6]
d2 = subvector( d1, 7UL, 3UL ) * 2.0;  // Scaling of the range [7..9]
d2 = 2.0 * subvector( d1, 7UL, 3UL );  // Scaling of the range [7..9]

subvector( d1, 0UL , 10UL ) += d2;   // Addition assignment
subvector( d1, 10UL, 10UL ) -= s2;   // Subtraction assignment
subvector( d1, 20UL, 10UL ) *= dsv;  // Multiplication assignment

double scalar = subvector( d1, 5UL, 10UL ) * trans( s1 );  // Scalar/dot/inner product between two vectors

A = trans( s1 ) * subvector( d1, 4UL, 16UL );  // Outer product between two vectors
```





---

## Aligned Subvectors ##

Usually subvectors can be defined anywhere within a vector. They may start at any position and may have an arbitrary size (only restricted by the size of the underlying vector). However, in contrast to vectors themselves, which are always properly aligned in memory and therefore can provide maximum performance, this means that subvectors in general have to be considered to be unaligned. This can be made explicit by the `blaze::unaligned` flag:

```
using blaze::unaligned;

typedef blaze::DynamicVector<double,blaze::rowVector>  DenseVectorType;

DenseVectorType x;
// ... Resizing and initialization

// Identical creations of an unaligned subvector in the range [8..23]
blaze::DenseSubvector<DenseVectorType>           sv1 = subvector           ( x, 8UL, 16UL );
blaze::DenseSubvector<DenseVectorType>           sv2 = subvector<unaligned>( x, 8UL, 16UL );
blaze::DenseSubvector<DenseVectorType,unaligned> sv3 = subvector           ( x, 8UL, 16UL );
blaze::DenseSubvector<DenseVectorType,unaligned> sv4 = subvector<unaligned>( x, 8UL, 16UL );
```

All of these calls to the `subvector()` function are identical. Whether the alignment flag is explicitly specified or not, it always returns an unaligned subvector. Whereas this may provide full flexibility in the creation of subvectors, this might result in performance disadvantages in comparison to vector primitives (even in case the specified subvector could be aligned). Whereas vector primitives are guaranteed to be properly aligned and therefore provide maximum performance in all operations, a general view on a vector might not be properly aligned. This may cause a performance penalty on some platforms and/or for some operations.

However, it is also possible to create aligned subvectors. Aligned subvectors are identical to unaligned subvectors in all aspects, except that they may pose additional alignment restrictions and therefore have less flexibility during creation, but don't suffer from performance penalties and provide the same performance as the underlying vector. Aligned subvectors are created by explicitly specifying the blaze::aligned flag:

```
using blaze::aligned;

// Creating an aligned dense subvector in the range [8..23]
blaze::DenseSubvector<DenseVectorType,aligned> sv = subvector<aligned>( x, 8UL, 16UL );
```

The alignment restrictions refer to system dependent address restrictions for the used element type and the available vectorization mode (SSE, AVX, ...). The following source code gives some examples for a double precision dense vector, assuming that AVX is available, which packs 4 `double` values into an intrinsic vector:

```
using blaze::columnVector;

typedef blaze::DynamicVector<double,columnVector>  VectorType;
typedef blaze::DenseSubvector<VectorType,aligned>  SubvectorType;

VectorType d( 17UL );
// ... Resizing and initialization

// OK: Starts at the beginning and the size is a multiple of 4
SubvectorType dsv1 = subvector<aligned>( d, 0UL, 12UL );

// OK: Start index and the size are both a multiple of 4
SubvectorType dsv2 = subvector<aligned>( d, 4UL, 8UL );

// OK: The start index is a multiple of 4 and the subvector includes the last element
SubvectorType dsv3 = subvector<aligned>( d, 8UL, 9UL );

// Error: Start index is not a multiple of 4
SubvectorType dsv4 = subvector<aligned>( d, 5UL, 8UL );

// Error: Size is not a multiple of 4 and the subvector does not include the last element
SubvectorType dsv5 = subvector<aligned>( d, 8UL, 5UL );
```

Note that the discussed alignment restrictions are only valid for aligned dense subvectors. In contrast, aligned sparse subvectors at this time don't pose any additional restrictions. Therefore aligned and unaligned sparse subvectors are truly fully identical. Still, in case the `blaze::aligned` flag is specified during setup, an aligned subvector is created:

```
using blaze::aligned;

typedef blaze::CompressedVector<double,blaze::rowVector>  SparseVectorType;

SparseVectorType x;
// ... Resizing and initialization

// Creating an aligned subvector in the range [8..23]
blaze::SparseSubvector<SparseVectorType,aligned> sv = subvector<aligned>( x, 8UL, 16UL );
```





---

## Subvectors on Subvectors ##

It is also possible to create a subvector view on another subvector. In this context it is important to remember that the type returned by the 'subvector()' function is the same type as the type of the given subvector, not a nested subvector type, since the view on a subvector is just another view on the underlying vector:

```
typedef blaze::DynamicVector<double,blaze::rowVector>  VectorType;
typedef blaze::DenseSubvector<VectorType>              SubvectorType;

VectorType d1;

// ... Resizing and initialization

// Creating a subvector view on the dense vector d1
SubvectorType sv1 = subvector( d1, 5UL, 10UL );

// Creating a subvector view on the dense subvector sv1
SubvectorType sv2 = subvector( sv1, 1UL, 5UL );
```



---

Previous: [Triangular Matrices](Triangular_Matrices.md)  ----  Next: [Submatrices](Submatrices.md)