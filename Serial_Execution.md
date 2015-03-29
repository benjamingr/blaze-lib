<a href='Hidden comment: =====================================================================================
#
#  Wiki page for enforced serial execution
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


Sometimes it may be necessary to enforce the serial execution of specific operations. For this purpose, the **Blaze** library offers three possible options: the serialization of a single expression via the `serial()` function, the serialization of a block of expressions via the `BLAZE_SERIAL_SECTION`, and the general deactivation of the parallel execution.


## Option 1: Serialization of a Single Expression ##

The first option is the serialization of a specific operation via the `serial()` function:

```
blaze::DynamicMatrix<double> A, B, C;
// ... Resizing and initialization
C = serial( A + B );
```

`serial()` enforces the serial evaluation of the enclosed expression. It can be used on any kind of dense or sparse vector or matrix expression.


## Option 2: Serialization of Multiple Expressions ##

The second option is the temporary and local enforcement of a serial execution via the `BLAZE_SERIAL_SECTION`:

```
using blaze::rowMajor;
using blaze::columnVector;

blaze::DynamicMatrix<double,rowMajor> A;
blaze::DynamicVector<double,columnVector> b, c, d, x, y, z;

// ... Resizing and initialization

// Parallel execution
// If possible and beneficial for performance the following operation is executed in parallel.
x = A * b;

// Serial execution
// All operations executed within the serial section are guaranteed to be executed in
// serial (even if a parallel execution would be possible and/or beneficial).
BLAZE_SERIAL_SECTION
{
   y = A * c;
   z = A * d;
}

// Parallel execution continued
// ...
```

Within the scope of the `BLAZE_SERIAL_SECTION`, all operations are guaranteed to run in serial. Outside the scope of the serial section, all operations are run in parallel (if beneficial for the performance).

Note that the `BLAZE_SERIAL_SECTION` must only be used within a single thread of execution. The use of the serial section within several concurrent threads will result undefined behavior!


## Option 3: Deactivation of Parallel Execution ##

The third option is the general deactivation of the parallel execution (even in case OpenMP is enabled on the command line). This can be achieved via the `BLAZE_USE_SHARED_MEMORY_PARALLELIZATION` switch in the `./blaze/config/SMP.h` configuration file:

```
#define BLAZE_USE_SHARED_MEMORY_PARALLELIZATION 1
```

In case the `BLAZE_USE_SHARED_MEMORY_PARALLELIZATION` switch is set to 0, the shared-memory parallelization is deactivated altogether.



---

Previous: [Boost Thread Parallelization](Boost_Thread_Parallelization.md) ---- Next: [Vector Serialization](Vector_Serialization.md)