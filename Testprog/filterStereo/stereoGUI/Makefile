#
#  $Id$
#
#################################
#  User customizable macros	#
#################################
PROGRAM		= $(shell basename $(PWD))
#LIBRARY		= lib$(shell basename $(PWD))

VPATH		=

IDLS		=
MOCHDRS		=

#CXX		= g++
INCDIRS		= -I. -I../../../src/TUTools++/Testprog/stereo1394 -I$(PREFIX)/include
CPPFLAGS	= -DNDEBUG -DVERBOSE #-DUSE_TBB #-DWITHOUT_CVTDOWN -DRING
CFLAGS		= -g -O
NVCCFLAGS	= -g
ifneq ($(findstring icpc,$(CXX)),)
  CFLAGS	= -O3
  NVCCFLAGS	= -O			# must < -O2
#  CPPFLAGS     += -DSSE3
endif
CCFLAGS		= $(CFLAGS)

LIBS		= -lTUOgl++ -lTUv++ -lTUTools++ \
		  -lGLU -lGL -lmkl_rt
LINKER		= $(CXX)

BINDIR		= $(PREFIX)/bin
LIBDIR		= $(PREFIX)/lib
INCDIR		= $(PREFIX)/include

#########################
#  Macros set by mkmf	#
#########################
SUFFIX		= .cc:sC .cpp:sC .cu:sC
EXTHDRS		= /usr/local/include/TU/Array++.h \
		/usr/local/include/TU/BoxFilter.h \
		/usr/local/include/TU/Camera++.h \
		/usr/local/include/TU/Filter2.h \
		/usr/local/include/TU/Geometry++.h \
		/usr/local/include/TU/GuidedFilter.h \
		/usr/local/include/TU/Image++.h \
		/usr/local/include/TU/List.h \
		/usr/local/include/TU/Minimize.h \
		/usr/local/include/TU/Profiler.h \
		/usr/local/include/TU/Quantizer.h \
		/usr/local/include/TU/Rectify.h \
		/usr/local/include/TU/StereoBase.h \
		/usr/local/include/TU/StereoUtility.h \
		/usr/local/include/TU/TreeFilter.h \
		/usr/local/include/TU/Vector++.h \
		/usr/local/include/TU/Warp.h \
		/usr/local/include/TU/WeightedMedianFilter.h \
		/usr/local/include/TU/algorithm.h \
		/usr/local/include/TU/functional.h \
		/usr/local/include/TU/iterator.h \
		/usr/local/include/TU/pair.h \
		/usr/local/include/TU/range.h \
		/usr/local/include/TU/simd/BufTraits.h \
		/usr/local/include/TU/simd/allocator.h \
		/usr/local/include/TU/simd/arithmetic.h \
		/usr/local/include/TU/simd/arm/allocator.h \
		/usr/local/include/TU/simd/arm/arch.h \
		/usr/local/include/TU/simd/arm/arithmetic.h \
		/usr/local/include/TU/simd/arm/bit_shift.h \
		/usr/local/include/TU/simd/arm/cast.h \
		/usr/local/include/TU/simd/arm/compare.h \
		/usr/local/include/TU/simd/arm/cvt.h \
		/usr/local/include/TU/simd/arm/dup.h \
		/usr/local/include/TU/simd/arm/insert_extract.h \
		/usr/local/include/TU/simd/arm/load_store.h \
		/usr/local/include/TU/simd/arm/logical.h \
		/usr/local/include/TU/simd/arm/lookup.h \
		/usr/local/include/TU/simd/arm/select.h \
		/usr/local/include/TU/simd/arm/shift.h \
		/usr/local/include/TU/simd/arm/type_traits.h \
		/usr/local/include/TU/simd/arm/vec.h \
		/usr/local/include/TU/simd/arm/zero.h \
		/usr/local/include/TU/simd/bit_shift.h \
		/usr/local/include/TU/simd/cast.h \
		/usr/local/include/TU/simd/compare.h \
		/usr/local/include/TU/simd/config.h \
		/usr/local/include/TU/simd/cvt.h \
		/usr/local/include/TU/simd/cvtdown_iterator.h \
		/usr/local/include/TU/simd/cvtup_iterator.h \
		/usr/local/include/TU/simd/dup.h \
		/usr/local/include/TU/simd/insert_extract.h \
		/usr/local/include/TU/simd/load_iterator.h \
		/usr/local/include/TU/simd/load_store.h \
		/usr/local/include/TU/simd/logical.h \
		/usr/local/include/TU/simd/lookup.h \
		/usr/local/include/TU/simd/misc.h \
		/usr/local/include/TU/simd/pack.h \
		/usr/local/include/TU/simd/select.h \
		/usr/local/include/TU/simd/shift.h \
		/usr/local/include/TU/simd/shift_iterator.h \
		/usr/local/include/TU/simd/simd.h \
		/usr/local/include/TU/simd/store_iterator.h \
		/usr/local/include/TU/simd/transform.h \
		/usr/local/include/TU/simd/type_traits.h \
		/usr/local/include/TU/simd/vec.h \
		/usr/local/include/TU/simd/x86/allocator.h \
		/usr/local/include/TU/simd/x86/arch.h \
		/usr/local/include/TU/simd/x86/arithmetic.h \
		/usr/local/include/TU/simd/x86/bit_shift.h \
		/usr/local/include/TU/simd/x86/cast.h \
		/usr/local/include/TU/simd/x86/compare.h \
		/usr/local/include/TU/simd/x86/cvt.h \
		/usr/local/include/TU/simd/x86/dup.h \
		/usr/local/include/TU/simd/x86/insert_extract.h \
		/usr/local/include/TU/simd/x86/load_store.h \
		/usr/local/include/TU/simd/x86/logical.h \
		/usr/local/include/TU/simd/x86/logical_base.h \
		/usr/local/include/TU/simd/x86/lookup.h \
		/usr/local/include/TU/simd/x86/select.h \
		/usr/local/include/TU/simd/x86/shift.h \
		/usr/local/include/TU/simd/x86/shuffle.h \
		/usr/local/include/TU/simd/x86/svml.h \
		/usr/local/include/TU/simd/x86/type_traits.h \
		/usr/local/include/TU/simd/x86/unpack.h \
		/usr/local/include/TU/simd/x86/vec.h \
		/usr/local/include/TU/simd/x86/zero.h \
		/usr/local/include/TU/simd/zero.h \
		/usr/local/include/TU/tuple.h \
		/usr/local/include/TU/v/App.h \
		/usr/local/include/TU/v/CmdPane.h \
		/usr/local/include/TU/v/CmdWindow.h \
		/usr/local/include/TU/v/Colormap.h \
		/usr/local/include/TU/v/Dialog.h \
		/usr/local/include/TU/v/FileSelection.h \
		/usr/local/include/TU/v/ModalDialog.h \
		/usr/local/include/TU/v/Notify.h \
		/usr/local/include/TU/v/TUv++.h \
		/usr/local/include/TU/v/Widget-Xaw.h
