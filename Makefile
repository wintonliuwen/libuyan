DIRS = lib app

all:
	for dir in $(DIRS); do \
		(cd $$dir && $(MAKE)) || exit 1;\
	done

install:
	for dir in $(DIRS);do \
		(cd $$dir && $(MAKE) install) || exit 1;\
	done

clean:
	for dir in $(DIRS); do \
		(cd $$dir && $(MAKE) clean) || exit 1; \
	done

