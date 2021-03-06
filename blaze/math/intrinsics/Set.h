//=================================================================================================
/*!
//  \file blaze/math/intrinsics/Set.h
//  \brief Header file for the intrinsic set functionality
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_INTRINSICS_SET_H_
#define _BLAZE_MATH_INTRINSICS_SET_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/intrinsics/BasicTypes.h>
#include <blaze/system/Inline.h>
#include <blaze/system/Vectorization.h>
#include <blaze/util/Assert.h>
#include <blaze/util/constraints/Integral.h>
#include <blaze/util/EnableIf.h>
#include <blaze/util/mpl/And.h>
#include <blaze/util/StaticAssert.h>
#include <blaze/util/Types.h>
#include <blaze/util/typetraits/HasSize.h>
#include <blaze/util/typetraits/IsIntegral.h>


namespace blaze {

//=================================================================================================
//
//  INTRINSIC SET FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Sets all values in the vector to the given 2-byte integral value.
// \ingroup intrinsics
//
// \param value The given 2-byte integral value.
// \return The set vector of 2-byte integral values.
*/
template< typename T >  // Type of the integral value
BLAZE_ALWAYS_INLINE typename EnableIf< And< IsIntegral<T>, HasSize<T,2UL> >, sse_int16_t >::Type
   set( T value )
{
#if BLAZE_AVX2_MODE
   return _mm256_set1_epi16( value );
#elif BLAZE_SSE2_MODE
   return _mm_set1_epi16( value );
#else
   return value;
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Sets all values in the vector to the given 4-byte integral value.
// \ingroup intrinsics
//
// \param value The given 4-byte integral value.
// \return The set vector of 4-byte integral values.
*/
template< typename T >  // Type of the integral value
BLAZE_ALWAYS_INLINE typename EnableIf< And< IsIntegral<T>, HasSize<T,4UL> >, sse_int32_t >::Type
   set( T value )
{
#if BLAZE_MIC_MODE
   return _mm512_set1_epi32( value );
#elif BLAZE_AVX2_MODE
   return _mm256_set1_epi32( value );
#elif BLAZE_SSE2_MODE
   return _mm_set1_epi32( value );
#else
   return value;
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Sets all values in the vector to the given 8-byte integral value.
// \ingroup intrinsics
//
// \param value The given 8-byte integral value.
// \return The set vector of 8-byte integral values.
*/
template< typename T >  // Type of the integral value
BLAZE_ALWAYS_INLINE typename EnableIf< And< IsIntegral<T>, HasSize<T,8UL> >, sse_int64_t >::Type
   set( T value )
{
#if BLAZE_MIC_MODE
   return _mm512_set1_epi64( value );
#elif BLAZE_AVX2_MODE
   return _mm256_set1_epi64x( value );
#elif BLAZE_SSE2_MODE
   return _mm_set1_epi64( value );
#else
   return value;
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Sets all values in the vector to the given 'float' value.
// \ingroup intrinsics
//
// \param value The given 'float' value.
// \return The set vector of 'float' values.
*/
BLAZE_ALWAYS_INLINE sse_float_t set( float value )
{
#if BLAZE_MIC_MODE
   return _mm512_set1_ps( value );
#elif BLAZE_AVX_MODE
   return _mm256_set1_ps( value );
#elif BLAZE_SSE_MODE
   return _mm_set1_ps( value );
#else
   return value;
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Sets all values in the vector to the given 'double' value.
// \ingroup intrinsics
//
// \param value The given 'double' value.
// \return The set vector of 'double' values.
*/
BLAZE_ALWAYS_INLINE sse_double_t set( double value )
{
#if BLAZE_MIC_MODE
   return _mm512_set1_pd( value );
#elif BLAZE_AVX_MODE
   return _mm256_set1_pd( value );
#elif BLAZE_SSE2_MODE
   return _mm_set1_pd( value );
#else
   return value;
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Sets all values in the vector to the given 'complex<float>' value.
// \ingroup intrinsics
//
// \param value The given 'complex<float>' value.
// \return The set vector of 'complex<float>' values.
*/
BLAZE_ALWAYS_INLINE sse_cfloat_t set( const complex<float>& value )
{
#if BLAZE_MIC_MODE
   return _mm512_set_ps( value.imag(), value.real(), value.imag(), value.real(),
                         value.imag(), value.real(), value.imag(), value.real(),
                         value.imag(), value.real(), value.imag(), value.real(),
                         value.imag(), value.real(), value.imag(), value.real() );
#elif BLAZE_AVX_MODE
   return _mm256_set_ps( value.imag(), value.real(), value.imag(), value.real(),
                         value.imag(), value.real(), value.imag(), value.real() );
#elif BLAZE_SSE_MODE
   return _mm_set_ps( value.imag(), value.real(), value.imag(), value.real() );
#else
   return value;
#endif
   BLAZE_STATIC_ASSERT( sizeof( complex<float> ) == 2UL*sizeof( float ) );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Sets all values in the vector to the given 'complex<double>' value.
// \ingroup intrinsics
//
// \param value The given 'complex<double>' value.
// \return The set vector of 'complex<double>' values.
*/
BLAZE_ALWAYS_INLINE sse_cdouble_t set( const complex<double>& value )
{
#if BLAZE_MIC_MODE
   return _mm512_set_pd( value.imag(), value.real(), value.imag(), value.real(),
                         value.imag(), value.real(), value.imag(), value.real() );
#elif BLAZE_AVX_MODE
   return _mm256_set_pd( value.imag(), value.real(), value.imag(), value.real() );
#elif BLAZE_SSE2_MODE
   return _mm_set_pd( value.imag(), value.real() );
#else
   return value;
#endif
   BLAZE_STATIC_ASSERT( sizeof( complex<double> ) == 2UL*sizeof( double ) );
}
//*************************************************************************************************

} // namespace blaze

#endif
