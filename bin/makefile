Parseur: ../src/main.cpp Parse.o recup.o Utilitaire.o
	g++ -o Parseur ../src/main.cpp Utilitaire.o recup.o Parse.o -std=c++11

recup.o: ../src/recup.cpp ../src/recup.h
	g++ -c ../src/recup.cpp -std=c++11

Parse.o: ../src/Parse.cpp ../src/Parse.h
	g++ -c ../src/Parse.cpp -std=c++11

Utilitaire.o: ../src/Utilitaire.cpp ../src/Utilitaire.h
	g++ -c ../src/Utilitaire.cpp -std=c++11
