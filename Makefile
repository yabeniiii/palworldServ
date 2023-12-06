.PHONY: setup build clean build-release

setup:
	mkdir build && cd build && cmake -GNinja ..

build:
	cd build && cmake --build .

clean:
	rm -rf build

build-release:
	cd build && cmake -GNinja -DCMAKE_BUILD_TYPE=Release .. && cmake --build . 
