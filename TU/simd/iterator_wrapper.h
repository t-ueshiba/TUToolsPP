/*!
  \file		iterator_wrapper.h
  \author	Toshio UESHIBA
  \brief	SIMDベクトル間の型変換関数の定義
*/
#if !defined(TU_SIMD_ITERATOR_WRAPPER_H)
#define	TU_SIMD_ITERATOR_WRAPPER_H

#include "TU/simd/load_store_iterator.h"

namespace TU
{
namespace simd
{
/************************************************************************
*  iterator_wrapper<ITER, ALIGNED>					*
************************************************************************/
//! 反復子をラップして名前空間 TU::simd に取り込むためのクラス
/*!
  本クラスの目的は，以下の2つである．
    (1)	iterator_value<ITER> がSIMDベクトル型となるあらゆる反復子を
	その機能を保持したまま名前を変更することにより，TU/algorithm.h にある
	関数のオーバーロード版を呼び出せるようにすること．
    (2)	ITER が const T* 型または T* 型のとき，それぞれ load_iterator<T, true>
	store_iterator<T, true> を生成できるようにすること．本クラスでラップ
	されたポインタが指すアドレスは sizeof(vec<T>) にalignされているものと
	みなされる．
	
  \param ITER	ラップする反復子の型
*/ 
template <class ITER, bool ALIGNED>
class iterator_wrapper
    : public boost::iterator_adaptor<iterator_wrapper<ITER, ALIGNED>, ITER>
{
  public:
    using element_type	= typename std::iterator_traits<ITER>::value_type;
    template <class U_>
    struct rebind
    {
	using type	= iterator_wrapper<U_*, ALIGNED>;
    };
    
  private:
    using super		= boost::iterator_adaptor<iterator_wrapper, ITER>;

  public:
    iterator_wrapper(ITER iter)	:super(iter)	{}
    template <class ITER_,
	      std::enable_if_t<std::is_convertible<ITER_, ITER>::value>*
	      = nullptr>
    iterator_wrapper(ITER_ iter) :super(iter)	{}
    template <class ITER_,
	      std::enable_if_t<std::is_convertible<ITER_, ITER>::value>*
	      = nullptr>
    iterator_wrapper(iterator_wrapper<ITER_, ALIGNED> iter)
	:super(iter.base())			{}

    operator ITER()			const	{ return super::base(); }
};

/************************************************************************
*  wrap_iterator<ALIGNED>(ITER iter)					*
************************************************************************/
//! 反復子をラップして名前空間 TU::simd に取り込む
/*!
  \param iter	ラップする反復子
*/
template <class ITER> inline iterator_wrapper<ITER, true>
wrap_iterator(ITER iter)
{
    return {iter};
}

template <class T> inline iterator_wrapper<T*, false>
wrap_iterator(T* p)
{
    return {p};
}
    
/************************************************************************
*  make_accessor(ITER iter)						*
************************************************************************/
//! ラップされた反復子からもとの反復子を取り出す
/*!
  map_iterator<T, MASK, FUNC, ITERS> 等のSIMDベクトルまたはその
  tuple を返す反復子がラップされている場合は，もとの反復子を取り出して
  他のSIMDベクトル用のアルゴリズムや反復子に渡せるようにする．
  \param iter	ラップされた反復子
  \return	もとの反復子
*/
template <class ITER, bool ALIGNED> inline ITER
make_accessor(const iterator_wrapper<ITER, ALIGNED>& iter)
{
    return iter.base();
}

//! ラップされた定数ポインタからSIMDベクトルを読み込む反復子を生成する
/*!
  ALIGNED = true の場合，ラップされたポインタは sizeof(vec<T>) に
  alignされていなければならない．
  \param p	ラップされた定数ポインタ
  \return	SIMDベクトルを読み込む反復子
*/
template <class T, bool ALIGNED> inline load_iterator<T, ALIGNED>
make_accessor(const iterator_wrapper<const T*, ALIGNED>& p)
{
    return {p.base()};
}

//! ラップされたポインタからSIMDベクトルを書き込む反復子を生成する
/*!
  ALIGNED = true の場合，ラップされたポインタは sizeof(vec<T>) に
  alignされていなければならない．
  \param p	ラップされたポインタ
  \return	SIMDベクトルを書き込む反復子
*/
template <class T, bool ALIGNED> inline store_iterator<T, ALIGNED>
make_accessor(const iterator_wrapper<T*, ALIGNED>& p)
{
    return {p.base()};
}

//! ラップされた反復子の tuple からSIMDベクトル用のアルゴリズムに渡せる反復子の tuple を生成する
template <class... ITER> constexpr inline auto
make_accessor(const std::tuple<ITER...>& iter_tuple)
{
    return tuple_transform([](const auto& iter){ return make_accessor(iter); },
			   iter_tuple);
}

//! zip_iterator中の各反復子からSIMDベクトルを読み書きする反復子を生成し，それを再度zip_iteratorにまとめる
/*!
  \param zip_iter	SIMDベクトルを読み込み元/書き込み先を指す反復子を束ねた
			zip_iterator
  \return		SIMDベクトルを読み書きする反復子を束ねたzip_iterator
*/
template <class ITER_TUPLE> inline auto
make_accessor(const zip_iterator<ITER_TUPLE>& zip_iter)
{
    return make_zip_iterator(make_accessor(zip_iter.get_iterator_tuple()));
}

template <class... ITER, bool... ALIGNED> inline auto
make_zip_iterator(const std::tuple<
			    iterator_wrapper<ITER, ALIGNED>...>& iter_tuple)
{
    return wrap_iterator(TU::make_zip_iterator(make_accessor(iter_tuple)));
}

template <class... ITER, bool... ALIGNED> inline auto
make_zip_iterator(const iterator_wrapper<ITER, ALIGNED>&... iter)
{
    return wrap_iterator(TU::make_zip_iterator(make_accessor(iter)...));
}

}	// namespace simd
}	// namespace TU
#endif	// !TU_SIMD_ITERATOR_WRAPPER_H

