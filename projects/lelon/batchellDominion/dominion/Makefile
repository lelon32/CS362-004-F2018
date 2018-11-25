CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestsmithy: randomtestsmithy.c dominion.o rngs.o
	gcc -o randomtestsmithy -g  randomtestsmithy.c dominion.o rngs.o $(CFLAGS)

randomtesttreasuremap: randomtesttreasuremap.c dominion.o rngs.o
	gcc -o randomtesttreasuremap -g  randomtesttreasuremap.c dominion.o rngs.o $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

testresults: unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c randomtestadventurer.c randomtestsmithy.c randomtesttreasuremap.c dominion.c rngs.c
# Unit testing instruction
	echo "Result for running dominion unit tests:" > unittestresults.out

	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov unittest1.c -b >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov unittest2.c -b >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov unittest3.c -b >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov unittest4.c -b >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	echo "cardtest1 segmentation faults - will not be run" >> unittestresults.out
	gcov cardtest1.c -b >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov cardtest2.c -b >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov cardtest3.c -b >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov cardtest4.c -b >> unittestresults.out

	gcov dominion.c -b >> unittestresults.out


# Random testing instruction
	echo "Result for running adventurer random tests:" > randomtestadventurer.out

	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov randomtestadventurer.c -b >> randomtestadventurer.out

	echo "Result for running smithy random tests:" > randomtestsmithy.out

	echo "randomtestsmithy.c:" >> randomtestsmithy.out
	gcc -o randomtestsmithy -g randomtestsmithy.c dominion.o rngs.o $(CFLAGS)
	./randomtestsmithy >> randomtestsmithy.out
	gcov randomtestsmithy.c -b >> randomtestsmithy.out

	echo "Result for running treasuremap random tests:" > randomtesttreasuremap.out

	echo "randomtesttreasuremap.c:" >> randomtesttreasuremap.out
	gcc -o randomtesttreasuremap -g randomtesttreasuremap.c dominion.o rngs.o $(CFLAGS)
	./randomtesttreasuremap >> randomtesttreasuremap.out
	gcov randomtesttreasuremap.c -b >> randomtesttreasuremap.out

testresults: testresults

randomtestadventurer: randomtestadventurer
randomtestsmithy: randomtestsmithy
randomtesttreasuremap: randomtesttreasuremap

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestadventurer randomtestsmithy randomtesttreasuremap
