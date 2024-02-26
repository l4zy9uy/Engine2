client: ApplicationClass.o InputClass.o main.o OpenGLClass.o SystemClass.o
	g++ -o client ApplicationClass.o InputClass.o main.o OpenGLClass.o SystemClass.o -l GL -l X11

ApplicationClass.o: src/ApplicationClass.cpp
	g++ -c ApplicationClass.cpp

InputClass.o: src/InputClass.cpp
	g++ -c InputClass.cpp

main.o: final/main.cpp
	g++ -c main.cpp

OpenGLClass.o: src/OpenGLClass.cpp
	g++ -c OpenGLClass.cpp

SystemClass.o: src/SystemClass.cpp
	g++ -c SystemClass.cpp
