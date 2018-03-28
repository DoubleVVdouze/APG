all: compiler 

compiler: 
	g++ -IInclude main.cpp Source/Client.cpp Source/DataFile.cpp Source/loader.cpp Source/Server.cpp -o main.exe 
nettoyer: 
	rm *.o 
