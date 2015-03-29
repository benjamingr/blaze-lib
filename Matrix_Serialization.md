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


The serialization of matrices works in the same manner as the serialization of vectors. The following example demonstrates the (de-)serialization of dense and sparse matrices:

```
using blaze::rowMajor;
using blaze::columnMajor;

// Serialization of both matrices
{
   blaze::StaticMatrix<double,3UL,5UL,rowMajor> D;
   blaze::CompressedMatrix<int,columnMajor> S;

   // ... Resizing and initialization

   // Creating an archive that writes into a the file "matrices.blaze"
   blaze::Archive<std::ofstream> archive( "matrices.blaze" );

   // Serialization of both matrices into the same archive. Note that D lies before S!
   archive << D << S;
}

// Reconstitution of both matrices
{
   blaze::DynamicMatrix<double,rowMajor> D1;
   blaze::DynamicMatrix<int,rowMajor> D2;

   // Creating an archive that reads from the file "matrices.blaze"
   blaze::Archive<std::ifstream> archive( "matrices.blaze" );

   // Reconstituting the former D matrix into D1. Note that it is possible to reconstitute
   // the matrix into a differrent kind of matrix (StaticMatrix -> DynamicMatrix), but that
   // the type of elements has to be the same.
   archive >> D1;

   // Reconstituting the former S matrix into D2. Note that is is even possible to reconstitute
   // a sparse matrix as a dense matrix (also the reverse is possible) and that a column-major
   // matrix can be reconstituted as row-major matrix (and vice versa). Note however that also
   // in this case the type of elements is the same!
   archive >> D2
}
```

Note that also in case of matrices it is possible to (de-)serialize matrices with vector or matrix elements:

```
// Serialization
{
   blaze::CompressedMatrix< blaze::DynamicMatrix< blaze::complex<double> > > mat;

   // ... Resizing and initialization

   // Creating an archive that writes into a the file "matrix.blaze"
   blaze::Archive<std::ofstream> archive( "matrix.blaze" );

   // Serialization of the matrix into the archive
   archive << mat;
}

// Deserialization
{
   blaze::CompressedMatrix< blaze::DynamicMatrix< blaze::complex<double> > > mat;

   // Creating an archive that reads from the file "matrix.blaze"
   blaze::Archive<std::ifstream> archive( "matrix.blaze" );

   // Reconstitution of the matrix from the archive
   archive >> mat;
}
```

Note that just as the vector serialization, the matrix serialization is restricted by a few important rules:

  * matrices cannot be reconstituted as vectors (and vice versa)
  * the element type of the serialized and reconstituted matrix must match, which means that on the source and destination platform the general type (signed/unsigned integral or floating point) and the size of the type must be exactly the same
  * when reconstituting a StaticMatrix, the number of rows and columns must match those of the serialized matrix

In case an error is encountered during (de-)serialization, a \a std::runtime\_exception is thrown.



---

Previous: [Vector Serialization](Vector_Serialization.md) ---- Next: [Intra-Statement Optimization](Intra_Statement_Optimization.md)