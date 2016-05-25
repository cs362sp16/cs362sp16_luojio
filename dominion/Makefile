CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2 testdominion player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM


#################### unit test compile ##################

test_result:
	$(info --------------------------------------------------------------)
	$(info FILE:	   unitestresults.out)
	$(info ASSIGNMENT: CS362 DEBUG ASSIGNMENT 2)
	$(info AUTHOR:     Jiongcheng Luo)
	$(info DATE:       4/26/2016)
	$(info --------------------------------------------------------------)

	gcc -fprofile-arcs -ftest-coverage UnitTests/unittest1.c -lm
	./a.out
	gcov unittest1.c
	rm a.out

	gcc -fprofile-arcs -ftest-coverage UnitTests/unittest2.c -lm
	./a.out
	gcov unittest2.c
	rm a.out

	gcc -fprofile-arcs -ftest-coverage UnitTests/unittest3.c -lm
	./a.out
	gcov unittest3.c
	rm a.out

	gcc -fprofile-arcs -ftest-coverage UnitTests/unittest4.c -lm
	./a.out
	gcov unittest4.c
	rm a.out

	gcc -fprofile-arcs -ftest-coverage CardTests/cardtest1.c -lm
	./a.out
	gcov cardtest1.c
	rm a.out

	gcc -fprofile-arcs -ftest-coverage CardTests/cardtest2.c -lm
	./a.out
	gcov cardtest2.c
	rm a.out

	gcc -fprofile-arcs -ftest-coverage CardTests/cardtest3.c -lm
	./a.out
	gcov cardtest3.c
	rm a.out

	gcc -fprofile-arcs -ftest-coverage CardTests/cardtest4.c -lm
	./a.out
	gcov cardtest4.c
	rm a.out

result:
	make test_result > unittestresult.out


#################### random test compile ##################

adven_test:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 RandomTests/randomtestadventurer.c -o randomtestadventurer -lm -g
	./randomtestadventurer 42
	gcov -f -b randomtestadventurer.c 

card1_test:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 RandomTests/randomtestcard1.c -o randomtestcard1 -lm -g
	./randomtestcard1 42
	gcov -f -b randomtestcard1.c 


card2_test:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 RandomTests/randomtestcard2.c -o randomtestcard2 -lm -g
	./randomtestcard2 42
	gcov -f -b randomtestcard2.c 

random_result:
	make adven_test > randomtestadventurer.out
	#cat dominion.c.gcov >> randomtestadventurer.out
	make card1_test > randomtestcard1.out
	make card2_test > randomtestcard2.out



###################  dominiontester(HW4) ######################
tester:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 testdominion.c -o testdominion -lm -g
	./testdominion 42
	

tester_result:
	make tester
	gcov -f -b testdominion.c > testdominion.ou
	
testdominion:
	gcc -std=c99 testdominion.c -o testdominion -lm -g

cleantest:
	rm -r -f temp1 temp2 diff1.out diff2.out
