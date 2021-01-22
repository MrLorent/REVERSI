CC= g++
CFLAGS= -Wall -lstdc++
LDFLAGS = -lm

DEBUG=no
ifeq ($(DEBUG), yes)
CFLAGS += -g
endif

reversi.exe: main.o jeu.o joueur.o plateau.o jeton.o sauvegarde.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: modele.h vue.h controleur.h
jeu.o : modele.h vue.h controleur.h
joueur.o: modele.h vue.h controleur.h
plateau.o: modele.h vue.h controleur.h
jeton.o: modele.h vue.h controleur.h
sauvegarde.o: modele.h vue.h controleur.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean :
	rm -f *.o
