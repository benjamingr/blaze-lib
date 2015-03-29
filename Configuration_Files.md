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



Sometimes it might necessary to adapt **Blaze** to specific requirements. For this purpose **Blaze** provides several configuration files in the `./blaze/config/` subdirectory, which provide ample opportunity to customize internal settings, behavior, and thresholds. This chapter explains the most important of these configuration files.





---

## Default Vector Storage ##

The **Blaze** default is that all vectors are created as column vectors (if not specified explicitly):

```
blaze::StaticVector<double,3UL> x;  // Creates a 3-dimensional static column vector
```

The header file `./blaze/config/TransposeFlag.h` allows the configuration of the default vector storage (i.e. the default transpose flag of the vectors). Via the `defaultTransposeFlag` value the default transpose flag for all vector of the **Blaze** library can be specified:

```
const bool defaultTransposeFlag = columnVector;
```

Valid settings for the `defaultTransposeFlag` are `blaze::rowVector` and `blaze::columnVector`.





---

## Default Matrix Storage ##

Matrices are by default created as row-major matrices:

```
blaze::StaticMatrix<double,3UL,3UL>  A;  // Creates a 3x3 row-major matrix
```

The header file `./blaze/config/StorageOrder.h` allows the configuration of the default matrix storage order. Via the `defaultStorageOrder` value the default storage order for all matrices of the **Blaze** library can be specified.

```
const bool defaultStorageOrder = rowMajor;
```

Valid settings for the `defaultStorageOrder` are `blaze::rowMajor` and `blaze::columnMajor`.





---

## Vectorization ##

In order to achieve maximum performance and to exploit the compute power of a target platform the **Blaze** library attempts to vectorize all linear algebra operations by SSE, AVX, and/or MIC intrinsics, depending on which instruction set is available. However, it is possible to disable the vectorization entirely by the compile time switch in the configuration file `./blaze/config/Vectorization.h`:

```
#define BLAZE_USE_VECTORIZATION 1
```

In case the switch is set to 1, vectorization is enabled and the **Blaze** library is allowed to use intrinsics to speed up computations. In case the switch is set to 0, vectorization is disabled entirely and the **Blaze** library chooses default, non-vectorized functionality for the operations. Note that deactivating the vectorization may pose a severe performance limitation for a large number of operations!





---

## Thresholds ##

**Blaze** provides several thresholds that can be adapted to the characteristics of the target platform. For instance, the `DMATDVECMULT_THRESHOLD` specifies the threshold between the application of the custom Blaze kernels for small dense matrix/dense vector multiplications and the BLAS kernels for large multiplications. All thresholds are contained within the configuration file `./blaze/config/Thresholds.h`.





---

## Streaming (Non-Temporal Stores) ##

For vectors and matrices that don't fit into the cache anymore non-temporal stores can provide a significant performance advantage of about 20%. However, this advantage is only in effect in case the memory bandwidth of the target architecture is maxed out. If the target architecture's memory bandwidth cannot be exhausted the use of non-temporal stores can decrease performance instead of increasing it.

The configuration file `./blaze/config/Streaming.h` provides a compile time switch that can be used to (de-)activate streaming:

```
const bool useStreaming = true;
```

If `useStreaming` is set to `true` streaming is enabled, if it is set to `false` streaming is disabled. It is recommended to consult the target architecture's white papers to decide whether streaming is beneficial or hurtful for performance.



---

Previous: [Intra-Statement Optimization](Intra_Statement_Optimization.md)