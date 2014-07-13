/*
 *  $Id$
 */
/*!
  \mainpage	libTUCuda++ - NVIDIA社のCUDAを利用するためのユティリティライブラリ
  \anchor	libTUCuda

  \section copyright 著作権
  平成14-23年（独）産業技術総合研究所 著作権所有

  創作者：植芝俊夫

  本プログラムは（独）産業技術総合研究所の職員である植芝俊夫が創作し，
  （独）産業技術総合研究所が著作権を所有する秘密情報です．著作権所有
  者による許可なしに本プログラムを使用，複製，改変，第三者へ開示する
  等の行為を禁止します．
   
  このプログラムによって生じるいかなる損害に対しても，著作権所有者お
  よび創作者は責任を負いません。

  Copyright 2002-2011.
  National Institute of Advanced Industrial Science and Technology (AIST)

  Creator: Toshio UESHIBA

  [AIST Confidential and all rights reserved.]
  This program is confidential. Any using, copying, changing or
  giving any information concerning with this program to others
  without permission by the copyright holder are strictly prohibited.

  [No Warranty.]
  The copyright holder or the creator are not responsible for any
  damages caused by using this program.

  \section abstract 概要
  libTUCuda++は，C++環境においてNVIDIA社のCUDAを利用するためのユティリティ
  ライブラリである．以下のようなクラスおよび関数が実装されている．

  <b>デバイス側のグローバルメモリ領域にとられる1次元および2次元配列</b>
  - #TU::CudaArray
  - #TU::CudaArray2

  <b>デバイス側のテクスチャメモリ</b>
  - #TU::CudaTexture
  
  <b>フィルタリング</b>
  - #TU::CudaFilter2
  - #TU::CudaGaussianConvolver2

  <b>ユティリティ</b>
  - #TU::cudaCopyToConstantMemory(Iterator, Iterator, T*)
  - #TU::cudaSubsample(const CudaArray2<T>&, CudaArray2<T>&)
  - #TU::cudaOp3x3(const CudaArray2<S>&, CudaArray2<T>&, OP op)
  - #TU::cudaSuppressNonExtrema3x3(const CudaArray2<T>&, CudaArray2<T>&, OP op, T)
  
  \file		CudaArray++.h
  \brief	CUDAデバイス上の配列に関連するクラスの定義と実装
*/
#ifndef __TU_CUDAARRAYPP_H
#define __TU_CUDAARRAYPP_H

#include <thrust/device_malloc.h>
#include <thrust/device_free.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include "TU/Array++.h"

/*!
  \namespace	TU
  \brief	本ライブラリで定義されたクラスおよび関数を納める名前空間
*/
namespace TU
{
/************************************************************************
*  class CudaBuf<T>							*
************************************************************************/
//! CUDAにおいてデバイス側に確保される可変長バッファクラス
/*!
  単独で使用することはなく，#TU::Arrayまたは#TU::Array2の
  第2テンプレート引数に指定することによって，それらの基底クラスとして使う．
  \param T	要素の型
*/
template <class T>
class CudaBuf
{
  public:
  //! 要素の型    
    typedef T						value_type;
  //! 要素への参照    
    typedef thrust::device_reference<value_type>	reference;
  //! 定数要素への参照    
    typedef thrust::device_reference<const value_type>	const_reference;
  //! 要素へのポインタ    
    typedef thrust::device_ptr<value_type>		pointer;
  //! 定数要素へのポインタ    
    typedef thrust::device_ptr<const value_type>	const_pointer;
  //! 反復子    
    typedef pointer					iterator;
  //! 定数反復子    
    typedef const_pointer				const_iterator;
    
  public:
    explicit		CudaBuf(size_t siz=0)				;
			CudaBuf(pointer p, size_t siz)			;
			CudaBuf(const CudaBuf& b)			;
    CudaBuf&		operator =(const CudaBuf& b)			;
			~CudaBuf()					;

    pointer		data()						;
    const_pointer	data()					const	;
    const_iterator	cbegin()				const	;
    const_iterator	begin()					const	;
    iterator		begin()						;
    const_iterator	cend()					const	;
    const_iterator	end()					const	;
    iterator		end()						;
    size_t		size()					const	;
    size_t		dim()					const	;
    bool		resize(size_t siz)				;
    void		resize(pointer p, size_t siz)			;
    static size_t	stride(size_t siz)				;
    std::istream&	get(std::istream& in, size_t m=0)		;
    std::ostream&	put(std::ostream& out)			const	;
    
  private:
    static pointer	memalloc(size_t siz)				;
    static void		memfree(pointer p)				;

