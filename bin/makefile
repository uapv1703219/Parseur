Parseur: ../src/main.cpp Parse.o recup.o Utilitaire.o
	g++ -o Parseur ../src/main.cpp Utilitaire.o recup.o Parse.o

Utilitaire.o: ../src/Utilitaire.cpp ../src/Utilitaire.h
	g++ -c ../src/Utilitaire.cpp

recup.o: ../src/recup.cpp ../src/recup.h
	g++ -c ../src/recup.cpp

Parse.o: ../src/Parse.cpp ../src/Parse.h
	g++ -c ../src/Parse.cpp
