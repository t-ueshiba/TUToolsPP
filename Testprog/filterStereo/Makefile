SUBDIR	= stereoTest			\
	  stereoTime			\
	  #stereoGUI			\
	  #stereoGUIWithoutRectification

TARGETS	= all clean depend

$(TARGETS):
	@for d in $(SUBDIR); do				\
	  echo "";					\
	  echo "*** Current directory: $$d ***";	\
	  cd $$d;					\
	  $(MAKE) NAME=$$d $@;				\
	  cd ..;					\
	done
