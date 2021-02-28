
build/src/main.o: src/main.cpp src/main.h
	mkdir -p build/src
	g++ -I. -I./src src/main.cpp -c -o build/src/main.o

build/src/sensor/ars4b.o: src/sensor/ars4b.cpp src/sensor/ars4b.h
	mkdir -p build/src/sensor
	g++ -I. -I.src src/sensor/ars4b.cpp -c -o build/src/sensor/ars4b.o



all: build/src/main.o build/src/sensor/ars4b.o
	g++ build/src/main.o build/src/sensor/ars4b.o -o foot

.PHONY: all

run:
	./build/foot

