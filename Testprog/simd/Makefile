
SUBDIR	= cvt_iterator_test		\
	  cvt_mask_iterator_test	\
	  dup				\
	  lookup			\
	  transform			\
	  map_iterator

TARGETS	= all clean depend

$(TARGETS):
	@for d in $(SUBDIR); do				\
	  echo "";					\
	  echo "*** Current directory: $$d ***";	\
	  cd $$d;					\
	  $(MAKE) NAME=$$d $@;				\
	  cd ..;					\
	done
