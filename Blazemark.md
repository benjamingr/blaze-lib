<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the Blazemark
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


## Overview ##

  * [Introduction](Blazemark#Introduction.md)
  * [Supported Libraries](Blazemark#Supported_Libraries.md)
  * [Configuration and Compilation](Blazemark#Configuration_and_Compilation.md)
  * [Command Line Parameters](Blazemark#Command_Line_Parameters.md)
  * [Interpreting the Output](Blazemark#Interpreting_the_Output.md)
  * [Available Benchmarks](Blazemark#Available_Benchmarks.md)





---

## Introduction ##

The **Blazemark** is the benchmark suite of the **Blaze** math library. It provides benchmarks for a direct comparison of several (Smart) Expression Template based libraries for various arithmetic operations. Additionally, for some operations, it allows a comparison to "good old" C code and/or C++ operator overloading. The **Blazemark** It is located in the `./blazemark` subdirectory of the **Blaze** library.





---

## Supported Libraries ##

Currently the following libraries are included in the Blazemark:

  * <a href='http://sourceforge.net/projects/blitz/'>Blitz++</a>; Minimum requirement: Version 0.10
  * <a href='http://www.boost.org'>Boost uBLAS</a>; Minimum requirement: Version 1.54
  * <a href='http://download.gna.org/getfem/html/homepage/gmm/index.html'>GMM++</a>; Minimum requirement: Version 4.1
  * <a href='http://arma.sourceforge.net'>Armadillo</a>; Minimum requirement: Version 2.4.2
  * <a href='http://www.simunova.com/de/home'>MTL4</a>; Minimum requirement: Version 4.0
  * <a href='http://eigen.tuxfamily.org'>Eigen3</a>; Minimum requirement: Version 3.1

Additionally, it is possible to include a plain BLAS library in the benchmark (such as for instance the <a href='http://software.intel.com/en-us/articles/intel-mkl/'>Intel MKL</a>, the <a href='http://developer.amd.com/libraries/acml/'>ACML</a>, <a href='http://math-atlas.sourceforge.net'>Atlas</a>, or <a href='http://www.tacc.utexas.edu/tacc-projects/gotoblas2'>Goto</a>).





---

## Configuration and Compilation ##

Just as the **Blaze** library itself, the **Blazemark** is fairly easy to configure and compile. Since currently there is no direct support for Windows available, the following instructions only summarize the necessary steps to configure and compile the **Blazemark** on Linux and MacOSX systems.

The first step is to adapt the `Configfile` of the **Blazemark** home directory (`./blazemark`). In the `Configfile` the necessary parameters for all required libraries (such as Boost) as well as all parameters for the optional libraries (any BLAS library, Blitz++, GMM, Armadillo, MTL4, Eigen3) can be specified. Note that it is also necessary to specifically select a compiler along with a set of suitable compilation flags. It is of highest importance to chose a reasonable set of compilation flags in order to achieve maximum performance of the benchmarked libraries. Assuming a "Sandy Bridge" or "Ivy Bridge" CPU capable of AVX, for the GNU C++ compiler, the following set of compiler flags are recommended:

```
-Wall -Wextra -Werror -Wshadow -Woverloaded-virtual -ansi -O3 -mavx -DNDEBUG -fpermissive
```

In case of the Intel C++ compiler, the following flags are recommended:

```
-Werror -Wshadow -w1 -ansi -O3 -mavx -DNDEBUG -inline-level=2 -finline -fbuiltin
```

Any text editor can be used to adapt the `Configfile`:

```
vi ./Configfile
```

The next step is the execution of the `configure` script. It uses the `Configfile` to create a `Makefile` and to adapt several header files required for the compilation process:

```
./configure
```

Alternatively it is also possible to specify a specific configuration file, which for instance enables different configurations:

```
./configure my_configuration
```

In order to compile the complete benchmark suite, the `Makefile` can be used:

```
make
```

Due to the large number of available benchmarks, this process will take several minutes. Alternatively, a specific benchmark can be build (for instance the sparse matrix/dense vector multiplication; for a complete list of all available benchmarks see the [last](Blazemark#Available_Benchmarks.md) section in this wiki):

```
make smatdvecmult
```

The resulting executable benchmark is located in the `./blazemark/bin` subdirectory. Before executing the benchmark, the size of the vectors and/or matrices involved in the benchmark can be specified via the according parameter file in the `./blazemark/params` subdirectory. Again, any text editor can be used for this task:

```
vi ./params/smatdvecmult.prm
```

Follow the instructions contained in the file to properly configure the parameters for the benchmark. After that, the benchmark can be started by simply calling the executable:

```
./bin/smatdvecmult
```





---

## Command Line Parameters ##

Each benchmark executable offers the possibility to activate or deactivate specific kernels/libraries via the command line. Per default, all kernels/libraries for a particular benchmark are executed (which can be set in the `./blazemark/config/Config.h` header file). However, via the following command line arguments the kernels can be activated very flexibly:

  * **`-clike`**: Activates the C-like kernel.
  * **`-classic`**: Activates the classic C++ kernel.
  * **`-blas`**: Activates the plain BLAS kernel.
  * **`-blaze`**: Activates the Blaze kernel.
  * **`-boost`**: Activates the Boost uBLAS kernel.
  * **`-blitz`**: Activates the Blitz++ kernel.
  * **`-gmm`**: Activates the GMM++ kernel.
  * **`-armadillo`**: Activates the Armadillo kernel.
  * **`-mtl`**: Activates the MTL kernel.
  * **`-eigen`**: Activates the Eigen kernel.

Additionally, these command line arguments can be prefixed with the `-no` or `-only` command:

  * **`-no`**: Deactivates the according kernel.
  * **`-only`**: Deactivates all other kernels except the given one. Since the command line arguments are evaluated from left to right, all succeeding activation commands will activate the according kernels.

The following two examples illustrate the use of these command. The call

```
./bin/smatdvecmult -no-boost
```

runs the sparse row-major matrix/dense column vector multiplication benchmark using all available libraries except the Boost uBLAS library, since the `-no-boost` command specifically deactivates the Boost kernel. The call

```
./bin/smatdvecmult -only-blaze -eigen
```

runs the multiplication with only the **Blaze** and the Eigen libraries, since the `-only-blaze`command deactivates all kernels except **Blaze** and the succeeding `-eigen` command re-activates the Eigen kernel.

Note that not all libraries support every operation. If no kernel exists for a certain library for a particular benchmark the command line argument is without effect.





---

## Interpreting the Output ##

The following example show the output of the dense vector/dense vector addition benchmark, which was run for vectors of size 100 and 10000000:

```
 Dense Vector/Dense Vector Addition:
   C-like implementation [MFlop/s]:
     100         1115.44
     10000000    206.317
   Classic operator overloading [MFlop/s]:
     100         415.703
     10000000    112.557
   Blaze [MFlop/s]:
     100         2602.56
     10000000    292.569
   Boost uBLAS [MFlop/s]:
     100         1056.75
     10000000    208.639
   Blitz++ [MFlop/s]:
     100         1011.1
     10000000    207.855
   GMM++ [MFlop/s]:
     100         1115.42
     10000000    207.699
   Armadillo [MFlop/s]:
     100         1095.86
     10000000    208.658
   MTL [MFlop/s]:
     100         1018.47
     10000000    209.065
   Eigen [MFlop/s]:
     100         2173.48
     10000000    209.899
   N=100, steps=55116257
     C-like      = 2.33322  (4.94123)
     Classic     = 6.26062  (13.2586)
     Blaze       = 1        (2.11777)
     Boost uBLAS = 2.4628   (5.21565)
     Blitz++     = 2.57398  (5.4511)
     GMM++       = 2.33325  (4.94129)
     Armadillo   = 2.3749   (5.0295)
     MTL         = 2.55537  (5.41168)
     Eigen       = 1.19742  (2.53585)
   N=10000000, steps=8
     C-like      = 1.41805  (0.387753)
     Classic     = 2.5993   (0.710753)
     Blaze       = 1        (0.27344)
     Boost uBLAS = 1.40227  (0.383437)
     Blitz++     = 1.40756  (0.384884)
     GMM++       = 1.40862  (0.385172)
     Armadillo   = 1.40215  (0.383403)
     MTL         = 1.39941  (0.382656)
     Eigen       = 1.39386  (0.381136)
```

The first section presents the individual results of each library in MFlop/s. The competitors in this benchmarks are a plain C-like implementation, classical C++ operator overloading, the Blaze library, the Boost uBLAS library, Blitz++, GMM++, Armadillo, MTL, and Eigen.

The second section compares the libraries for each specified vector size. The first line shows the size of the vectors and the number of iteration steps used for the benchmark. After that the libraries are listed. The first number represents a factor of how much slower the library was than the fastest competitor; a number of 1 therefore represents the fastest competitor. The number in brackets is the runtime spend in the benchmark.





---

## Available Benchmarks ##

Due to the high number of possible operations and thus also benchmarks, the names of the benchmarks and executables are assembled from abbreviations for the involved left and right operands:

  * **Vectors**:
    * **dvec**: Dense column vector
    * **tdvec**: Dense row vector
    * **vec3**: Dense 3D column vector
    * **tvec3**: Dense 3D row vector
    * **vec6**: Dense 6D column vector
    * **tvec6**: Dense 6D row vector
    * **svec**: Sparse column vector
    * **tsvec**: Sparse row vector

  * **Matrices**:
    * **dmat**: Dense row-major matrix
    * **tdmat**: Dense column-major matrix
    * **mat3**: Dense 3x3 row-major matrix
    * **tmat3**: Dense 3x3 column-major matrix
    * **mat6**: Dense 6x6 row-major matrix
    * **tmat6**: Dense 6x6 column-major matrix
    * **smat**: Sparse row-major matrix
    * **tsmat**: Sparse column-major matrix

For instance, the `tdvecsmatmult` benchmark represents the multiplication between a dense row vector with a row-major sparse matrix.

The following is a complete list of all available benchmarks, listed in alphabetical order:

![http://wiki.blaze-lib.googlecode.com/git/images/blazemark.jpg](http://wiki.blaze-lib.googlecode.com/git/images/blazemark.jpg)