<a href='Hidden comment: =====================================================================================
#
#  Wiki page for the vector serialization
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


Sometimes it is necessary to store vector and/or matrices on disk, for instance for storing results or for sharing specific setups with other people. The **Blaze** math serialization module provides the according functionality to create platform independent, portable, binary representations of vectors and matrices that can be used to store the **Blaze** data structures without loss of precision and to reliably transfer them from one machine to another.

The following example demonstrates the (de-)serialization of dense and sparse vectors:

```
using blaze::columnVector;
using blaze::rowVector;

// Serialization of both vectors
{
   blaze::StaticVector<double,5UL,rowVector> d;
   blaze::CompressedVector<int,columnVector> s;

   // ... Resizing and initialization

   // Creating an archive that writes into a the file "vectors.blaze"
   blaze::Archive<std::ofstream> archive( "vectors.blaze" );

   // Serialization of both vectors into the same archive. Note that d lies before s!
   archive << d << s;
}

// Reconstitution of both vectors
{
   blaze::DynamicVector<double,rowVector> d1;
   blaze::DynamicVector<int,rowVector> d2;

   // Creating an archive that reads from the file "vectors.blaze"
   blaze::Archive<std::ifstream> archive( "vectors.blaze" );

   // Reconstituting the former d vector into d1. Note that it is possible to reconstitute
   // the vector into a differrent kind of vector (StaticVector -> DynamicVector), but that
   // the type of elements has to be the same.
   archive >> d1;

   // Reconstituting the former s vector into d2. Note that is is even possible to reconstitute
   // a sparse vector as a dense vector (also the reverse is possible) and that a column vector
   // can be reconstituted as row vector (and vice versa). Note however that also in this case
   // the type of elements is the same!
   archive >> d2
}
```

The (de-)serialization of vectors is not restricted to vectors of built-in data type, but can also be used for vectors with vector or matrix element type:

```
// Serialization
{
   blaze::CompressedVector< blaze::DynamicVector< blaze::complex<double> > > vec;

   // ... Resizing and initialization

   // Creating an archive that writes into a the file "vector.blaze"
   blaze::Archive<std::ofstream> archive( "vector.blaze" );

   // Serialization of the vector into the archive
   archive << vec;
}

// Deserialization
{
   blaze::CompressedVector< blaze::DynamicVector< blaze::complex<double> > > vec;

   // Creating an archive that reads from the file "vector.blaze"
   blaze::Archive<std::ifstream> archive( "vector.blaze" );

   // Reconstitution of the vector from the archive
   archive >> vec;
}
```

As the examples demonstrates, the vector serialization offers an enormous flexibility. However, several actions result in errors:

  * vectors cannot be reconstituted as matrices (and vice versa)
  * the element type of the serialized and reconstituted vector must match, which means that on the source and destination platform the general type (signed/unsigned integral or floating point) and the size of the type must be exactly the same
  * when reconstituting a StaticVector, its size must match the size of the serialized vector

In case an error is encountered during (de-)serialization, a \a std::runtime\_exception is thrown.



---

Previous: [Serial Execution](Serial_Execution.md) ---- Next: [Matrix Serialization](Matrix_Serialization.md)