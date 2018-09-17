##by @bnatalha

CPPFLAGS += -pthread -std=c++11
INC =-I include

.PHONY: all clean tetris

#compilar tudo
all: bin/thretris clean


#
#
#gerar executaveis
bin/thretris: bin/main.o bin/functest.o bin/fileman.o
	g++ $^ -o $@ -pthread

#gerar objetos
bin/main.o: src/main.cpp
	g++ $(CPPFLAGS) $< $(INC) -c -o $@

bin/functest.o: src/functest.cpp
	g++ $(CPPFLAGS) $< $(INC) -c -o $@

bin/fileman.o: src/fileman.cpp
	g++ $(CPPFLAGS) $< $(INC) -c -o $@

#remover .o's
clean:
	$(RM) bin/*.o

#executar binario
tetris:
	bin/thretris