HDRS		= MyCmdWindow.h
SRCS		= DrawThreeD.cc \
		MyCanvasPane.cc \
		MyCmdWindow.cc \
		MyOglCanvasPane.cc \
		Rectify.cc \
		createMenuCmds.cc \
		main.cc
OBJS		= DrawThreeD.o \
		MyCanvasPane.o \
		MyCmdWindow.o \
		MyOglCanvasPane.o \
		Rectify.o \
		createMenuCmds.o \
		main.o

#include $(PROJECT)/lib/rtc.mk		# IDLHDRS, IDLSRCS, CPPFLAGS, OBJS, LIBS
#include $(PROJECT)/lib/qt.mk		# MOCSRCS, OBJS
#include $(PROJECT)/lib/cnoid.mk	# CPPFLAGS, LIBS, LIBDIR
#include $(PROJECT)/lib/lib.mk		# PUBHDRS TARGHDRS
include $(PROJECT)/lib/common.mk
###
DrawThreeD.o: /usr/local/include/TU/simd/simd.h \
	/usr/local/include/TU/simd/config.h /usr/local/include/TU/simd/vec.h \
	/usr/local/include/TU/simd/type_traits.h \
	/usr/local/include/TU/simd/x86/type_traits.h \
	/usr/local/include/TU/simd/arm/type_traits.h \
	/usr/local/include/TU/simd/x86/vec.h \
	/usr/local/include/TU/simd/x86/arch.h \
	/usr/local/include/TU/simd/arm/vec.h \
	/usr/local/include/TU/simd/arm/arch.h \
	/usr/local/include/TU/simd/allocator.h \
	/usr/local/include/TU/simd/x86/allocator.h \
	/usr/local/include/TU/simd/arm/allocator.h \
	/usr/local/include/TU/simd/load_store.h /usr/local/include/TU/pair.h \
	/usr/local/include/TU/simd/pack.h /usr/local/include/TU/simd/cvt.h \
	/usr/local/include/TU/tuple.h /usr/local/include/TU/simd/zero.h \
	/usr/local/include/TU/simd/x86/zero.h \
	/usr/local/include/TU/simd/arm/zero.h \
	/usr/local/include/TU/simd/cast.h \
	/usr/local/include/TU/simd/x86/cast.h \
	/usr/local/include/TU/simd/arm/cast.h \
	/usr/local/include/TU/simd/shift.h \
	/usr/local/include/TU/simd/x86/shift.h \
	/usr/local/include/TU/simd/arm/shift.h \
	/usr/local/include/TU/simd/bit_shift.h \
	/usr/local/include/TU/simd/x86/bit_shift.h \
	/usr/local/include/TU/simd/arm/bit_shift.h \
	/usr/local/include/TU/simd/x86/cvt.h \
	/usr/local/include/TU/simd/x86/unpack.h \
	/usr/local/include/TU/simd/arm/cvt.h \
	/usr/local/include/TU/simd/x86/load_store.h \
	/usr/local/include/TU/simd/arm/load_store.h \
	/usr/local/include/TU/simd/insert_extract.h \
	/usr/local/include/TU/simd/x86/insert_extract.h \
	/usr/local/include/TU/simd/arm/insert_extract.h \
	/usr/local/include/TU/simd/dup.h /usr/local/include/TU/simd/logical.h \
	/usr/local/include/TU/simd/x86/logical.h \
	/usr/local/include/TU/simd/x86/logical_base.h \
	/usr/local/include/TU/simd/arm/logical.h \
	/usr/local/include/TU/simd/x86/dup.h \
	/usr/local/include/TU/simd/arm/dup.h \
	/usr/local/include/TU/simd/compare.h \
	/usr/local/include/TU/simd/x86/compare.h \
	/usr/local/include/TU/simd/arm/compare.h \
	/usr/local/include/TU/simd/select.h \
	/usr/local/include/TU/simd/x86/select.h \
	/usr/local/include/TU/simd/arm/select.h \
	/usr/local/include/TU/simd/arithmetic.h \
	/usr/local/include/TU/simd/x86/arithmetic.h \
	/usr/local/include/TU/simd/arm/arithmetic.h \
	/usr/local/include/TU/simd/misc.h \
	/usr/local/include/TU/simd/x86/shuffle.h \
	/usr/local/include/TU/simd/x86/svml.h \
	/usr/local/include/TU/simd/transform.h \
	/usr/local/include/TU/iterator.h /usr/local/include/TU/functional.h \
	/usr/local/include/TU/simd/lookup.h \
	/usr/local/include/TU/simd/x86/lookup.h \
	/usr/local/include/TU/simd/arm/lookup.h \
	/usr/local/include/TU/simd/load_iterator.h \
	/usr/local/include/TU/simd/store_iterator.h \
	/usr/local/include/TU/simd/cvtdown_iterator.h \
	/usr/local/include/TU/simd/cvtup_iterator.h \
	/usr/local/include/TU/simd/shift_iterator.h \
	/usr/local/include/TU/simd/BufTraits.h \
	/usr/local/include/TU/Array++.h /usr/local/include/TU/range.h \
	/usr/local/include/TU/algorithm.h
