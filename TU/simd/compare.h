/*!
  \file		compare.h
  \author	Toshio UESHIBA
  \brief	SIMDベクトルに対する比較演算の定義
*/
#if !defined(TU_SIMD_COMPARE_H)
#define TU_SIMD_COMPARE_H

#include "TU/simd/vec.h"

namespace TU
{
namespace simd
{
/************************************************************************
*  Compare operators							*
************************************************************************/
template <class T> vec<mask_type<T> >	operator ==(vec<T> x, vec<T> y)	;
template <class T> vec<mask_type<T> >	operator > (vec<T> x, vec<T> y)	;
template <class T> vec<mask_type<T> >	operator < (vec<T> x, vec<T> y)	;
template <class T> vec<mask_type<T> >	operator !=(vec<T> x, vec<T> y)	;
template <class T> vec<mask_type<T> >	operator >=(vec<T> x, vec<T> y)	;
template <class T> vec<mask_type<T> >	operator <=(vec<T> x, vec<T> y)	;
    
}	// namespace simd
}	// namespace TU

#if defined(MMX)
#  include "TU/simd/x86/compare.h"
#elif defined(NEON)
#  include "TU/simd/arm/compare.h"
#endif

#endif	// !TU_SIMD_COMPARE_H
