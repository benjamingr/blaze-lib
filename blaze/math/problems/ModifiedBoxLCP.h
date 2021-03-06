//=================================================================================================
/*!
//  \file blaze/math/problems/ModifiedBoxLCP.h
//  \brief A data structure for modified box linear complementarity problems
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

#ifndef _BLAZE_MATH_PROBLEMS_MODIFIEDBOXLCP_H_
#define _BLAZE_MATH_PROBLEMS_MODIFIEDBOXLCP_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cmath>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/DynamicVector.h>
#include <blaze/math/Functions.h>
#include <blaze/system/Precision.h>
#include <blaze/util/Types.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief A modified box linear complementarity problem (MBLCP) data structure.
// \ingroup math
//
// The ModifiedBoxLCP class represent a modified box linear complementarity problem (MBLCP) of
// the form

      \f[ A \cdot x + b \leq 0 \quad\perp\quad \underline{x}(x) \leq x \leq \bar{x}(x), \f]

// where \f$ \underline{x}(x) = \underline{x} + \underline{\lambda} + x_{\underline{j}} \f$
// and \f$ \bar{x}(x) = \bar{x} + \bar{\lambda} + x_{\bar{j}} \f$ are the lower and upper
// bound of the BLCP, respectively.
*/
struct ModifiedBoxLCP
{
   //**Utility functions***************************************************************************
   /*!\name Utility functions */
   //@{
   inline size_t size    ()               const;
   inline void   project ( size_t index );
   inline real   lbound  ( size_t index ) const;
   inline real   ubound  ( size_t index ) const;
   inline real   residual( size_t index ) const;
   inline real   residual()               const;
   //@}
   //**********************************************************************************************

   //**Member variables****************************************************************************
   /*!\name Member variables */
   //@{
   CMatMxN A_;          //!< The system matrix \f$ A \f$.
   VecN    b_;          //!< The right-hand side vector \f$ b \f$.
   VecN    x_;          //!< The vector of unknowns \f$ x \f$.
   VecN    xmin_;       //!< The lower bound of the MBLCP \f$ \underline{x} \f$.
   VecN    xmax_;       //!< The upper bound of the MBLCP \f$ \bar{x} \f$.
   VecN    lambdamin_;  //!< The lower bound of the friction coefficients \f$ \underline{\lambda} \f$.
   VecN    lambdamax_;  //!< The upper bound of the friction coefficients \f$ \bar{\lambda} \f$.
   VecN    jmin_;       //!< The lower bound of the index for the vector of unknowns \f$ \underline{j} \f$.
   VecN    jmax_;       //!< The upper bound of the index for the vector of unknowns \f$ \bar{j} \f$.
   //@}
   //**********************************************************************************************
};
//*************************************************************************************************




//=================================================================================================
//
//  UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Returns the size of the MBLCP.
//
// \return The actual size of the MBLCP.
*/
inline size_t ModifiedBoxLCP::size() const
{
   return x_.size();
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Projects the unknown at the given index on the solution range.
//
// \param index Access index. The index has to be in the range \f$ [0..size) \f$.
// \return void
*/
inline void ModifiedBoxLCP::project( size_t index )
{
   x_[index] = min( xmax_[index], max( xmin_[index], x_[index] ) );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Returns the lower bound of the unknown at the given index.
//
// \param index Access index. The index has to be in the range \f$ [0..size) \f$.
// \return void
*/
inline real ModifiedBoxLCP::lbound( size_t index ) const
{
   return ( xmin_[index] + lambdamin_[index] * x_[ jmin_[index] ] );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Returns the upper bound of the unknown at the given index.
//
// \param index Access index. The index has to be in the range \f$ [0..size) \f$.
// \return void
*/
inline real ModifiedBoxLCP::ubound( size_t index ) const
{
   return ( xmax_[index] + lambdamax_[index] * x_[ jmax_[index] ] );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Calculates the residual of the unknown at the given index.
//
// \param index Access index. The index has to be in the range \f$ [0..size) \f$.
// \return The residual at index \a index.
*/
inline real ModifiedBoxLCP::residual( size_t index ) const
{
   // Computing the residual using max( x - xmax, min( x - xmin, Ax+b ) )
   return max( x_[index] - ubound( index ),
               min( x_[index] - lbound( index ), ( A_ * x_ )[index] + b_[index] ) );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Calculates the maximum norm of the residual of the BLCP.
//
// \return The maximum norm of the global residual of the BLCP.
*/
inline real ModifiedBoxLCP::residual() const
{
   real rmax( 0 );

   for( size_t i=0; i<size(); ++i )
      rmax = max( rmax, std::fabs( residual( i ) ) );

   return rmax;
}
//*************************************************************************************************

} // namespace blaze

#endif
