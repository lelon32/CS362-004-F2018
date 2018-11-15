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
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
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

randomtestresults: randomtestadventurer.c randomtestsmithy.c randomtesttreasuremap.c dominion.c rngs.c

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

randomtestresults: randomtestresults

randomtestadventurer: randomtestadventurer
randomtestsmithy: randomtestsmithy
randomtesttreasuremap: randomtesttreasuremap

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestadventurer randomtestsmithy randomtesttreasuremap
