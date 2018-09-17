##by @bnatalha

CPPFLAGS += -pthread -std=c++11
INC =-I include

.PHONY: all clean tetris

#compilar tudo
all: bin/thretris clean


#
#
#gerar executaveis
bin/thretris: bin/thread_in.o bin/tetris.o
	g++ $^ -o $@ -pthread

#gerar objetos
bin/thread_in.o: src/thread_in.cpp
	g++ $(CPPFLAGS) $< $(INC) -c -o $@

bin/tetris.o: src/tetris.cpp
	g++ $(CPPFLAGS) $< $(INC) -c -o $@


#remover .o's
clean:
	$(RM) bin/*.o