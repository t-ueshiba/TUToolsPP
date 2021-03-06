/*
 *  $Id$
 */
#include "TU/simd/Array++.h"

namespace TU
{
#ifdef SIMD
template <class T>
using Allocator = simd::allocator<T>;
#else
template <class T>
using Allocator = std::allocator<T>;
#endif
    
struct sum
{
    template <class S, class T, class U>
    auto	operator ()(S x, T y, U z)	const	{ return x + y + z; }
};
    
template <class IN, class OUT> void
test_assign()
{
    Array<IN, 0, Allocator<IN> >
	x({ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31});
    Array<OUT, 0, Allocator<OUT> >	w;

    w = x;

    std::copy(cbegin(w), cend(w),
	      std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
    
template <class IN0, class IN1, class T, class OUT> void
test_single_stage()
{
    Array<IN0, 0, Allocator<IN0> >
	x({ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31});
    Array<IN1, 0, Allocator<IN1> >
	y({ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31});
    Array<OUT, 0, Allocator<OUT> >	w;

    w = zip(x, y) >> mapped<T>(std::plus<>());

    std::copy(cbegin(w), cend(w), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <class IN0, class IN1, class T, class IN2, class OUT> void
test_two_stages()
{
    Array<IN0, 0, Allocator<IN0> >
	x({ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31});
    Array<IN1, 0, Allocator<IN1> >
	y({ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31});
    Array<IN2, 0, Allocator<IN2> >
	z({ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31});
    Array<OUT, 0, Allocator<OUT> >	w;

    w = zip(zip(x, y) >> mapped<T>(std::plus<>()), z)
	>> mapped<OUT>(std::multiplies<>());
    
    std::copy(cbegin(w), cend(w), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    w += zip(x, y, z) >> mapped<T>(sum());
    
    std::copy(cbegin(w), cend(w), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

template <class T, class IN0, class IN1> void
test_map_iterator()
{
    Array<IN0, 0, Allocator<IN0> >
	x({ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31});
    Array<IN1, 0, Allocator<IN1> >
	y({ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31});

    const auto	end = make_map_iterator<T>(std::plus<>(), cend(x), cend(y));
    for (auto iter = make_map_iterator<T>(std::plus<>(), cbegin(x), cbegin(y));
	 iter != end; ++iter)
	std::cout << *iter << std::endl;
}

template <class IN, class OUT> void
test_assign2()
{
  // simd::allocatorを使った場合，alignmentが満たされないので
  // 2次元配列はinitializer_listで初期化できない
    Array2<IN, 0, 0, Allocator<IN> >	x(2, 32);
    x[0] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    x[1] = 2*x[0];
    Array2<OUT, 0, 0, Allocator<OUT> >	w;

    w = x;

    for (auto row : w)
    {
	std::copy(begin(row), end(row),
		  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
    }
    std::cout << std::endl;
}
    
template <class IN0, class IN1, class T, class OUT> void
test_single_stage2()
{
    Array2<IN0, 0, 0, Allocator<IN0> >	x(2, 32);
    x[0] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    x[1] = 2*x[0];
    Array2<IN1, 0, 0, Allocator<IN1> >	y = x;
    Array2<OUT, 0, 0, Allocator<OUT> >	w;
#if 0
    auto	z = zip(x, y);
    std::cout << demangle<decltype(begin(z))>() << std::endl;
#else
    w = zip(x, y) >> mapped<T>(std::plus<>());

    for (auto row : w)
    {
	std::copy(begin(row), end(row),
		  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
    }
    std::cout << std::endl;
#endif
}

template <class IN0, class IN1, class T, class IN2, class OUT> void
test_two_stages2()
{
    Array2<IN0, 0, 0, Allocator<IN0> >	x(2, 32);
    x[0] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    x[1] = 2*x[0];
    Array2<IN1, 0, 0, Allocator<IN1> >	y = x;
    Array2<IN2, 0, 0, Allocator<IN2> >	z = x;
    Array2<OUT, 0, 0, Allocator<OUT> >	w;

    auto	yy = zip(x, y) >> mapped<T>(std::plus<>());
    std::cout << "=======" << std::endl;
    std::cout << demangle<decltype(yy)>() << std::endl;
    std::cout << yy.begin().stride() << std::endl;
    std::cout << "=======" << std::endl;

    auto	zz =  zip(zip(x, y) >> mapped<T>(std::plus<>()), z)
		   >> mapped<OUT>(std::multiplies<>());
    std::cout << "=======" << std::endl;
    std::cout << demangle<decltype(zz)>() << std::endl;
    std::cout << zz.begin().stride() << std::endl;
    std::cout << "=======" << std::endl;

    w = zip(zip(x, y) >> mapped<T>(std::plus<>()), z)
	>> mapped<OUT>(std::multiplies<>());

    for (auto row : w)
    {
	std::copy(begin(row), end(row),
		  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
    }
    std::cout << std::endl;

    w += zip(x, y, z) >> mapped<T>(sum());
    
    for (auto row : w)
    {
	std::copy(begin(row), end(row),
		  std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
    }
    std::cout << std::endl;
}

}

int
main()
{

    TU::test_assign<int32_t, int8_t>();

    std::cerr << "--------------" << std::endl;

    TU::test_single_stage<int16_t, int16_t, int8_t, int32_t>();

    std::cerr << "--------------" << std::endl;
    
    TU::test_two_stages<int16_t, int32_t, float, int8_t, int16_t>();

    std::cerr << "--------------" << std::endl;
    
    TU::test_map_iterator<int16_t, int16_t, float>();

    std::cerr << "--------------" << std::endl;

    TU::test_assign2<int16_t, int8_t>();

    std::cerr << "--------------" << std::endl;

    TU::test_single_stage2<int16_t, int16_t, int8_t, int32_t>();

    std::cerr << "--------------" << std::endl;

    TU::test_two_stages2<int16_t, int32_t, float, int8_t, int16_t>();

    return 0;
}
