<a href='Hidden comment: =====================================================================================
#
#  Wiki page for matrix/vector multiplications
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


In **Blaze** matrix/vector multiplications can be as intuitively formulated as in mathematical textbooks. Just as in textbooks there are two different multiplications between a matrix and a vector: a matrix/column vector multiplication and a row vector/matrix multiplication:

```
using blaze::StaticVector;
using blaze::DynamicVector;
using blaze::DynamicMatrix;

DynamicMatrix<int> M1( 39UL, 12UL );
StaticVector<int,12UL,columnVector> v1;

// ... Initialization of the matrix and the vector

DynamicVector<int,columnVector> v2 = M1 * v1;           // Matrix/column vector multiplication
DynamicVector<int,rowVector>    v3 = trans( v1 ) * M1;  // Row vector/matrix multiplication
```

Note that the storage order of the matrix poses no restrictions on the operation. Also note, that the highest performance for a multiplication between a dense matrix and a dense vector can be achieved if both the matrix and the vector have the same scalar element type.



---

Previous: [Vector/Vector Multiplication](Vector_Vector_Multiplication.md) ---- Next: [Matrix/Matrix Multiplication](Matrix_Matrix_Multiplication.md)