<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the C++11 thread-based shared-memory parallelization
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


In addition to the OpenMP-based shared memory parallelization, starting with **Blaze** 2.1, **Blaze** also provides a shared memory parallelization based on C++11 threads.





---

## C++11 Thread Setup ##

In order to enable the C++11 thread-based parallelization, first the according C++11-specific compiler flags have to be used and second the `BLAZE_USE_CPP_THREADS` command line argument has to be explicitly specified. For instance, in case of the GNU C++ and Clang compilers the compiler flags have to be extended by

```
... -std=c++11 -DBLAZE_USE_CPP_THREADS ...
```

This simple action will cause the **Blaze** library to automatically try to run all operations in parallel with the specified number of C++11 threads. Note that in case both OpenMP and C++11 threads are enabled on the command line, the OpenMP-based parallelization has priority and is preferred.

The number of threads can be either specified via the environment variable `BLAZE_NUM_THREADS`

```
export BLAZE_NUM_THREADS=4  // Unix systems
set BLAZE_NUM_THREADS=4     // Windows systems
```

or alternatively via the `setNumThreads()` function provided by the **Blaze** library:

```
blaze::setNumThreads( 4 );
```

Please note that the **Blaze** library does not limit the available number of threads. Therefore it is in YOUR responsibility to choose an appropriate number of threads. The best performance, though, can be expected if the specified number of threads matches the available number of cores.

In order to query the number of threads used for the parallelization of operations, the ´getNumThreads()´ function can be used:

```
const size_t threads = blaze::getNumThreads();
```

In the context of C++11 threads, the function will return the previously specified number of threads.





---

## C++11 Thread Configuration ##

As in case of the OpenMP-based parallelization **Blaze** is not unconditionally running an operation in parallel. In case **Blaze** deems the parallel execution as counterproductive for the overall performance, the operation is executed serially. One of the main reasons for not executing an operation in parallel is the size of the operands. For instance, a vector addition is only executed in parallel if the size of both vector operands exceeds a certain threshold. Otherwise, the performance could seriously decrease due to the overhead caused by the thread setup. However, in order to be able to adjust the **Blaze** library to a specific system, it is possible to configure these thresholds manually. All thresholds are contained within the configuration file ´./blaze/config/Thresholds.h´.

Please note that these thresholds are highly sensitiv to the used system architecture and the shared memory parallelization technique. Therefore the default values cannot guarantee maximum performance for all possible situations and configurations. They merely provide a reasonable standard for the current CPU generation. Also note that the provided defaults have been determined using the OpenMP parallelization and require individual adaption for the C++11 thread parallelization.





---

## Known Issues ##

There is a <a href='http://connect.microsoft.com/VisualStudio/feedback/details/747145'>known issue</a> in Visual Studio 2012 and 2013 that may cause C++11 threads to hang if their destructor is executed after the `main()` function. Unfortunately, the C++11 parallelization of the **Blaze** library is affected from this bug. In order to circumvent this problem, **Blaze** provides the `shutDownThreads()` function, which can be used to manually destroy all threads at the end of the `main()` function:

```
int main()
{
   // ... Using the C++11 thread parallelization of Blaze

   shutDownThreads();
}
```

Please note that this function may only be used at the end of the `main()` function. After this function no further computation may be executed! Also note that this function has an effect for Visual Studio compilers only and doesn't need to be used with any other compiler.



---

Previous: [OpenMP Parallelization](OpenMP_Parallelization.md) ---- Next: [Boost Thread Parallelization](Boost_Thread_Parallelization.md)