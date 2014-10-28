all: build

setup:
	mkdir -p lib
	mkdir -p lib/TestRunner
	mkdir -p src
	cp TestRunner.* lib/TestRunner/
	cp examples/boilerplate/boilerplate.pde src/

build: setup
	ino build

clean:
	rm -rf lib
	rm -rf src
	rm -rf .build
