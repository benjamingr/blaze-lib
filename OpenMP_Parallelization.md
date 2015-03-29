<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the OpenMP-based shared-memory parallelization
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


One of the main motivations of the **Blaze** 1.x releases was to achieve maximum performance on a single CPU core for all possible operations. However, today's CPUs are not single core anymore, but provide several (homogeneous or heterogeneous) compute cores. In order to fully exploit the performance potential of a multicore CPU, computations have to be parallelized across all available cores of a CPU. Therefore, starting with **Blaze** 2.0, the **Blaze** library provides shared memory parallelization with OpenMP.





---

## OpenMP Setup ##

To enable OpenMP-based parallelization, all that needs to be done is to explicitly specify the use of OpenMP on the command line:

```
-fopenmp   // GNU C++ compiler
-openmp    // Intel C++ compiler
/openmp    // Visual Studio
```

This simple action will cause the **Blaze** library to automatically try to run all operations in parallel with the specified number of threads.

In order to enable OpenMP-based parallelization, all that needs to be done is to explicitly specify the use of OpenMP on the command line: `-fopenmp` for the GNU C++ compiler, `-openmp` for the Intel C++ compiler, and `/openmp` for the Visual Studio compiler (for all other compilers, please consult the according documentation). This simple action will cause the **Blaze** library to automatically try to run all operations in parallel with the specified number of threads.

As common for OpenMP, the number of threads can be specified either via an environment variable

```
export OMP_NUM_THREADS=4
```

or via an explicit call to the `omp_set_num_threads()` function:

```
omp_set_num_threads( 4 );
```

Alternatively, the number of threads can also be specified via the `setNumThreads()` function provided by the **Blaze** library:

```
blaze::setNumThreads( 4 );
```

Please note that the **Blaze** library does not limit the available number of threads. Therefore it is in YOUR responsibility to choose an appropriate number of threads. The best performance, though, can be expected if the specified number of threads matches the available number of cores.

In order to query the number of threads used for the parallelization of operations, the `getNumThreads()` function can be used:

```
const size_t threads = blaze::getNumThreads();
```

In the context of OpenMP, the function returns the maximum number of threads OpenMP will use within a parallel region and is therefore equivalent to the `omp_get_max_threads()` function.





---

## OpenMP Configuration ##

Note that **Blaze** is not unconditionally running an operation in parallel. In case **Blaze** deems the parallel execution as counterproductive for the overall performance, the operation is executed serially. One of the main reasons for not executing an operation in parallel is the size of the operands. For instance, a vector addition is only executed in parallel if the size of both vector operands exceeds a certain threshold. Otherwise, the performance could seriously decrease due to the overhead caused by the thread setup. However, in order to be able to adjust the **Blaze** library to a specific system, it is possible to configure these thresholds manually. All shared memory thresholds are contained within the configuration file `./blaze/config/Thresholds.h`.

