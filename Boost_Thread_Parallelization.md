<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the Boost thread-based shared-memory parallelization
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


The third available shared memory parallelization provided with **Blaze** is based on Boost threads.





---

## Boost Thread Setup ##

In order to enable the Boost thread-based parallelization, two steps have to be taken: First, the `BLAZE_USE_BOOST_THREADS` command line argument has to be explicitly specified during compilation:

```
... -DBLAZE_USE_BOOST_THREADS ...
```

Second, the according Boost libraries have to be linked. These two simple actions will cause the **Blaze** library to automatically try to run all operations in parallel with the specified number of Boost threads. Note that the OpenMP-based and C++11 thread-based parallelizations have priority, i.e. are preferred in case either is enabled in combination with the Boost thread parallelization.

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

In order to query the number of threads used for the parallelization of operations, the `getNumThreads()` function can be used:

```
const size_t threads = blaze::getNumThreads();
```

In the context of Boost threads, the function will return the previously specified number of threads.





---

## Boost Thread Configuration ##

As in case of the other shared memory parallelizations **Blaze** is not unconditionally running an operation in parallel (see [OpenMP Parallelization](OpenMP_Parallelization.md) or [C++11 Thread Parallelization](Cpp_Thread_Parallelization.md)). All thresholds related to the Boost thread parallelization are also contained within the configuration file `./blaze/config/Thresholds.h`.

Please note that these thresholds are highly sensitiv to the used system architecture and the shared memory parallelization technique. Therefore the default values cannot guarantee maximum performance for all possible situations and configurations. They merely provide a reasonable standard for the current CPU generation. Also note that the provided defaults have been determined using the OpenMP parallelization and require individual adaption for the Boost thread parallelization.



---

Previous: [C++11 Thread Parallelization](Cpp_Thread_Parallelization.md) ---- Next: [Serial Execution](Serial_Execution.md)