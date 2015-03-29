<a href='Hidden comment: =====================================================================================
#
#  Wiki page for scalar multiplications
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


The scalar multiplication is the multiplication of a scalar value with a vector or a matrix. In **Blaze** it is possible to use all built-in/fundamental data types except bool as scalar values. Additionally, it is possible to use `std::complex` values with the same built-in data types as element type.

```
blaze::StaticVector<int,3UL> v1( 1, 2, 3 );

blaze::DynamicVector<double>   v2 = v1 * 1.2;
blaze::CompressedVector<float> v3 = -0.3F * v1;
```

```
blaze::StaticMatrix<int,3UL,2UL> M1( 1, 2, 3, 4, 5, 6 );

blaze::DynamicMatrix<double>   M2 = M1 * 1.2;
blaze::CompressedMatrix<float> M3 = -0.3F * M1;
```

Vectors and matrices cannot be used for as scalar value for scalar multiplications (see the following example). However, each vector and matrix provides the `scale()` function, which can be used to scale a vector or matrix element-wise with arbitrary scalar data types:

```
blaze::CompressedMatrix< blaze::StaticMatrix<int,3UL,3UL> > M1;
blaze::StaticMatrix<int,3UL,3UL> scalar;

M1 * scalar;  // No scalar multiplication, but matrix/matrix multiplication

M1.scale( scalar );  // Scalar multiplication
```



---

Previous: [Subtraction](Subtraction.md) ---- Next: [Vector/Vector Multiplication](Vector_Vector_Multiplication.md)