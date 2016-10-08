all: bitmap

bitmap: bitmap.h bitmap.cpp test.cpp
	g++ bitmap.h bitmap.cpp test.cpp -o bitmap.out
