<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the matrix serialization
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



One of the prime features of the **Blaze** library is the automatic intra-statement optimization. In order to optimize the overall performance of every single statement **Blaze** attempts to rearrange the operands based on their types. For instance, the following addition of dense and sparse vectors

```
blaze::DynamicVector<double> d1, d2, d3;
blaze::CompressedVector<double> s1;

// ... Resizing and initialization

d3 = d1 + s1 + d2;
```

is automatically rearranged and evaluated as

```
// ...
d3 = d1 + d2 + s1;  // <- Note that s1 and d2 have been rearranged
```

This order of operands is highly favorable for the overall performance since the addition of the two dense vectors `d1` and `d2` can be handled much more efficiently in a vectorized fashion.

This intra-statement optimization can have a tremendous effect on the performance of a statement. Consider for instance the following computation:

```
blaze::DynamicMatrix<double> A, B;
blaze::DynamicVector<double> x, y;

// ... Resizing and initialization

y = A * B * x;
```

Since multiplications are evaluated from left to right, this statement would result in a matrix/matrix multiplication, followed by a matrix/vector multiplication. However, if the right subexpression is evaluated first, the performance can be dramatically improved since the matrix/matrix multiplication can be avoided in favor of a second matrix/vector multiplication. The **Blaze** library exploits this by automatically restructuring the expression such that the right multiplication is evaluated first:

```
// ...
y = A * ( B * x );
```

Note however that although this intra-statement optimization may result in a measurable or even significant performance improvement, this behavior may be undesirable for several reasons, for instance because of numerical stability. Therefore, in case the order of evaluation matters, the best solution is to be explicit and to separate a statement into several statements:

```
blaze::DynamicVector<double> d1, d2, d3;
blaze::CompressedVector<double> s1;

// ... Resizing and initialization

d3  = d1 + s1;  // Compute the dense vector/sparse vector addition first ...
d3 += d2;       // ... and afterwards add the second dense vector
```

```
blaze::DynamicMatrix<double> A, B, C;
blaze::DynamicVector<double> x, y;

// ... Resizing and initialization

C = A * B;  // Compute the left-hand side matrix-matrix multiplication first ...
y = C * x;  // ... before the right-hand side matrix-vector multiplication
```

Alternatively, it is also possible to use the `eval()` function to fix the order of evaluation:

```
blaze::DynamicVector<double> d1, d2, d3;
blaze::CompressedVector<double> s1;

// ... Resizing and initialization

d3 = d1 + eval( s1 + d2 );
```

```
blaze::DynamicMatrix<double> A, B;
blaze::DynamicVector<double> x, y;

// ... Resizing and initialization

y = eval( A * B ) * x;
```



---

Previous: [Matrix Serialization](Matrix_Serialization.md) ---- Next: [Configuration Files](Configuration_Files.md)