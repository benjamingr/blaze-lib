<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the vector types of the Blaze library
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


The **Blaze** library currently offers three dense vector types ([StaticVector](Vector_Types#StaticVector.md), [DynamicVector](Vector_Types#DynamicVector.md) and [HybridVector](Vector_Types#HybridVector.md)) and one sparse vector type ([CompressedVector](Vector_Types#CompressedVector.md)). All vectors can be specified as either column vectors or row vectors. Per default, all vectors in **Blaze** are column vectors.





---

## StaticVector ##

The `blaze::StaticVector` class template is the representation of a fixed-size vector with statically allocated elements of arbitrary type. It can be included via the header file

```
#include <blaze/math/StaticVector.h>
```

The type of the elements, the number of elements, and the transpose flag of the vector can be specified via the three template parameters:

```
template< typename Type, size_t N, bool TF >
class StaticVector;
```

  * `Type`: specifies the type of the vector elements. `StaticVector` can be used with any non-cv-qualified element type, even including other vector or matrix types.
  * `N` : specifies the total number of vector elements. It is expected that `StaticVector` is only used for tiny and small vectors.
  * `TF` : specifies whether the vector is a row vector (`blaze::rowVector`) or a column vector (`blaze::columnVector`). The default value is `blaze::columnVector`.





---

## DynamicVector ##

The `blaze::DynamicVector` class template is the representation of an arbitrary sized vector with dynamically allocated elements of arbitrary type. It can be included via the header file

```
#include <blaze/math/DynamicVector.h>
```

The type of the elements and the transpose flag of the vector can be specified via the two template parameters:

```
template< typename Type, bool TF >
class DynamicVector;
```

  * `Type`: specifies the type of the vector elements. `DynamicVector` can be used with any non-cv-qualified element type, even other vector or matrix types.
  * `TF` : specifies whether the vector is a row vector (`blaze::rowVector`) or a column vector (`blaze::columnVector`). The default value is `blaze::columnVector`.





---

## HybridVector ##

The `blaze::HybridVector` class template combines the advantages of the `blaze::StaticVector` and the `blaze::DynamicVector` class templates. It represents a fixed-size vector with statically allocated elements, but still can be dynamically resized (within the bounds of the available memory). It can be included via the header file

```
#include <blaze/math/HybridVector.h>
```

The type of the elements, the number of elements, and the transpose flag of the vector can be specified via the three template parameters:

```
template< typename Type, size_t N, bool TF >
class HybridVector;
```

  * `Type`: specifies the type of the vector elements. `HybridVector` can be used with any non-cv-qualified element type, even including other vector or matrix types.
  * `N` : specifies the total number of vector elements. It is expected that `HybridVector` is only used for tiny and small vectors.
  * `TF` : specifies whether the vector is a row vector (`blaze::rowVector`) or a column vector (`blaze::columnVector`). The default value is `blaze::columnVector`.





---

## CompressedVector ##

The `blaze::CompressedVector` class is the representation of an arbitrarily sized sparse vector, which stores only non-zero elements of arbitrary type. It can be included via the header file

```
#include <blaze/math/CompressedVector.h>
```

The type of the elements and the transpose flag of the vector can be specified via the two template parameters:

```
template< typename Type, bool TF >
class CompressedVector;
```

  * `Type`: specifies the type of the vector elements. `CompressedVector` can be used with any non-cv-qualified element type (including other vector or matrix types).
  * `TF` : specifies whether the vector is a row vector (`blaze::rowVector`) or a column vector (`blaze::columnVector`). The default value is `blaze::columnVector`.



---

Previous: [Getting Started](Getting_Started.md)  ----  Next: [Vector Operations](Vector_Operations.md)