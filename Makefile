DIRS   = avl heap skiplist
BIN    = website/js/bin.js
JSOBJ := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.o))

.PHONY: all js clean website website-src publish

all:
	-for dir in $(DIRS); do make -C $$dir all; done

js:
	-for dir in $(DIRS); do make -C $$dir js; done
	emmake make jsbin

jsbin:
	$(CXX) -s NO_EXIT_RUNTIME=1 $(JSOBJ) -o $(BIN)

clean:
	-for dir in $(DIRS); do make -C $$dir clean; done
	rm -f $(BIN)

website: js website-src

website-src:
	rm -rf website/src/*
	-for dir in $(DIRS); do mkdir website/src/$$dir; \
	                        cp $$dir/*.h website/src/$$dir; \
	                        cp $$dir/*.cpp website/src/$$dir; done

publish: website
	git subtree push --prefix website origin gh-pages