MyCmdWindow.o: /usr/local/include/TU/GuidedFilter.h \
	/usr/local/include/TU/BoxFilter.h /usr/local/include/TU/Filter2.h \
	/usr/local/include/TU/iterator.h /usr/local/include/TU/tuple.h \
	/usr/local/include/TU/Array++.h /usr/local/include/TU/range.h \
	/usr/local/include/TU/algorithm.h /usr/local/include/TU/TreeFilter.h \
	/usr/local/include/TU/Profiler.h \
	/usr/local/include/TU/WeightedMedianFilter.h \
	/usr/local/include/TU/Quantizer.h /usr/local/include/TU/Vector++.h \
	/usr/local/include/TU/v/FileSelection.h \
	/usr/local/include/TU/v/ModalDialog.h \
	/usr/local/include/TU/v/Dialog.h /usr/local/include/TU/v/CmdPane.h \
	/usr/local/include/TU/v/CmdWindow.h /usr/local/include/TU/v/TUv++.h \
	/usr/local/include/TU/List.h /usr/local/include/TU/Geometry++.h \
	/usr/local/include/TU/Minimize.h /usr/local/include/TU/v/Widget-Xaw.h \
	/usr/local/include/TU/v/Colormap.h /usr/local/include/TU/Image++.h \
	/usr/local/include/TU/pair.h /usr/local/include/TU/v/Notify.h \
	MyCmdWindow.h /usr/local/include/TU/StereoUtility.h \
	/usr/local/include/TU/StereoBase.h /usr/local/include/TU/simd/simd.h \
	/usr/local/include/TU/simd/config.h /usr/local/include/TU/simd/vec.h \
	/usr/local/include/TU/simd/type_traits.h \
	/usr/local/include/TU/simd/x86/type_traits.h \
	/usr/local/include/TU/simd/arm/type_traits.h \
	/usr/local/include/TU/simd/x86/vec.h \
	/usr/local/include/TU/simd/x86/arch.h \
	/usr/local/include/TU/simd/arm/vec.h \
	/usr/local/include/TU/simd/arm/arch.h \
	/usr/local/include/TU/simd/allocator.h \
	/usr/local/include/TU/simd/x86/allocator.h \
	/usr/local/include/TU/simd/arm/allocator.h \
	/usr/local/include/TU/simd/load_store.h \
	/usr/local/include/TU/simd/pack.h /usr/local/include/TU/simd/cvt.h \
	/usr/local/include/TU/simd/zero.h \
	/usr/local/include/TU/simd/x86/zero.h \
	/usr/local/include/TU/simd/arm/zero.h \
	/usr/local/include/TU/simd/cast.h \
	/usr/local/include/TU/simd/x86/cast.h \
	/usr/local/include/TU/simd/arm/cast.h \
	/usr/local/include/TU/simd/shift.h \
	/usr/local/include/TU/simd/x86/shift.h \
	/usr/local/include/TU/simd/arm/shift.h \
	/usr/local/include/TU/simd/bit_shift.h \
	/usr/local/include/TU/simd/x86/bit_shift.h \
	/usr/local/include/TU/simd/arm/bit_shift.h \
	/usr/local/include/TU/simd/x86/cvt.h \
	/usr/local/include/TU/simd/x86/unpack.h \
	/usr/local/include/TU/simd/arm/cvt.h \
	/usr/local/include/TU/simd/x86/load_store.h \
	/usr/local/include/TU/simd/arm/load_store.h \
	/usr/local/include/TU/simd/insert_extract.h \
	/usr/local/include/TU/simd/x86/insert_extract.h \
	/usr/local/include/TU/simd/arm/insert_extract.h \
	/usr/local/include/TU/simd/dup.h /usr/local/include/TU/simd/logical.h \
	/usr/local/include/TU/simd/x86/logical.h \
	/usr/local/include/TU/simd/x86/logical_base.h \
	/usr/local/include/TU/simd/arm/logical.h \
	/usr/local/include/TU/simd/x86/dup.h \
	/usr/local/include/TU/simd/arm/dup.h \
	/usr/local/include/TU/simd/compare.h \
	/usr/local/include/TU/simd/x86/compare.h \
	/usr/local/include/TU/simd/arm/compare.h \
	/usr/local/include/TU/simd/select.h \
	/usr/local/include/TU/simd/x86/select.h \
	/usr/local/include/TU/simd/arm/select.h \
	/usr/local/include/TU/simd/arithmetic.h \
	/usr/local/include/TU/simd/x86/arithmetic.h \
	/usr/local/include/TU/simd/arm/arithmetic.h \
	/usr/local/include/TU/simd/misc.h \
	/usr/local/include/TU/simd/x86/shuffle.h \
	/usr/local/include/TU/simd/x86/svml.h \
	/usr/local/include/TU/simd/transform.h \
	/usr/local/include/TU/functional.h \
	/usr/local/include/TU/simd/lookup.h \
	/usr/local/include/TU/simd/x86/lookup.h \
	/usr/local/include/TU/simd/arm/lookup.h \
	/usr/local/include/TU/simd/load_iterator.h \
	/usr/local/include/TU/simd/store_iterator.h \
	/usr/local/include/TU/simd/cvtdown_iterator.h \
	/usr/local/include/TU/simd/cvtup_iterator.h \
	/usr/local/include/TU/simd/shift_iterator.h \
	/usr/local/include/TU/simd/BufTraits.h /usr/local/include/TU/v/App.h \
	/usr/local/include/TU/Rectify.h /usr/local/include/TU/Warp.h \
	/usr/local/include/TU/Camera++.h
