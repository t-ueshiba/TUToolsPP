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
CPPFLAGS	= -DNDEBUG
CFLAGS		= -O3
NVCCFLAGS	= -g
ifeq ($(shell arch), armv7l)
  CPPFLAGS     += -DNEON
else ifeq ($(shell arch), aarch64)
  CPPFLAGS     += -DNEON
else
  CPPFLAGS     += -DSSE4
  CFLAGS       += -msse4
endif
CCFLAGS		= $(CFLAGS)

LIBS		= -lTUTools++
LINKER		= $(CXX)

BINDIR		= $(PREFIX)/bin
LIBDIR		= $(PREFIX)/lib
INCDIR		= $(PREFIX)/include

#########################
#  Macros set by mkmf	#
#########################
SUFFIX		= .cc:sC .cpp:sC .cu:sC
EXTHDRS		= ../../../TU/Array++.h \
		../../../TU/Camera++.h \
		../../../TU/Geometry++.h \
		../../../TU/Image++.h \
		../../../TU/Manip.h \
		../../../TU/Minimize.h \
		../../../TU/Profiler.h \
		../../../TU/Quantizer.h \
		../../../TU/Vector++.h \
		../../../TU/algorithm.h \
		../../../TU/iterator.h \
		../../../TU/pair.h \
		../../../TU/range.h \
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
main.o: ../../../TU/Image++.h ../../../TU/pair.h ../../../TU/type_traits.h \
	../../../TU/Manip.h ../../../TU/Camera++.h ../../../TU/Geometry++.h \
	../../../TU/Minimize.h ../../../TU/Vector++.h ../../../TU/Array++.h \
	../../../TU/range.h ../../../TU/iterator.h ../../../TU/tuple.h \
	../../../TU/algorithm.h ../../../TU/Quantizer.h \
	../../../TU/Profiler.h
