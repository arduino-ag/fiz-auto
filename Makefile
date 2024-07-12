.PHONY: compile

upload: compile
	arduino-cli upload -b arduino:avr:uno -p /dev/ttyUSB0 --input-dir ./build/ .

compile: create-build-dir
	arduino-cli compile -b arduino:avr:uno --build-cache-path ./build/cache/ --build-path ./build/ ./fiz-auto.ino

create-build-dir:
	mkdir -p ./build/
	mkdir -p ./build-cache/

clean:
	-rm -r ./build/
