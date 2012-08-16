/*
 *  $Id: BoxFilter.h,v 1.2 2012-08-16 01:30:37 ueshiba Exp $
 */
/*!
  \file		BoxFilter.h
  \brief	box filterに関するクラスの定義と実装
*/
#ifndef	__TUBoxFilter_h
#define	__TUBoxFilter_h

#include "TU/iterator.h"
#if defined(USE_TBB)
#  include <tbb/parallel_for.h>
#  include <tbb/blocked_range.h>
#endif

namespace TU
{
/************************************************************************
*  global functions							*
************************************************************************/
//! box filter反復子を生成する
/*!
  \param iter	コンテナ中の要素を指す定数反復子の型
  \return	box filter反復子
*/
template <class Iterator> box_filter_iterator<Iterator>
make_box_filter_iterator(Iterator iter)
{
    return box_filter_iterator<Iterator>(iter);
}

//! 1次元入力データ列にbox filterを適用する
/*!
  \param ib	1次元入力データ列の先頭を示す反復子
  \param ie	1次元入力データ列の末尾の次を示す反復子
  \param out	box filterを適用した出力データ列の先頭を示す反復子
  \param w	box filterのウィンドウ幅
  \param shift	出力データの書き込み位置をoutで指定した位置よりもこの量だけずらす
*/
template <class IN, class OUT> void
boxFilter(IN ib, IN ie, OUT out, size_t w, size_t shift=0)
{
    while (shift-- > 0)
	++out;
    
    for (box_filter_iterator<IN> iter(ib, w), end(ie, 0); iter != end; ++iter)
    {
	*out = *iter;
	++out;
    }
}

namespace detail
{
    template <class IN, class OUT> static void
    boxFilter2Kernel(IN ib, IN ie, OUT out,
		     size_t wrow, size_t wcol, size_t srow, size_t scol)
    {
	while (srow-- > 0)
	    ++out;
	
	for (box_filter_iterator<IN> iter(ib, wrow), end(ie, 0);
	     iter != end; ++iter)
	{
	    boxFilter(iter->begin(), iter->end() + 1 - wcol,
		      out->begin(), wcol, scol);
	    ++out;
	}
    }

# if defined(USE_TBB)
  /**********************************************************************
  *  class BoxFilter2							*
  **********************************************************************/
    template <class IN, class OUT>
    class BoxFilter2
    {
      public:
	BoxFilter2(IN in, OUT out,
		   size_t wrow, size_t wcol, size_t srow, size_t scol)
	    :_in(in), _out(out),
	     _wrow(wrow), _wcol(wcol), _srow(srow), _scol(scol)		{}

	void	operator ()(const tbb::blocked_range<int>& r) const
		{
		    detail::boxFilter2Kernel(_in + r.begin(), _in + r.end(),
					     _out + r.begin(),
					     _wrow, _wcol, _srow, _scol);
		}

      private:
	const IN	_in;
	const OUT	_out;
	const size_t	_wrow;
	const size_t	_wcol;
	const size_t	_srow;
	const size_t	_scol;
    };
# endif
}

//! 2次元入力データにbox filterを適用する
/*!
  \param ib		2次元入力データの先頭の行を示す反復子
  \param ie		2次元入力データの末尾の次の行を示す反復子
  \param out		box filterを適用した出力データの先頭の行を示す反復子
  \param wrow		box filterのウィンドウの行数
  \param wcol		box filterのウィンドウの列数
  \param srow		出力データの書き込み位置をこの量だけ行方向にずらす
  \param scol		出力データの書き込み位置をこの量だけ列方向にずらす
  \param grainSize	スレッドの粒度(TBB使用時のみ有効)
*/
template <class IN, class OUT> void
boxFilter2(IN ib, IN ie, OUT out, size_t wrow, size_t wcol,
	   size_t srow=0, size_t scol=0, size_t grainSize=100)
{
#if defined(USE_TBB)
    tbb::parallel_for(tbb::blocked_range<int>(0, ie - ib, grainSize),
		      detail::BoxFilter2<IN, OUT>(ib, out,
						  wrow, wcol, srow, scol));
#else
    detail::boxFilter2Kernel(ib, ie, out, wrow, wcol, srow, scol);
#endif
}

}
#endif	/* !__TUBoxFilter_h	*/
