# This is the makefile for MP2
COMPILER = g++
COMPILER_FLAGS = -std=c++11 -c -g -O0 
#-Wall 
#-Werror
LINKER = g++
#LINKER_OPTS = -lpng


all: NaiveBayes NBAdaBoost


NaiveBayes: naive_main.cpp
	$(COMPILER) naive_main.cpp -o NaiveBayes


NBAdaBoost: ada_main.o adaboost.o naive_bayes_boost.o
	$(LINKER) ada_main.o adaboost.o naive_bayes_boost.o -o NBAdaBoost

ada_main.o: ada_main.cpp adaboost.h
	$(COMPILER) $(COMPILER_FLAGS) ada_main.cpp

adaboost.o: adaboost.cpp adaboost.h naive_bayes_boost.h  
	$(COMPILER) $(COMPILER_FLAGS) adaboost.cpp

naive_bayes_boost.o: naive_bayes_boost.cpp naive_bayes_boost.h
	$(COMPILER) $(COMPILER_FLAGS) naive_bayes_boost.cpp

clean:
	-rm -f *.o NBAdaBoost NaiveBayes