Rectify.o: /usr/local/include/TU/Rectify.h /usr/local/include/TU/Warp.h \
	/usr/local/include/TU/simd/simd.h /usr/local/include/TU/simd/config.h \
	/usr/local/include/TU/simd/vec.h \
	/usr/local/include/TU/simd/type_traits.h \
	/usr/local/include/TU/simd/x86/type_traits.h \
	/usr/local/include/TU/simd/arm/type_traits.h \
	/usr/local/include/TU/simd/x86/vec.h \
	/usr/local/include/TU/simd/x86/arch.h \
	/usr/local/include/TU/simd/arm/vec.h \
	/usr/local/include/TU/simd/arm/arch.h \
	/usr/local/include/TU/simd/allocator.h \
	/usr/local/include/TU/simd/x86/allocator.h \
	/usr/local/include/TU/simd/arm/allocator.h \
	/usr/local/include/TU/simd/load_store.h /usr/local/include/TU/pair.h \
	/usr/local/include/TU/simd/pack.h /usr/local/include/TU/simd/cvt.h \
	/usr/local/include/TU/tuple.h /usr/local/include/TU/simd/zero.h \
	/usr/local/include/TU/simd/x86/zero.h \
	/usr/local/include/TU/simd/arm/zero.h \
	/usr/local/include/TU/simd/cast.h \
	/usr/local/include/TU/simd/x86/cast.h \
	/usr/local/include/TU/simd/arm/cast.h \
	/usr/local/include/TU/simd/shift.h \
	/usr/local/include/TU/simd/x86/shift.h \
	/usr/local/include/TU/simd/arm/shift.h \
	/usr/local/include/TU/simd/bit_shift.h \
	/usr/local/include/TU/simd/x86/bit_shift.h \
	/usr/local/include/TU/simd/arm/bit_shift.h \
	/usr/local/include/TU/simd/x86/cvt.h \
	/usr/local/include/TU/simd/x86/unpack.h \
	/usr/local/include/TU/simd/arm/cvt.h \
	/usr/local/include/TU/simd/x86/load_store.h \
	/usr/local/include/TU/simd/arm/load_store.h \
	/usr/local/include/TU/simd/insert_extract.h \
	/usr/local/include/TU/simd/x86/insert_extract.h \
	/usr/local/include/TU/simd/arm/insert_extract.h \
	/usr/local/include/TU/simd/dup.h /usr/local/include/TU/simd/logical.h \
	/usr/local/include/TU/simd/x86/logical.h \
	/usr/local/include/TU/simd/x86/logical_base.h \
	/usr/local/include/TU/simd/arm/logical.h \
	/usr/local/include/TU/simd/x86/dup.h \
	/usr/local/include/TU/simd/arm/dup.h \
	/usr/local/include/TU/simd/compare.h \
	/usr/local/include/TU/simd/x86/compare.h \
	/usr/local/include/TU/simd/arm/compare.h \
	/usr/local/include/TU/simd/select.h \
	/usr/local/include/TU/simd/x86/select.h \
	/usr/local/include/TU/simd/arm/select.h \
	/usr/local/include/TU/simd/arithmetic.h \
	/usr/local/include/TU/simd/x86/arithmetic.h \
	/usr/local/include/TU/simd/arm/arithmetic.h \
	/usr/local/include/TU/simd/misc.h \
	/usr/local/include/TU/simd/x86/shuffle.h \
	/usr/local/include/TU/simd/x86/svml.h \
	/usr/local/include/TU/simd/transform.h \
	/usr/local/include/TU/iterator.h /usr/local/include/TU/functional.h \
	/usr/local/include/TU/simd/lookup.h \
	/usr/local/include/TU/simd/x86/lookup.h \
	/usr/local/include/TU/simd/arm/lookup.h \
	/usr/local/include/TU/simd/load_iterator.h \
	/usr/local/include/TU/simd/store_iterator.h \
	/usr/local/include/TU/simd/cvtdown_iterator.h \
	/usr/local/include/TU/simd/cvtup_iterator.h \
	/usr/local/include/TU/simd/shift_iterator.h \
	/usr/local/include/TU/simd/BufTraits.h \
	/usr/local/include/TU/Array++.h /usr/local/include/TU/range.h \
	/usr/local/include/TU/algorithm.h /usr/local/include/TU/Image++.h \
	/usr/local/include/TU/Vector++.h /usr/local/include/TU/Camera++.h \
	/usr/local/include/TU/Geometry++.h /usr/local/include/TU/Minimize.h
