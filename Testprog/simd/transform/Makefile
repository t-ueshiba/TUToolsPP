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

INCDIRS		= -I../../..
CPPFLAGS	= -DNDEBUG #-DTU_SIMD_DEBUG
CFLAGS		= -g
NVCCFLAGS	= -g
ifeq ($(shell arch), armv7l)
  CPPFLAGS     += -DNEON
else ifeq ($(shell arch), aarch64)
  CPPFLAGS     += -DNEON
else
  CPPFLAGS     += -DSSE2
endif
CCFLAGS		= $(CFLAGS)

LIBS		=
LINKER		= $(CXX)

BINDIR		= $(PREFIX)/bin
LIBDIR		= $(PREFIX)/lib
INCDIR		= $(PREFIX)/include

#########################
#  Macros set by mkmf	#
#########################
SUFFIX		= .cc:sC .cpp:sC .cu:sC
EXTHDRS		= ../../../TU/functional.h \
		../../../TU/iterator.h \
		../../../TU/simd/arithmetic.h \
		../../../TU/simd/arm/arch.h \
		../../../TU/simd/arm/arithmetic.h \
		../../../TU/simd/arm/bit_shift.h \
		../../../TU/simd/arm/cast.h \
		../../../TU/simd/arm/cvt.h \
		../../../TU/simd/arm/insert_extract.h \
		../../../TU/simd/arm/load_store.h \
		../../../TU/simd/arm/logical.h \
		../../../TU/simd/arm/select.h \
		../../../TU/simd/arm/shift.h \
		../../../TU/simd/arm/type_traits.h \
		../../../TU/simd/arm/vec.h \
		../../../TU/simd/arm/zero.h \
		../../../TU/simd/bit_shift.h \
		../../../TU/simd/cast.h \
		../../../TU/simd/config.h \
		../../../TU/simd/cvt.h \
		../../../TU/simd/insert_extract.h \
		../../../TU/simd/load_store.h \
		../../../TU/simd/load_store_iterator.h \
		../../../TU/simd/logical.h \
		../../../TU/simd/select.h \
		../../../TU/simd/shift.h \
		../../../TU/simd/transform.h \
		../../../TU/simd/type_traits.h \
		../../../TU/simd/vec.h \
		../../../TU/simd/x86/arch.h \
		../../../TU/simd/x86/arithmetic.h \
		../../../TU/simd/x86/bit_shift.h \
		../../../TU/simd/x86/cast.h \
		../../../TU/simd/x86/cvt.h \
		../../../TU/simd/x86/insert_extract.h \
		../../../TU/simd/x86/load_store.h \
		../../../TU/simd/x86/logical.h \
		../../../TU/simd/x86/logical_base.h \
		../../../TU/simd/x86/select.h \
		../../../TU/simd/x86/shift.h \
		../../../TU/simd/x86/type_traits.h \
		../../../TU/simd/x86/unpack.h \
		../../../TU/simd/x86/vec.h \
		../../../TU/simd/x86/zero.h \
		../../../TU/simd/zero.h \
		../../../TU/tuple.h \
		../../../TU/type_traits.h
HDRS		=
SRCS		= main.cc
OBJS		= main.o

#include $(PROJECT)/lib/rtc.mk		# IDLHDRS, IDLSRCS, CPPFLAGS, OBJS, LIBS
#include $(PROJECT)/lib/qt.mk		# MOCSRCS, OBJS
#include $(PROJECT)/lib/cnoid.mk	# CPPFLAGS, LIBS, LIBDIR
#include $(PROJECT)/lib/lib.mk		# PUBHDRS TARGHDRS
include $(PROJECT)/lib/common.mk
###
main.o: ../../../TU/simd/transform.h ../../../TU/iterator.h \
	../../../TU/tuple.h ../../../TU/type_traits.h \
	../../../TU/functional.h ../../../TU/simd/cvt.h \
	../../../TU/simd/zero.h ../../../TU/simd/vec.h \
	../../../TU/simd/config.h ../../../TU/simd/type_traits.h \
	../../../TU/simd/x86/type_traits.h ../../../TU/simd/arm/type_traits.h \
	../../../TU/simd/x86/vec.h ../../../TU/simd/x86/arch.h \
	../../../TU/simd/arm/vec.h ../../../TU/simd/arm/arch.h \
	../../../TU/simd/x86/zero.h ../../../TU/simd/arm/zero.h \
	../../../TU/simd/cast.h ../../../TU/simd/x86/cast.h \
	../../../TU/simd/arm/cast.h ../../../TU/simd/shift.h \
	../../../TU/simd/x86/shift.h ../../../TU/simd/arm/shift.h \
	../../../TU/simd/bit_shift.h ../../../TU/simd/x86/bit_shift.h \
	../../../TU/simd/arm/bit_shift.h ../../../TU/simd/x86/cvt.h \
	../../../TU/simd/x86/unpack.h ../../../TU/simd/arm/cvt.h \
	../../../TU/simd/load_store_iterator.h ../../../TU/simd/load_store.h \
	../../../TU/simd/x86/load_store.h ../../../TU/simd/arm/load_store.h \
	../../../TU/simd/arithmetic.h ../../../TU/simd/logical.h \
	../../../TU/simd/x86/logical.h ../../../TU/simd/x86/logical_base.h \
	../../../TU/simd/arm/logical.h ../../../TU/simd/x86/arithmetic.h \
	../../../TU/simd/select.h ../../../TU/simd/x86/select.h \
	../../../TU/simd/arm/select.h ../../../TU/simd/insert_extract.h \
	../../../TU/simd/x86/insert_extract.h \
	../../../TU/simd/arm/insert_extract.h \
	../../../TU/simd/arm/arithmetic.h
