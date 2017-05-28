all: rsa

rsa: RSAprog.cpp
	g++ -o rsa -O3 RSAprog.cpp