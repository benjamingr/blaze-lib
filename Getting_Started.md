<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the introduction of the Blaze library
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


This short tutorial serves the purpose to give a quick overview of the way mathematical expressions have to be formulated in **Blaze**. Starting with [Vector Types](Vector_Types.md), the following long tutorial covers the most important aspects of the **Blaze** math library.





---

## A First Example ##

**Blaze** is written such that using mathematical expressions is as close to mathematical textbooks as possible and therefore as intuitive as possible. In nearly all cases the seemingly easiest solution is the right solution and most users experience no problems when trying to use **Blaze** in the most natural way. The following example gives a first impression of the formulation of a vector addition in **Blaze**:

```
#include <iostream>
#include <blaze/Math.h>

using blaze::StaticVector;
using blaze::DynamicVector;

// Instantiation of a static 3D column vector. The vector is directly initialized as
//    ( 4 -2  5 )
StaticVector<int,3UL> a( 4, -2, 5 );

// Instantiation of a dynamic 3D column vector. Via the subscript operator the values are set to
//    ( 2  5 -3 )
DynamicVector<int> b( 3UL );
b[0] = 2;
b[1] = 5;
b[2] = -3;

// Adding the vectors a and b
DynamicVector<int> c = a + b;

// Printing the result of the vector addition
std::cout << "c =\n" << c << "\n";
```

Note that the entire **Blaze** math library can be included via the `blaze/Math.h` header file. Alternatively, the entire **Blaze** library, including both the math and the entire utility module, can be included via the `blaze/Blaze.h` header file. Also note that all classes and functions of **Blaze** are contained in the `blaze` namespace.

Assuming that this program resides in a source file called `FirstExample.cpp`, it can be compiled for instance via the GNU C++ compiler:

```
g++ -ansi -O3 -DNDEBUG -mavx -o FirstExample FirstExample.cpp
```

Note the definition of the `NDEBUG` preprocessor symbol. In order to achieve maximum performance, it is necessary to compile the program in release mode, which deactivates all debugging functionality inside **Blaze**. It is also strongly recommended to specify the available architecture specific instruction set (as for instance the AVX instruction set, which if available can be activated via the `-mavx` flag). This allows **Blaze** to optimize computations via vectorization.

When running the resulting executable `FirstExample`, the output of the last line of this small program is

```
c =
6
3
2
```





---

## An Example Involving Matrices ##

Similarly easy and intuitive are expressions involving matrices:

```
#include <blaze/Math.h>

using namespace blaze;

// Instantiating a dynamic 3D column vector
DynamicVector<int> x( 3UL );
x[0] =  4;
x[1] = -1;
x[2] =  3;

// Instantiating a dynamic 2x3 row-major matrix, preinitialized with 0. Via the function call
// operator three values of the matrix are explicitly set to get the matrix
//   ( 1  0  4 )
//   ( 0 -2  0 )
DynamicMatrix<int> A( 2UL, 3UL, 0 );
A(0,0) =  1;
A(0,2) =  4;
A(1,1) = -2;

// Performing a dense matrix/dense vector multiplication
DynamicVector<int> y = A * x;

// Printing the resulting vector
std::cout << "y =\n" << y << "\n";

// Instantiating a static column-major matrix. The matrix is directly initialized as
//   (  3 -1 )
//   (  0  2 )
//   ( -1  0 )
StaticMatrix<int,3UL,2UL,columnMajor> B( 3, 0, -1, -1, 2, 0 );

// Performing a dense matrix/dense matrix multiplication
DynamicMatrix<int> C = A * B;

// Printing the resulting matrix
std::cout << "C =\n" << C << "\n";
```

The output of this program is

```
y =
16
2

C =
( -1 -1 )
(  0  4 )
```





---

## A Complex Example ##

The following example is much more sophisticated. It shows the implementation of the Conjugate Gradient (CG) algorithm (http://en.wikipedia.org/wiki/Conjugate_gradient) by means of the **Blaze** library:

![http://wiki.blaze-lib.googlecode.com/git/images/cg.jpg](http://wiki.blaze-lib.googlecode.com/git/images/cg.jpg)

In this example it is not important to understand the CG algorithm itself, but to see the advantage of the API of the **Blaze** library. In the **Blaze** implementation we will use a sparse matrix/dense vector multiplication for a 2D Poisson equation using NxN unknowns. It becomes apparent that the core of the algorithm is very close to the mathematical formulation and therefore has huge advantages in terms of readability and maintainability, while the performance of the code is close to the expected theoretical peak performance:

```
const size_t NN( N*N );

blaze::CompressedMatrix<double,rowMajor> A( NN, NN );
blaze::DynamicVector<double,columnVector> x( NN, 1.0 ), b( NN, 0.0 ), r( NN ), p( NN ), Ap( NN );
double alpha, beta, delta;

// ... Initializing the sparse matrix A

// Performing the CG algorithm
r = b - A * x;
p = r;
delta = (r,r);

for( size_t iteration=0UL; iteration<iterations; ++iteration )
{
   Ap = A * p;
   alpha = delta / (p,Ap);
   x += alpha * p;
   r -= alpha * Ap;
   beta = (r,r);
   if( std::sqrt( beta ) < 1E-8 ) break;
   p = r + ( beta / delta ) * p;
   delta = beta;
}
```

Hopefully this short tutorial gives a good first impression of how mathematical expressions are formulated with **Blaze**. The following long tutorial, starting with [Vector Types](Vector_Types.md), will cover all aspects of the **Blaze** math library, i.e. it will introduce all vector and matrix types, all possible operations on vectors and matrices, and of course all possible mathematical expressions.



---

Previous: [Configuration and Installation](Configuration_and_Installation.md) ---- Next: [Vector Types](Vector_Types.md)