.PHONY: upload build create-build-dir clean

.DEFAULT_GOAL := build

upload: build
	arduino-cli upload -b arduino:avr:uno -p /dev/ttyUSB0 --input-dir ./build/ .

build: create-build-dir fiz-auto.ino
	arduino-cli compile -b arduino:avr:uno --build-cache-path ./build/cache/ --build-path ./build/ ./fiz-auto.ino

create-build-dir:
	mkdir -p ./build/
	mkdir -p ./build/cache/

clean:
	-rm -r ./build/
