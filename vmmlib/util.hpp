/*
 * Copyright (c) 2006-2016, Visualization and Multimedia Lab,
 *                          University of Zurich <http://vmml.ifi.uzh.ch>,
 *                          Eyescale Software GmbH,
 *                          Blue Brain Project, EPFL
 *
 * This file is part of VMMLib <https://github.com/VMML/vmmlib/>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.  Redistributions in binary
 * form must reproduce the above copyright notice, this list of conditions and
 * the following disclaimer in the documentation and/or other materials provided
 * with the distribution.  Neither the name of the Visualization and Multimedia
 * Lab, University of Zurich nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __VMML__UTIL__HPP__
#define __VMML__UTIL__HPP__

#include "vector.hpp"
#include "matrix.hpp"

#include <algorithm>
#include <limits>
#include <cstdlib>

namespace vmml
{

#define M_PI_F		3.14159265358979323846f
#define M_PI_2_F	1.57079632679489661923f
#define M_PI_3_F	1.04719755119659774615f
#define M_PI_4_F	0.78539816339744830962f


template< typename T, typename U > bool equals( T arg0, U arg1)
{
    return std::abs( arg0 - arg1 ) < std::numeric_limits< float >::epsilon();
}


// matrix convenience functions


template< size_t M, size_t N, typename T >
inline matrix< M, N, T >
create_translation( const vector< M - 1, T > &arg )
{
	matrix< M, N, T > ret;
	identity( ret );
	ret.set_translation( arg );

	return ret;
}

template< typename T >
inline matrix< 4, 4, T >
create_translation( const vector< 3, T > &arg )
{
   return create_translation< 4, 4 >(arg);
}

template< size_t M, size_t N, typename T >
inline void
apply_translation( matrix< M, N, T > &m, T t0, T t1, T t2 )
{
    m *= create_translation< M, N, T >( vector< M - 1, T >( t0, t1, t2 ) );
}

template< size_t M, size_t N, typename T >
inline matrix< M, N, T >
create_rotation( T angle, const vector< M - 1, T > &axis )
{
	matrix< M, N, T > ret;
	identity( ret );
	ret.rotate( angle, axis );

	return ret;
}

template< typename T >
inline matrix< 4, 4, T >
create_rotation( T angle, const vector< 3, T > &axis )
{
    return create_rotation< 4, 4 >( angle, axis );
}

template< size_t M, size_t N, typename T >
inline void
apply_rotation( matrix< M, N, T > &m, T angle, T t0, T t1, T t2 )
{
    m *= create_rotation< M, N, T >( angle, vector< M - 1, T >( t0, t1, t2 ) );
}

template< size_t M, size_t N, typename T >
inline matrix< M, N, T >
create_scaling( const vector< N - 1, T > &arg )
{
    matrix< M, N, T > ret;
    identity(ret);
    ret.scale(arg);

    return ret;
}

template< typename T >
inline matrix< 4, 4, T >
const
create_scaling( const vector< 3, T > &arg )
{
    return create_scaling< 4, 4 >(arg);
}

template< typename T >
inline matrix< 4, 4, T >
create_scaling( T arg )
{
    return create_scaling< 4, 4 >( vector< 3, T >( arg ) );
}


// vector convenience functions


template< size_t M, typename T >
inline void zero( vector< M, T > &arg )
{
	std::fill( arg.begin(), arg.end(), 0 );
}

template< size_t M, typename T >
vector< M, T > min( const vector< M, T > &arg0,  const vector< M, T > &arg1 )
{
	vector< M, T > ret;

	for( size_t i = 0; i < M; ++i )
        ret[i] = std::min( arg0[i], arg1[i] );

	return ret;
}

template< size_t M, typename T >
vector< M, T > max( const vector< M, T > &arg0,  const vector< M, T > &arg1 )
{
	vector< M, T > ret;

	for( size_t i = 0; i < M; ++i )
        ret[i] = std::max( arg0[i], arg1[i] );

	return ret;
}

template< size_t M, typename T >
T
manhattan( const vector< M, T > &arg )
{
	T ret = 0;
	for( size_t i = 0; i < M; ++i )
	{
		ret += std::abs(arg[i]);
	}

	return ret;
}

} // namespace vmml

#endif
