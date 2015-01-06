DIRS            = common bst avl heap skiplist
BIN             = website/js/bin.js
JS_OBJ         := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.o))
WEBSITE_SRC_DIR = website/public/src

.PHONY: all js clean serve website website-src publish

all:
	-for dir in $(DIRS); do make -C $$dir all; done

js:
	-for dir in $(DIRS); do make -C $$dir js; done
	emmake make $(BIN)

$(BIN): $(JS_OBJ)
	$(CXX) -s NO_EXIT_RUNTIME=1 $(JS_OBJ) -o $(BIN)

clean:
	-for dir in $(DIRS); do make -C $$dir clean; done

serve:
	cd website; broccoli serve

website: js website-src
	rm -rf website/dist
	cd website; broccoli build dist

website-src:
	rm -rf $(WEBSITE_SRC_DIR)/*
	-for dir in $(DIRS); do mkdir          $(WEBSITE_SRC_DIR)/$$dir; \
	                        cp $$dir/*.h   $(WEBSITE_SRC_DIR)/$$dir; \
	                        cp $$dir/*.cpp $(WEBSITE_SRC_DIR)/$$dir; done

publish: website
	git subtree push --prefix website/dist origin gh-pages