Please note that these thresholds are highly sensitiv to the used system architecture and the shared memory parallelization technique (see also [C++11 Thread Parallelization](Cpp_Thread_Parallelization.md) and [Boost Thread Parallelization](Boost_Thread_Parallelization.md). Therefore the default values cannot guarantee maximum performance for all possible situations and configurations. They merely provide a reasonable standard for the current CPU generation.





---

## First Touch Policy ##

So far the **Blaze** library does not (yet) automatically initialize dynamic memory according to the first touch principle. Consider for instance the following vector triad example:

```
using blaze::columnVector;

const size_t N( 1000000UL );

blaze::DynamicVector<double,columnVector> a( N ), b( N ), c( N ), d( N );

// Initialization of the vectors b, c, and d
for( size_t i=0UL; i<N; ++i ) {
   b[i] = rand<double>();
   c[i] = rand<double>();
   d[i] = rand<double>();
}

// Performing a vector triad
a = b + c * d;
```

If this code, which is prototypical for many OpenMP applications that have not been optimized for ccNUMA architectures, is run across several locality domains (LD), it will not scale beyond the maximum performance achievable on a single LD if the working set does not fit into the cache. This is because the initialization loop is executed by a single thread, writing to `b`, `c`, and `d` for the first time. Hence, all memory pages belonging to those arrays will be mapped into a single LD.

As mentioned above, this problem can be solved by performing vector initialization in parallel:

```
// ...

// Initialization of the vectors b, c, and d
#pragma omp parallel for
for( size_t i=0UL; i<N; ++i ) {
   b[i] = rand<double>();
   c[i] = rand<double>();
   d[i] = rand<double>();
}

// ...
```

This simple modification makes a huge difference on ccNUMA in memory-bound situations (as for instance in all BLAS level 1 operations and partially BLAS level 2 operations). Therefore, in order to achieve the maximum possible performance, it is imperative to initialize the memory according to the later use of the data structures.





---

## Limitations of the OpenMP Parallelization ##

There are a few important limitations to the current **Blaze** OpenMP parallelization. The first one involves the explicit use of an OpenMP parallel region (see [The Parallel Directive](OpenMP_Parallelization#The_Parallel_Directive.md)), the other one the OpenMP `sections` directive (see [The Sections Directive](OpenMP_Parallelization#The_Sections_Directive.md)).


#### The Parallel Directive ####

In OpenMP threads are explicitly spawned via the an OpenMP parallel directive:

```
// Serial region, executed by a single thread

#pragma omp parallel
{
   // Parallel region, executed by the specified number of threads
}

// Serial region, executed by a single thread
```

Conceptually, the specified number of threads (see [OpenMP Setup](OpenMP_Parallelization#OpenMP_Setup.md)) is created every time a parallel directive is encountered. Therefore, from a performance point of view, it seems to be beneficial to use a single OpenMP parallel directive for several operations:

```
blaze::DynamicVector x, y1, y2;
blaze::DynamicMatrix A, B;

#pragma omp parallel
{
   y1 = A * x;
   y2 = B * x;
}
```

Unfortunately, this optimization approach is not allowed within the **Blaze** library. More explicitly, it is not allowed to put an operation into a parallel region. The reason is that the entire code contained within a parallel region is executed by all threads. Although this appears to just comprise the contained computations, a computation (or more specifically the assignment of an expression to a vector or matrix) can contain additional logic that must not be handled by multiple threads (as for instance memory allocations, setup of temporaries, etc.). Therefore it is not possible to manually start a parallel region for several operations, but **Blaze** will spawn threads automatically, depending on the specifics of the operation at hand and the given operands.


#### The Sections Directive ####

OpenMP provides several work-sharing construct to distribute work among threads. One of these constructs is the `sections` directive:

```
blaze::DynamicVector x, y1, y2;
blaze::DynamicMatrix A, B;

// ... Resizing and initialization

#pragma omp sections
{
#pragma omp section

   y1 = A * x;

#pragma omp section

   y2 = B * x;

}
```

In this example, two threads are used to compute two distinct matrix/vector multiplications concurrently. Thereby each of the `sections` is executed by exactly one thread.

Unfortunately **Blaze** does not support concurrent parallel computations and therefore this approach does not work with the **Blaze** OpenMP parallelization. The OpenMP implementation of **Blaze** is optimized for the parallel computation of an operation within a single thread of execution. This means that **Blaze** tries to use all available OpenMP threads to compute the result of a single operation as efficiently as possible. Therefore, for this special case, it is advisable to disable the **Blaze** OpenMP parallelization and to let **Blaze** compute all operations within a `sections` directive in serial. This can be done by either completely disabling the **Blaze** OpenMP parallelization (see [Serial Execution](Serial_Execution.md)) or by selectively serializing all operations within a `sections` directive via the `serial()` function:

```
blaze::DynamicVector x, y1, y2;
blaze::DynamicMatrix A, B;

// ... Resizing and initialization

#pragma omp sections
{
#pragma omp section

   y1 = serial( A * x );

#pragma omp section

   y2 = serial( B * x );

}
```

Please note that the use of the `BLAZE_SERIAL_SECTION` (see also [Serial Execution](Serial_Execution.md)) does NOT work in this context!





---

## The `sections` Directive ##

OpenMP provides several work-sharing construct to distribute work among threads. One of these constructs is the `sections` directive:

```
blaze::DynamicVector x, y1, y2;
blaze::DynamicMatrix A, B;

// ... Resizing and initialization

#pragma omp sections
{
#pragma omp section

   y1 = A * x;

#pragma omp section

   y2 = B * x;

}
```

In this example, two threads are used to compute two distinct matrix/vector multiplications concurrently. Thereby each of the `sections` is executed by exactly one thread.

Unfortunately **Blaze** does not support concurrent parallel computations and therefore this approach does not work with any of the **Blaze** parallelization techniques. All techniques (including the C++11 and Boost thread parallelizations; see [C++11 Thread Parallelization](Cpp_Thread_Parallelization.md) and [Boost Thread Parallelization](Boost_Thread_Parallelization.md)) are optimized for the parallel computation of an operation within a single thread of execution. This means that **Blaze** tries to use all available threads to compute the result of a single operation as efficiently as possible. Therefore, for this special case, it is advisable to disable all **Blaze** parallelizations and to let **Blaze** compute all operations within a ´sections´ directive in serial. This can be done by either completely disabling the **Blaze** parallelization (see [Serial Execution](Serial_Execution.md)) or by selectively serializing all operations within a `sections` directive via the `serial()` function:

```
blaze::DynamicVector x, y1, y2;
blaze::DynamicMatrix A, B;

// ... Resizing and initialization

#pragma omp sections
{
#pragma omp section

   y1 = serial( A * x );

#pragma omp section

   y2 = serial( B * x );

}
```

Please note that the use of the `BLAZE_SERIAL_SECTION` (see also [Serial Execution](Serial_Execution.md)) does NOT work in this context!



---

Previous: [Matrix/Matrix Multiplication](Matrix_Matrix_Multiplication.md) ---- Next: [C++11 Thread Parallelization](Cpp_Thread_Parallelization.md)