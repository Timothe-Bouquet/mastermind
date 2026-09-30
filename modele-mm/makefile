# ______________ parametres de compilation
CFLAGS=-Wall --pedantic

# ______________ excecutables
all: mastermind-demo mastermind-test

# ______________ modele
mastermind-demo: mastermind-demo.o mastermind.o stat-essai.o combinaison.o 
	gcc $^ -o $@
mastermind-demo.o: mastermind-demo.c mastermind.h combinaison.h stat-essai.h
	gcc -c $< -o $@ $(CFLAGS)

mastermind-test: mastermind-test.o mastermind.o stat-essai.o combinaison.o 
	gcc $^ -o $@
mastermind-test.o: mastermind-test.c mastermind.h combinaison.h stat-essai.h
	gcc -c $< -o $@ $(CFLAGS)

mastermind.o: mastermind.c mastermind.h combinaison.h stat-essai.h
	gcc -c $< -o $@ $(CFLAGS)
combinaison.o: combinaison.c combinaison.h
	gcc -c $< -o $@ $(CFLAGS)
stat-essai.o: stat-essai.c stat-essai.h
	gcc -c $< -o $@ $(CFLAGS)

# ______________ nettoyage
clean:
	rm -rf *.o *~ 

mrproper: clean
	rm -rf mastermind-demo mastermind-test

