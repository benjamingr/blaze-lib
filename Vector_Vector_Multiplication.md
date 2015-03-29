<a href='Hidden comment: =====================================================================================
#
#  Wiki page for vector/vector multiplications
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


## Componentwise Multiplication ##

Multiplying two vectors with the same transpose flag (i.e. either `blaze::columnVector` or `blaze::rowVector`) via the multiplication operator results in a componentwise multiplication of the two vectors:

```
using blaze::DynamicVector;
using blaze::CompressedVector;

CompressedVector<int,columnVector> v1( 17UL );
DynamicVector<int,columnVector>    v2( 17UL );

StaticVector<double,10UL,rowVector> v3;
DynamicVector<double,rowVector>     v4( 10UL );

// ... Initialization of the vectors

CompressedVector<int,columnVector> v5( v1 * v2 );  // Componentwise multiplication of a dense and a sparse column
                                                   // vector. The result is a sparse column vector.
DynamicVector<double,rowVector>    v6( v3 * v4 );  // Componentwise multiplication of two dense row vectors. The
                                                   // result is a dense row vector.
```





---

## Inner Product / Scalar Product / Dot Product ##

The multiplication between a row vector and a column vector results in an inner product between the two vectors:

```
blaze::StaticVector<int,3UL,rowVector> v1( 2, 5, -1 );

blaze::DynamicVector<int,columnVector> v2( 3UL );
v2[0] = -1;
v2[1] = 3;
v2[2] = -2;

int result = v1 * v2;  // Results in the value 15.
```

The `trans()` function can be used to transpose a vector as necessary:

```
blaze::StaticVector<int,3UL,rowVector> v1( 2, 5, -1 );
blaze::StaticVector<int,3UL,rowVector> v2( -1, 3, -2 );

int result = v1 * trans( v2 );  // Also results in the value 15.
```

Alternatively, the comma operator can used for any combination of vectors (row or column vectors) to perform an inner product:

```
blaze::StaticVector<int,3UL,rowVector> v1(  2, 5, -1 );
blaze::StaticVector<int,3UL,rowVector> v2( -1, 3, -2 );

int result = (v1,v2);  // Inner product between two row vectors
```

Please note the brackets embracing the inner product expression. Due to the low precedence of the comma operator (lower even than the assignment operator) these brackets are strictly required for a correct evaluation of the inner product.





---

## Outer Product ##

The multiplication between a column vector and a row vector results in the outer product of the two vectors:

```
blaze::StaticVector<int,3UL,columnVector> v1( 2, 5, -1 );

blaze::DynamicVector<int,rowVector> v2( 3UL );
v2[0] = -1;
v2[1] = 3;
v2[2] = -2;

StaticMatrix<int,3UL,3UL> M1 = v1 * v2;
```

The `trans()` function can be used to transpose a vector as necessary:

```
blaze::StaticVector<int,3UL,rowVector> v1( 2, 5, -1 );
blaze::StaticVector<int,3UL,rowVector> v2( -1, 3, -2 );

int result = trans( v1 ) * v2;
```





---

## Cross Product ##

Two column vectors can be multiplied via the cross product. The cross product between two vectors `a` and `b` is defined as

![http://wiki.blaze-lib.googlecode.com/git/images/crossProduct.jpg](http://wiki.blaze-lib.googlecode.com/git/images/crossProduct.jpg)

Due to the absence of a `x` operator in the C++ language, the cross product is realized via the modulo operator (i.e. `operator%`):

```
blaze::StaticVector<int,3UL,columnVector> v1( 2, 5, -1 );

blaze::DynamicVector<int,columnVector> v2( 3UL );
v2[0] = -1;
v2[1] = 3;
v2[2] = -2;

blaze::StaticVector<int,3UL,columnVector> v3( v1 % v2 );
```

Please note that the cross product is restricted to three dimensional (dense and sparse) column vectors.



---

Previous: [Scalar\_Multiplication](Scalar_Multiplication.md) ---- Next: [Matrix\_Vector\_Multiplication](Matrix_Vector_Multiplication.md)