main.o: MyCmdWindow.h /usr/local/include/TU/StereoUtility.h \
	/usr/local/include/TU/algorithm.h /usr/local/include/TU/Image++.h \
	/usr/local/include/TU/pair.h /usr/local/include/TU/Vector++.h \
	/usr/local/include/TU/Array++.h /usr/local/include/TU/range.h \
	/usr/local/include/TU/iterator.h /usr/local/include/TU/tuple.h \
	/usr/local/include/TU/StereoBase.h /usr/local/include/TU/simd/simd.h \
	/usr/local/include/TU/simd/config.h /usr/local/include/TU/simd/vec.h \
	/usr/local/include/TU/simd/type_traits.h \
	/usr/local/include/TU/simd/x86/type_traits.h \
	/usr/local/include/TU/simd/arm/type_traits.h \
	/usr/local/include/TU/simd/x86/vec.h \
	/usr/local/include/TU/simd/x86/arch.h \
	/usr/local/include/TU/simd/arm/vec.h \
	/usr/local/include/TU/simd/arm/arch.h \
	/usr/local/include/TU/simd/allocator.h \
	/usr/local/include/TU/simd/x86/allocator.h \
	/usr/local/include/TU/simd/arm/allocator.h \
	/usr/local/include/TU/simd/load_store.h \
	/usr/local/include/TU/simd/pack.h /usr/local/include/TU/simd/cvt.h \
	/usr/local/include/TU/simd/zero.h \
	/usr/local/include/TU/simd/x86/zero.h \
	/usr/local/include/TU/simd/arm/zero.h \
	/usr/local/include/TU/simd/cast.h \
	/usr/local/include/TU/simd/x86/cast.h \
	/usr/local/include/TU/simd/arm/cast.h \
	/usr/local/include/TU/simd/shift.h \
	/usr/local/include/TU/simd/x86/shift.h \
	/usr/local/include/TU/simd/arm/shift.h \
	/usr/local/include/TU/simd/bit_shift.h \
	/usr/local/include/TU/simd/x86/bit_shift.h \
	/usr/local/include/TU/simd/arm/bit_shift.h \
	/usr/local/include/TU/simd/x86/cvt.h \
	/usr/local/include/TU/simd/x86/unpack.h \
	/usr/local/include/TU/simd/arm/cvt.h \
	/usr/local/include/TU/simd/x86/load_store.h \
	/usr/local/include/TU/simd/arm/load_store.h \
	/usr/local/include/TU/simd/insert_extract.h \
	/usr/local/include/TU/simd/x86/insert_extract.h \
	/usr/local/include/TU/simd/arm/insert_extract.h \
	/usr/local/include/TU/simd/dup.h /usr/local/include/TU/simd/logical.h \
	/usr/local/include/TU/simd/x86/logical.h \
	/usr/local/include/TU/simd/x86/logical_base.h \
	/usr/local/include/TU/simd/arm/logical.h \
	/usr/local/include/TU/simd/x86/dup.h \
	/usr/local/include/TU/simd/arm/dup.h \
	/usr/local/include/TU/simd/compare.h \
	/usr/local/include/TU/simd/x86/compare.h \
	/usr/local/include/TU/simd/arm/compare.h \
	/usr/local/include/TU/simd/select.h \
	/usr/local/include/TU/simd/x86/select.h \
	/usr/local/include/TU/simd/arm/select.h \
	/usr/local/include/TU/simd/arithmetic.h \
	/usr/local/include/TU/simd/x86/arithmetic.h \
	/usr/local/include/TU/simd/arm/arithmetic.h \
	/usr/local/include/TU/simd/misc.h \
	/usr/local/include/TU/simd/x86/shuffle.h \
	/usr/local/include/TU/simd/x86/svml.h \
	/usr/local/include/TU/simd/transform.h \
	/usr/local/include/TU/functional.h \
	/usr/local/include/TU/simd/lookup.h \
	/usr/local/include/TU/simd/x86/lookup.h \
	/usr/local/include/TU/simd/arm/lookup.h \
	/usr/local/include/TU/simd/load_iterator.h \
	/usr/local/include/TU/simd/store_iterator.h \
	/usr/local/include/TU/simd/cvtdown_iterator.h \
	/usr/local/include/TU/simd/cvtup_iterator.h \
	/usr/local/include/TU/simd/shift_iterator.h \
	/usr/local/include/TU/simd/BufTraits.h \
	/usr/local/include/TU/Profiler.h /usr/local/include/TU/v/App.h \
	/usr/local/include/TU/v/TUv++.h /usr/local/include/TU/List.h \
	/usr/local/include/TU/Geometry++.h /usr/local/include/TU/Minimize.h \
	/usr/local/include/TU/v/Widget-Xaw.h \
	/usr/local/include/TU/v/Colormap.h \
	/usr/local/include/TU/v/CmdWindow.h /usr/local/include/TU/v/CmdPane.h \
	/usr/local/include/TU/Rectify.h /usr/local/include/TU/Warp.h \
	/usr/local/include/TU/Camera++.h