  private:
    size_t	_size;		// the number of elements in the buffer
    pointer	_p;		// pointer to the buffer area
    bool	_shared;	// buffer area is shared with other object
};
    
//! 指定した要素数のバッファを作る．
/*!
  \param siz	要素数
*/
template <class T> inline
CudaBuf<T>::CudaBuf(size_t siz)
    :_size(siz), _p(memalloc(_size)), _shared(false)
{
}

//! 外部の領域と要素数を指定してバッファを作る．
/*!
  \param p	外部領域へのポインタ
  \param siz	要素数
*/
template <class T> inline
CudaBuf<T>::CudaBuf(pointer p, size_t siz)
    :_size(siz), _p(p), _shared(true)
{
}
    
//! コピーコンストラクタ
template <class T> inline
CudaBuf<T>::CudaBuf(const CudaBuf<T>& b)
    :_size(b._size), _p(memalloc(_size)), _shared(false)
{
    thrust::copy(b.cbegin(), b.cend(), begin());
}

//! 標準代入演算子
template <class T> inline CudaBuf<T>&
CudaBuf<T>::operator =(const CudaBuf<T>& b)
{
    if (this != &b)
    {
	resize(b._size);
	thrust::copy(b.cbegin(), b.cend(), begin());
    }
    return *this;
}

//! デストラクタ
template <class T> inline
CudaBuf<T>::~CudaBuf()
{
    if (!_shared)
	memfree(_p);
}
    
//! バッファが使用する内部記憶領域へのポインタを返す．
template <class T> inline typename CudaBuf<T>::pointer
CudaBuf<T>::data()
{
    return _p;
}

//! バッファが使用する内部記憶領域へのポインタを返す．
template <class T> inline typename CudaBuf<T>::const_pointer
CudaBuf<T>::data() const
{
    return _p;
}
    
//! バッファの先頭要素を指す定数反復子を返す．
template <class T> inline typename CudaBuf<T>::const_iterator
CudaBuf<T>::cbegin() const
{
    return data();
}

//! バッファの先頭要素を指す定数反復子を返す．
template <class T> inline typename CudaBuf<T>::const_iterator
CudaBuf<T>::begin() const
{
    return cbegin();
}

//! バッファの先頭要素を指す反復子を返す．
template <class T> inline typename CudaBuf<T>::iterator
CudaBuf<T>::begin()
{
    return data();
}

//! バッファの末尾を指す定数反復子を返す．
template <class T> inline typename CudaBuf<T>::const_iterator
CudaBuf<T>::cend() const
{
    return cbegin() + size();
}

//! バッファの末尾を指す定数反復子を返す．
template <class T> inline typename CudaBuf<T>::const_iterator
CudaBuf<T>::end() const
{
    return cend();
}

//! バッファの末尾を指す反復子を返す．
template <class T> inline typename CudaBuf<T>::iterator
CudaBuf<T>::end()
{
    return begin() + size();
}

//! バッファの要素数を返す．
template <class T> inline size_t
CudaBuf<T>::size() const
{
    return _size;
}
    
//! バッファの要素数を返す．
template <class T> inline size_t
CudaBuf<T>::dim() const
{
    return _size;
}
    
//! バッファの要素数を変更する．
/*!
  ただし，他のオブジェクトと記憶領域を共有しているバッファの要素数を
  変更することはできない．
  \param siz			新しい要素数
  \return			sizが元の要素数よりも大きければtrue，そう
				でなければfalse
  \throw std::logic_error	記憶領域を他のオブジェクトと共有している場合
				に送出
*/
template <class T> bool
CudaBuf<T>::resize(size_t siz)
{
    if (_size == siz)
	return false;
    
    if (_shared)
	throw std::logic_error("CudaBuf<T>::resize: cannot change size of shared buffer!");

    memfree(_p);
    const size_t	old_size = _size;
    _size = siz;
    _p = memalloc(_size);

    return _size > old_size;
}

//! バッファが内部で使用する記憶領域を指定したものに変更する．
/*!
  \param p	新しい記憶領域へのポインタ
  \param siz	新しい要素数
*/
template <class T> inline void
CudaBuf<T>::resize(pointer p, size_t siz)
{
    if (!_shared)
	memfree(_p);
    _size = siz;
    _p = p;
    _shared = true;
}

//! 指定された要素数を持つ記憶領域を確保するために実際に必要な要素数を返す．
/*!
  （記憶容量ではなく）要素数が16または32の倍数になるよう，
  与えられた要素数を繰り上げる．
  \param siz	要素数
  \return	16または32の倍数に繰り上げられた要素数
*/
template <class T> inline size_t
CudaBuf<T>::stride(size_t siz)
{
    const size_t	ALIGN = (sizeof(T) % 8 != 0 ? 32 : 16);
	
    return (siz > 0 ? ALIGN * ((siz - 1) / ALIGN + 1) : 0);
}
    
//! 入力ストリームから指定した箇所に配列を読み込む(ASCII)．
/*!
  \param in	入力ストリーム
  \param m	読み込み先の先頭を指定するindex
  \return	inで指定した入力ストリーム
*/
template <class T> std::istream&
CudaBuf<T>::get(std::istream& in, size_t m)
{
    const size_t	BufSiz = (sizeof(T) < 2048 ? 2048 / sizeof(T) : 1);
    T* const		tmp = new T[BufSiz];
    size_t		n = 0;
    
    while (n < BufSiz)
    {
	char	c;
	while (in.get(c))		// skip white spaces other than '\n'
	    if (!isspace(c) || c == '\n')
		break;

	if (!in || c == '\n')
	{
	    resize(m + n);
	    break;
	}

	in.putback(c);
	in >> tmp[n++];
    }
    if (n == BufSiz)
	get(in, m + n);

    for (size_t i = 0; i < n; ++i)
	_p[m + i] = tmp[i];

    delete [] tmp;
    
    return in;
}

//! 出力ストリームに配列を書き出す(ASCII)．
/*!
  \param out	出力ストリーム
  \return	outで指定した出力ストリーム
*/
template <class T> std::ostream&
CudaBuf<T>::put(std::ostream& out) const
{
    for (size_t i = 0; i < _size; )
	out << ' ' << _p[i++];
    return out;
}

template <class T> inline typename CudaBuf<T>::pointer
CudaBuf<T>::memalloc(size_t siz)
{
    if (siz > 0)
    {
	pointer	p = thrust::device_malloc<T>(siz);
	cudaMemset(p.get(), 0, sizeof(T) * siz);
	return p;
    }
    else
	return pointer((T*)0);
}
    
template <class T> inline void
CudaBuf<T>::memfree(pointer p)
{
    if (p.get() != 0)
	thrust::device_free(p);
}
    
/************************************************************************
*  class CudaArray<T>							*
************************************************************************/
//! CUDAにおいてデバイス側に確保されるT型オブジェクトの1次元配列クラス
/*!
  \param T	要素の型
*/
template <class T>
class CudaArray : public Array<T, CudaBuf<T> >
{
  private:
    typedef Array<T, CudaBuf<T> >		super;

