all: example.cpp defer.h
	g++ -g -O0 example.cpp -std=c++17 -o example

clean:
	rm -f example core *.o
