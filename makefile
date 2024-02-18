client: ApplicationClass.o InputClass.o main.o OpenGLClass.o SystemClass.o
	g++ -o client ApplicationClass.o InputClass.o main.o OpenGLClass.o SystemClass.o -l GL -l X11

ApplicationClass.o: ApplicationClass.cpp
	g++ -c ApplicationClass.cpp

InputClass.o: InputClass.cpp
	g++ -c InputClass.cpp

main.o: main.cpp
	g++ -c main.cpp

OpenGLClass.o: OpenGLClass.cpp
	g++ -c OpenGLClass.cpp

SystemClass.o: SystemClass.cpp
	g++ -c SystemClass.cpp
