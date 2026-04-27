all:
	g++ -std=c++17 main.cpp HojaCalculo.cpp -o programa

clean:
	rm -f programa