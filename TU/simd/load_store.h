/*!
  \file		load_store.h
  \author	Toshio UESHIBA
  \brief	メモリとSIMDベクトル間のデータ転送を行う関数の定義
*/
#if !defined(TU_SIMD_LOAD_STORE_H)
#define TU_SIMD_LOAD_STORE_H

#include <memory>
#include "TU/simd/vec.h"

namespace std
{
#if !defined(__clang__) && (__GNUG__ <= 4)
inline void*
align(std::size_t alignment,
      std::size_t size, void*& ptr, std::size_t& space) noexcept
{
    std::uintptr_t	pn	= reinterpret_cast<std::uintptr_t>(ptr);
    std::uintptr_t	aligned = (pn + alignment - 1) & -alignment;
    std::size_t		padding = aligned - pn;

    if (space < size + padding)
	return nullptr;

    space -= padding;
    return ptr = reinterpret_cast<void*>(aligned);
}
#endif
}

namespace TU
{
namespace simd
{
/************************************************************************
*  functions for memory alignment					*
************************************************************************/
template <class T> inline auto
ceil(T* p)
{
    constexpr size_t	vsize = sizeof(vec<std::remove_cv_t<T> >);
    size_t		space = 2*vsize - 1;
    void*		q     = const_cast<void*>(p);
    
    return reinterpret_cast<T*>(std::align(vsize, vsize, q, space));
}

template <class T> inline auto
floor(T* p)
{
    constexpr size_t	vsize = sizeof(vec<std::remove_cv_t<T> >);

    return ceil(reinterpret_cast<T*>(reinterpret_cast<char*>(p) - vsize + 1));
}

/************************************************************************
*  Load/Store								*
************************************************************************/
//! メモリからベクトルをロードする．
/*!
  \param p	ロード元のメモリアドレス
  \return	ロードされたベクトル
*/
template <bool ALIGNED=false, class T> vec<T>
load(const T* p)							;

//! メモリにベクトルをストアする．
/*!
  \param p	ストア先のメモリアドレス
  \param x	ストアされるベクトル
*/
template <bool ALIGNED=false, class T> void
store(T* p, vec<T> x)							;

}	// namespace simd
}	// namespace TU

#if defined(MMX)
#  include "TU/simd/x86/load_store.h"
#elif defined(NEON)
#  include "TU/simd/arm/load_store.h"
#endif

#endif	// !TU_SIMD_LOAD_STORE_H