  public:
  //! 成分の型
    typedef typename super::element_type	element_type;
  //! 要素の型    
    typedef typename super::value_type		value_type;
  //! 要素への参照
    typedef typename super::reference		reference;
  //! 定数要素への参照
    typedef typename super::const_reference	const_reference;
  //! 要素へのポインタ
    typedef typename super::pointer		pointer;
  //! 定数要素へのポインタ
    typedef typename super::const_pointer	const_pointer;
  //! 反復子
    typedef typename super::iterator		iterator;
  //! 定数反復子
    typedef typename super::const_iterator	const_iterator;
  //! 逆反復子    
    typedef typename super::reverse_iterator	reverse_iterator;
  //! 定数逆反復子    
    typedef typename super::const_reverse_iterator
						const_reverse_iterator;
  //! ポインタ間の差
    typedef typename super::difference_type	difference_type;
  //! 要素への直接ポインタ
    typedef element_type*			raw_pointer;
  //! 定数要素への直接ポインタ
    typedef const element_type*			const_raw_pointer;
    
  public:
		CudaArray()						;
    explicit	CudaArray(size_t d)					;
		CudaArray(pointer p, size_t d)				;
		CudaArray(CudaArray& a, size_t i, size_t d)		;
    template <class B>
		CudaArray(const Array<T, B>& a)				;
    template <class B>
    CudaArray&	operator =(const Array<T, B>& a)			;
    template <class B> const CudaArray&
		write(Array<T, B>& a)				const	;
    CudaArray&	operator =(const element_type& c)			;

    raw_pointer		data()						;
    const_raw_pointer	data()					const	;
    
