<a href='Hidden comment: =====================================================================================
#
#  Wiki page for subtraction operations
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


The subtraction of vectors and matrices works exactly as intuitive as the addition, but with the subtraction operator. For both the vector subtraction as well as the matrix subtraction the subtraction operator can be used. It also enables the subtraction of dense and sparse vectors as well as the subtraction of dense and sparse matrices:

```
blaze::DynamicVector<int> v1( 5UL ), v3;
blaze::CompressedVector<float> v2( 5UL );

// ... Initializing the vectors

v3 = v1 - v2;  // Subtraction of a two column vectors of different data type
```

```
blaze::DynamicMatrix<float,rowMajor> M1( 7UL, 3UL );
blaze::CompressedMatrix<size_t,columnMajor> M2( 7UL, 3UL ), M3;

// ... Initializing the matrices

M3 = M1 - M2;  // Subtraction of a row-major and a column-major matrix of different data type
```

Note that it is necessary that both operands have exactly the same dimensions. Violating this precondition results in an exception. Also note that in case of vectors it is only possible to subtract vectors with the same transpose flag:

```
blaze::DynamicVector<int,columnVector> v1( 5UL );
blaze::CompressedVector<float,rowVector> v2( 5UL );

v1 - v2;           // Compilation error: Cannot subtract a row vector from a column vector
v1 - trans( v2 );  // OK: Subtraction of two column vectors
```

In case of matrices, however, it is possible to subtract row-major and column-major matrices. Note however that in favor of performance the subtraction of two matrices with the same storage order is favorable. The same argument holds for the element type: In case two vectors or matrices with the same element type are added, the performance can be much higher due to vectorization of the operation.

```
blaze::DynamicVector<double>v1( 100UL ), v2( 100UL ), v3;

// ... Initialization of the vectors

v3 = v1 - v2;  // Vectorized subtraction of two double precision vectors
```

```
blaze::DynamicMatrix<float> M1( 50UL, 70UL ), M2( 50UL, 70UL ), M3;

// ... Initialization of the matrices

M3 = M1 - M2;  // Vectorized subtraction of two row-major, single precision dense matrices
```



---

Previous: [Addition](Addition.md) ---- Next: [Scalar Multiplication](Scalar_Multiplication.md)