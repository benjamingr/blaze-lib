<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the matrix types of the Blaze library
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


The **Blaze** library currently offers two dense matrix types ([StaticMatrix](Matrix_Types#StaticMatrix.md) and [DynamicMatrix](Matrix_Types#DynamicMatrix.md)) and one sparse matrix type ([CompressedMatrix](CompressedMatrix.md)). All matrices can either be stored as row-major matrices or column-major matrices. Per default, all matrices in Blaze are row-major matrices.





---

## StaticMatrix ##

The `blaze::StaticMatrix` class template is the representation of a fixed-size matrix with statically allocated elements of arbitrary type. It can be included via the header file

```
#include <blaze/math/StaticMatrix.h>
```

The type of the elements, the number of rows and columns, and the storage order of the matrix can be specified via the four template parameters:

```
template< typename Type, size_t M, size_t N, bool SO >
class StaticMatrix;
```

  * `Type`: specifies the type of the matrix elements. `StaticMatrix` can be used with any non-cv-qualified element type, including vector and other matrix types.
  * `M` : specifies the total number of rows of the matrix.
  * `N` : specifies the total number of columns of the matrix. Note that it is expected that `StaticMatrix` is only used for tiny and small matrices.
  * `SO` : specifies the storage order (`blaze::rowMajor`, `blaze::columnMajor`) of the matrix. The default value is `blaze::rowMajor`.





---

## DynamicMatrix ##

The `blaze::DynamicMatrix` class template is the representation of an arbitrary sized matrix with MxN dynamically allocated elements of arbitrary type. It can be included via the header file

```
#include <blaze/math/DynamicMatrix.h>
```

The type of the elements and the storage order of the matrix can be specified via the two template parameters:

```
template< typename Type, bool SO >
class DynamicMatrix;
```

  * `Type`: specifies the type of the matrix elements. `DynamicMatrix` can be used with any non-cv-qualified element type (even with vector and other matrix types).
  * `SO` : specifies the storage order (`blaze::rowMajor`, `blaze::columnMajor`) of the matrix. The default value is `blaze::rowMajor`.





---

## HybridMatrix ##

The `blaze::HybridMatrix` class template combines the flexibility of a dynamically sized matrix with the efficiency and performance of a fixed-size matrix. It is implemented as a crossing between the `blaze::StaticMatrix` and the `blaze::DynamicMatrix` class templates: Similar to the static matrix it uses static stack memory instead of dynamically allocated memory and similar to the dynamic matrix it can be resized (within the extend of the static memory). It can be included via the header file

```
#include <blaze/math/HybridMatrix.h>
```

The type of the elements, the maximum number of rows and columns and the storage order of the matrix can be specified via the four template parameters:

```
template< typename Type, size_t M, size_t N, bool SO >
class HybridMatrix;
```

  * `Type`: specifies the type of the matrix elements. `HybridMatrix` can be used with any non-cv-qualified, non-reference, non-pointer element type.
  * `M`   : specifies the maximum number of rows of the matrix.
  * `N`   : specifies the maximum number of columns of the matrix. Note that it is expected that `HybridMatrix` is only used for tiny and small matrices.
  * `SO`  : specifies the storage order (`blaze::rowMajor`, `blaze::columnMajor`) of the matrix. The default value is `blaze::rowMajor`.





---

## CompressedMatrix ##

The `blaze::CompressedMatrix` class template is the representation of an arbitrary sized sparse matrix with MxN dynamically allocated elements of arbitrary type. It can be included via the header file

```
#include <blaze/math/CompressedMatrix.h>
```

The type of the elements and the storage order of the matrix can be specified via the two template parameters:

```
template< typename Type, bool SO >
class CompressedMatrix;
```

  * `Type`: specifies the type of the matrix elements. `CompressedMatrix` can be used with any non-cv-qualified element type (including vector and other matrix types).
  * `SO` : specifies the storage order (`blaze::rowMajor`, `blaze::columnMajor`) of the matrix. The default value is `blaze::rowMajor`.



---

Previous: [Vector Operations](Vector_Operations.md) ---- Next: [Matrix Operations](Matrix_Operations.md)