    using	super::begin;
    using	super::end;
    using	super::rbegin;
    using	super::rend;
    using	super::size;
    using	super::dim;
    using	super::resize;
};

//! CUDA配列を作る．
template <class T> inline
CudaArray<T>::CudaArray()
    :super()
{
}

//! 指定した要素数のCUDA配列を作る．
/*!
  \param d	配列の要素数
*/
template <class T> inline
CudaArray<T>::CudaArray(size_t d)
    :super(d)
{
}

//! 外部の領域と要素数を指定してCUDA配列を作る．
/*!
  \param p	外部領域へのポインタ
  \param d	配列の要素数
*/
template <class T> inline
CudaArray<T>::CudaArray(pointer p, size_t d)
    :super(p, d)
{
}

//! 記憶領域を元の配列と共有した部分CUDA配列を作る．
/*!
  \param a	配列
  \param i	部分配列の第0要素を指定するindex
  \param d	部分配列の次元(要素数)
*/
template <class T> inline
CudaArray<T>::CudaArray(CudaArray<T>& a, size_t i, size_t d)
    :super(a, i, d)
{
}

//! 他の配列と同一要素を持つCUDA配列を作る（コピーコンストラクタの拡張）
/*!
  コピーコンストラクタは別途自動的に生成される．
  \param a	コピー元の配列
*/
template <class T> template <class B> inline
CudaArray<T>::CudaArray(const Array<T, B>& a)
    :super(a.size())
{
    thrust::copy(a.begin(), a.end(), begin());
}

//! 他の配列を自分に代入する（標準代入演算子の拡張）
/*!
  標準代入演算子は別途自動的に生成される．
  \param a	コピー元の配列
  \return	この配列
*/
template <class T> template <class B> inline CudaArray<T>&
CudaArray<T>::operator =(const Array<T, B>& a)
{
    resize(a.size());
    thrust::copy(a.begin(), a.end(), begin());
    return *this;
}

//! このCUDA配列の内容を他の配列に書き出す．
/*!
  \param a	コピー先の配列
  \return	この配列
*/
template <class T> template <class B> inline const CudaArray<T>&
CudaArray<T>::write(Array<T, B>& a) const
{
    a.resize(size());
    thrust::copy(begin(), end(), a.begin());
    return *this;
}

//! 全ての要素に同一の値を代入する．
/*!
  \param c	代入する値
  \return	この配列
*/
template <class T> inline CudaArray<T>&
CudaArray<T>::operator =(const element_type& c)
{
    thrust::fill(begin(), end(), c);
    return *this;
}

//! このCUDA配列の内部記憶領域へのポインタを返す．
/*!
  \return	内部記憶領域へのポインタ
*/
template <class T> inline typename CudaArray<T>::raw_pointer
CudaArray<T>::data()
{
    return super::data().get();
}
		    
//! このCUDA配列の内部記憶領域へのポインタを返す．
/*!
  \return	内部記憶領域へのポインタ
*/
template <class T> inline typename CudaArray<T>::const_raw_pointer
CudaArray<T>::data() const
{
    return super::data().get();
}
		    
/************************************************************************
*  class CudaArray2<T>							*
************************************************************************/
//! CUDAにおいてデバイス側に確保されるT型オブジェクトの2次元配列クラス
/*!
  \param T	要素の型
*/
template <class T>
class CudaArray2 : public Array2<CudaArray<T>, CudaBuf<T> >
{
  private:
    typedef Array2<CudaArray<T>, CudaBuf<T> >		super;
    typedef CudaBuf<T>					buf_type;
    
  public:
  //! 行の型    
    typedef typename super::value_type			value_type;
  //! 行への参照    
    typedef typename super::reference			reference;
  //! 定数行への参照    
    typedef typename super::const_reference		const_reference;
  //! 行の反復子    
    typedef typename super::iterator			iterator;
  //! 行の定数反復子    
    typedef typename super::const_iterator		const_iterator;
  //! 行の逆反復子    
    typedef typename super::reverse_iterator		reverse_iterator;
  //! 行の定数逆反復子    
    typedef typename super::const_reverse_iterator	const_reverse_iterator;
  //! 成分の型    
    typedef typename super::element_type		element_type;
  //! 成分へのポインタ    
    typedef typename super::pointer			pointer;
  //! 定数成分へのポインタ    
    typedef typename super::const_pointer		const_pointer;
  //! 成分への直接ポインタ    
    typedef element_type*				raw_pointer;
  //! 定数成分への直接ポインタ    
    typedef const element_type*				const_raw_pointer;
  //! ポインタ間の差    
    typedef std::ptrdiff_t				difference_type;

