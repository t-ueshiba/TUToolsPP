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

INCDIRS		= -I../../.. -I$(PREFIX)/include
CPPFLAGS	= -DNDEBUG
CFLAGS		= -O
NVCCFLAGS	= -g
ifeq ($(shell arch),armv7l)
  CPPFLAGS     += -DNEON
else ifeq ($(shell arch), aarch64)
  CPPFLAGS     += -DNEON
else
  CPPFLAGS     += -DSSE4
  CFLAGS       += -msse4
endif
CCFLAGS		= $(CFLAGS)

LIBS		= -lTUv++ -lTUTools++

LINKER		= $(CXX)

BINDIR		= $(PREFIX)/bin
LIBDIR		= $(PREFIX)/lib
INCDIR		= $(PREFIX)/include

#########################
#  Macros set by mkmf	#
#########################
SUFFIX		= .cc:sC .cpp:sC .cu:sC
EXTHDRS		= ../../../TU/Array++.h \
		../../../TU/Geometry++.h \
		../../../TU/Image++.h \
		../../../TU/List.h \
		../../../TU/Manip.h \
		../../../TU/Minimize.h \
		../../../TU/Profiler.h \
		../../../TU/Quantizer.h \
		../../../TU/Vector++.h \
		../../../TU/WeightedMedianFilter.h \
		../../../TU/algorithm.h \
		../../../TU/iterator.h \
		../../../TU/pair.h \
		../../../TU/range.h \
		../../../TU/tuple.h \
		/usr/local/include/TU/v/App.h \
		/usr/local/include/TU/v/CanvasPane.h \
		/usr/local/include/TU/v/CanvasPaneDC.h \
		/usr/local/include/TU/v/CmdPane.h \
		/usr/local/include/TU/v/CmdWindow.h \
		/usr/local/include/TU/v/Colormap.h \
		/usr/local/include/TU/v/DC.h \
		/usr/local/include/TU/v/Menu.h \
		/usr/local/include/TU/v/TUv++.h \
		/usr/local/include/TU/v/Widget-Xaw.h \
		/usr/local/include/TU/v/XDC.h
HDRS		=
SRCS		= main.cc
OBJS		= main.o

#include $(PROJECT)/lib/rtc.mk		# IDLHDRS, IDLSRCS, CPPFLAGS, OBJS, LIBS
#include $(PROJECT)/lib/qt.mk		# MOCSRCS, OBJS
#include $(PROJECT)/lib/cnoid.mk	# CPPFLAGS, LIBS, LIBDIR
#include $(PROJECT)/lib/lib.mk		# PUBHDRS TARGHDRS
include $(PROJECT)/lib/common.mk
###
main.o: ../../../TU/Image++.h ../../../TU/pair.h ../../../TU/Vector++.h \
	../../../TU/Array++.h ../../../TU/range.h ../../../TU/algorithm.h \
	../../../TU/iterator.h ../../../TU/tuple.h \
	/usr/local/include/TU/v/App.h /usr/local/include/TU/v/TUv++.h \
	../../../TU/List.h ../../../TU/Geometry++.h ../../../TU/Minimize.h \
	/usr/local/include/TU/v/Widget-Xaw.h \
	/usr/local/include/TU/v/Colormap.h \
	/usr/local/include/TU/v/CmdWindow.h /usr/local/include/TU/v/CmdPane.h \
	/usr/local/include/TU/v/CanvasPane.h \
	/usr/local/include/TU/v/CanvasPaneDC.h /usr/local/include/TU/v/XDC.h \
	/usr/local/include/TU/v/DC.h ../../../TU/Manip.h \
	/usr/local/include/TU/v/Menu.h ../../../TU/WeightedMedianFilter.h \
	../../../TU/Quantizer.h ../../../TU/Profiler.h
