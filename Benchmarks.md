<a href='Hidden comment: =====================================================================================
#
#  Wiki page for benchmark results
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


The following selected benchmarks give an impression of the single and multi core performance of the **Blaze** library. In the single core benchmarks, **Blaze** is compared to the following third party libraries:

  * <a href='http://sourceforge.net/projects/blitz/'>Blitz++</a>, version 0.10
  * <a href='http://www.boost.org'>Boost uBLAS</a>, version 1.54
  * <a href='http://download.gna.org/getfem/html/homepage/gmm/index.html'>GMM++</a>, version 4.2
  * <a href='http://arma.sourceforge.net'>Armadillo</a>, version 3.920.2
  * <a href='http://www.simunova.com/de/home'>MTL4</a>, version 4.0.9486
  * <a href='http://eigen.tuxfamily.org'>Eigen3</a>, version 3.2
  * <a href='http://software.intel.com/en-us/articles/intel-mkl/'>Intel MKL</a>, version 11.0 (update 5)

The benchmark system is an **Intel Xeon E5-2660 ("Ivy Bridge") CPU at 2.2 GHz** base frequency with 25.6 MByte of shared L3 cache. Due to the “Turbo Mode” feature the processor can increase the clock speed depending on load and temperature. In order to produce reliable single core results, we turned of the “Turbo Mode” and fixed the clock speed at 2.2 GHz.

The maximum achievable memory bandwidth (as measured by the STREAM benchmark) is about 43 GByte/s. Each core has a theoretical peak performance of eight flops per cycle in double precision (DP) using AVX (“Advanced Vector Extensions”) vector instructions. A single core of the Xeon CPU can execute one AVX add and one AVX multiply operation per cycle. Full in-cache performance can only be achieved with SIMD-vectorized code. This includes loads and stores, which exist in full-width (AVX) vectorized, half-width (SSE) vectorized, and “scalar” variants. A maximum of one 256-bit wide AVX load and one 128-bit wide store can be sustained per cycle. 256-bit wide AVX stores thus have a two cycle throughput.

The **GNU g++ 4.8.1** compiler was used with the following compiler flags:

```
g++ -Wall -Wshadow -Woverloaded-virtual -ansi -pedantic -O3 -mavx -DNDEBUG -DMTL_HAS_BLAS ...
```

All libraries are benchmarked as given, but configured such that maximum performance can be achieved. We only show double precision results in MFlop/s graphs for each test case. For all in-cache benchmarks we make sure that the data has already been loaded to the cache.

Please note that due to the continued development for all libraries the performance results are subject to change. Also note that the used releases of all libraries may not be the most recent ones. We are currently updating the results with the newest releases of all libraries.





---

## Dense Vector Addition ##

```
blaze::DynamicVector<double> a( N ), b( N ), c( N );
// ... Initialization of the vectors
c = a + b;
```

#### Single Thread Results ####
![http://wiki.blaze-lib.googlecode.com/git/images/dvecdvecadd.jpg](http://wiki.blaze-lib.googlecode.com/git/images/dvecdvecadd.jpg)

#### Multi Thread Results (OpenMP) ####
![http://wiki.blaze-lib.googlecode.com/git/images/dvecdvecadd-openmp.jpg](http://wiki.blaze-lib.googlecode.com/git/images/dvecdvecadd-openmp.jpg)





---

## Daxpy ##

```
blaze::DynamicVector<double> a( N ), b( N );
// ... Initialization of the vectors
b += a * 0.001;
```

#### Single Thread Results ####
![http://wiki.blaze-lib.googlecode.com/git/images/daxpy.jpg](http://wiki.blaze-lib.googlecode.com/git/images/daxpy.jpg)

#### Multi Thread Results (OpenMP) ####
![http://wiki.blaze-lib.googlecode.com/git/images/daxpy-openmp.jpg](http://wiki.blaze-lib.googlecode.com/git/images/daxpy-openmp.jpg)





---

## Row-major Dense Matrix/Vector Multiplication ##

```
blaze::DynamicMatrix<double,rowMajor> A( N, N );
blaze::DynamicVector<double> a, b;
// ... Initialization of the matrix and the vector a
b = A * a;
```

#### Single Thread Results ####
![http://wiki.blaze-lib.googlecode.com/git/images/dmatdvecmult.jpg](http://wiki.blaze-lib.googlecode.com/git/images/dmatdvecmult.jpg)

#### Multi Thread Results (OpenMP) ####
![http://wiki.blaze-lib.googlecode.com/git/images/dmatdvecmult-openmp.jpg](http://wiki.blaze-lib.googlecode.com/git/images/dmatdvecmult-openmp.jpg)





---

## Column-major Dense Matrix/Vector Multiplication ##

```
blaze::DynamicMatrix<double,columnMajor> A( N, N );
blaze::DynamicVector<double> a, b;
// ... Initialization of the matrix and the vector a
b = A * a;
```

#### Single Thread Results ####
![http://wiki.blaze-lib.googlecode.com/git/images/tdmatdvecmult.jpg](http://wiki.blaze-lib.googlecode.com/git/images/tdmatdvecmult.jpg)

#### Multi Thread Results (OpenMP) ####
![http://wiki.blaze-lib.googlecode.com/git/images/tdmatdvecmult-openmp.jpg](http://wiki.blaze-lib.googlecode.com/git/images/tdmatdvecmult-openmp.jpg)





---

## Row-major Matrix/Matrix Multiplication ##

```
blaze::DynamicMatrix<double,rowMajor> A( N, N ), B( N, N ), C( N, N );
// ... Initialization of the matrices
C = A * B;
```

#### Single Thread Results ####
![http://wiki.blaze-lib.googlecode.com/git/images/dmatdmatmult.jpg](http://wiki.blaze-lib.googlecode.com/git/images/dmatdmatmult.jpg)

#### Multi Thread Results (OpenMP) ####
![http://wiki.blaze-lib.googlecode.com/git/images/dmatdmatmult-openmp.jpg](http://wiki.blaze-lib.googlecode.com/git/images/dmatdmatmult-openmp.jpg)





---

## Column-major Matrix/Matrix Multiplication ##

```
blaze::DynamicMatrix<double,columnMajor> A( N, N ), B( N, N ), C( N, N );
// ... Initialization of the matrices
C = A * B;
```

#### Single Thread Results ####
![http://wiki.blaze-lib.googlecode.com/git/images/tdmattdmatmult.jpg](http://wiki.blaze-lib.googlecode.com/git/images/tdmattdmatmult.jpg)

#### Multi Thread Results (OpenMP) ####
![http://wiki.blaze-lib.googlecode.com/git/images/tdmattdmatmult-openmp.jpg](http://wiki.blaze-lib.googlecode.com/git/images/tdmattdmatmult-openmp.jpg)