  public:
    CudaArray2()							;
    CudaArray2(size_t r, size_t c)					;
    CudaArray2(pointer p, size_t r, size_t c)				;
    CudaArray2(CudaArray2& a, size_t i, size_t j, size_t r, size_t c)	;
    template <class T2, class B2, class R2>
    CudaArray2(const Array2<T2, B2, R2>& a)				;
    template <class T2, class B2, class R2>
    CudaArray2&	operator =(const Array2<T2, B2, R2>& a)			;
    template <class T2, class B2, class R2> const CudaArray2&
		write(Array2<T2, B2, R2>& a)			const	;
    CudaArray2&	operator =(const element_type& c)			;

    raw_pointer		data()						;
    const_raw_pointer	data()					const	;

    using	super::begin;
    using	super::end;
    using	super::size;
    using	super::dim;
    using	super::nrow;
    using	super::ncol;
    using	super::stride;
};

//! 2次元CUDA配列を作る．
template <class T> inline
CudaArray2<T>::CudaArray2()
    :super()
{
}

//! 行数と列数を指定して2次元CUDA配列を作る．
/*!
  \param r	行数
  \param c	列数
*/
template <class T> inline
CudaArray2<T>::CudaArray2(size_t r, size_t c)
    :super(r, c)
{
}

//! 外部の領域と行数および列数を指定して2次元CUDA配列を作る．
/*!
  \param p	外部領域へのポインタ
  \param r	行数
  \param c	列数
*/
template <class T> inline
CudaArray2<T>::CudaArray2(pointer p, size_t r, size_t c)
    :super(p, r, c)
{
}

//! 記憶領域を元の配列と共有した2次元部分CUDA配列を作る
/*!
  \param a	配列
  \param i	部分配列の左上隅要素の行を指定するindex
  \param j	部分配列の左上隅要素の列を指定するindex
  \param r	部分配列の行数
  \param c	部分配列の列数
*/
template <class T> inline
CudaArray2<T>::CudaArray2(CudaArray2& a, size_t i, size_t j, size_t r, size_t c)
    :super(a, i, j, r, c)
{
}    

//! 他の2次元配列と同一要素を持つ2次元CUDA配列を作る（コピーコンストラクタの拡張）
/*!
  コピーコンストラクタは別途自動的に生成される．
  \param a	コピー元の配列
*/
template <class T>
template <class T2, class B2, class R2> inline
CudaArray2<T>::CudaArray2(const Array2<T2, B2, R2>& a)
    :super()
{
    operator =(a);
}

//! 他の2次元配列を自分に代入する（標準代入演算子の拡張）
/*!
  標準代入演算子は別途自動的に生成される．
  \param a	コピー元の配列
  \return	この配列
*/
template <class T>
template <class T2, class B2, class R2> inline CudaArray2<T>&
CudaArray2<T>::operator =(const Array2<T2, B2, R2>& a)
{
    resize(a.nrow(), a.ncol());
    if (a.nrow() > 0 && a.stride() == stride())
    {
	thrust::copy(a[0].begin(), a[a.nrow()-1].end(), (*this)[0].begin());
    }
    else
    {
	for (size_t i = 0; i < nrow(); ++i)
	    (*this)[i] = a[i];
    }
    return *this;
}

//! この2次元CUDA配列の内容を他の2次元配列に書き出す．
/*!
  \param a	コピー先の配列
  \return	この配列
*/
template <class T>
template <class T2, class B2, class R2> inline const CudaArray2<T>&
CudaArray2<T>::write(Array2<T2, B2, R2>& a) const
{
    a.resize(nrow(), ncol());
    if (nrow() > 0 && stride() == a.stride())
    {
	thrust::copy((*this)[0].begin(),
		     (*this)[nrow()-1].end(), a[0].begin());
    }
    else
    {
	for (size_t i = 0; i < nrow(); ++i)
	    (*this)[i].write(a[i]);
    }
    return *this;
}

//! 全ての要素に同一の値を代入する．
/*!
  \param c	代入する値
  \return	この配列
*/
template <class T> inline CudaArray2<T>&
CudaArray2<T>::operator =(const element_type& c)
{
    if (nrow() > 0)
	thrust::fill((*this)[0].begin(), (*this)[nrow()-1].end(), c);
    return *this;
}

//! この2次元CUDA配列の内部記憶領域へのポインタを返す．
/*!
  
  \return	内部記憶領域へのポインタ
*/
template <class T> inline typename CudaArray2<T>::raw_pointer
CudaArray2<T>::data()
{
    return super::data().get();
}
		    
//! この2次元CUDA配列の内部記憶領域へのポインタを返す．
/*!
  \return	内部記憶領域へのポインタ
*/
template <class T> inline typename CudaArray2<T>::const_raw_pointer
CudaArray2<T>::data() const
{
    return super::data().get();
}

}
#endif	// !__TU_CUDAARRAYPP_H
