CC=g++
CFLAGS=-std=c++11 -I./include -I./poly2tri -L./lib
LDFLAGS=-Llib -lpthread -lfftw3 -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpoly2tri
SRC=./src
INC=./include
OUT=./output
P2T=./poly2tri
LIB=./lib
EXE=game

all: clean $(LIB)/libpoly2tri.a $(EXE)

$(EXE): $(OUT)/main.o $(OUT)/Camera.o $(OUT)/Air.o $(OUT)/Entity.o $(OUT)/TestBox.o $(OUT)/Vortex.o $(OUT)/Wall.o $(OUT)/WhistleMan.o $(OUT)/InputManager.o $(OUT)/Game.o $(OUT)/Attractor.o $(OUT)/Bound.o $(OUT)/Force.o $(OUT)/Friction.o $(OUT)/World.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(OUT)/main.o: $(SRC)/main.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Camera.o: $(SRC)/Camera/Camera.cpp $(INC)/Camera/Camera.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Air.o: $(SRC)/Entity/Air.cpp $(INC)/Entity/Air.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Entity.o: $(SRC)/Entity/Entity.cpp $(INC)/Entity/Entity.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/TestBox.o: $(SRC)/Entity/TestBox.cpp $(INC)/Entity/TestBox.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Vortex.o: $(SRC)/Entity/Vortex.cpp $(INC)/Entity/Vortex.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Wall.o: $(SRC)/Entity/Wall.cpp $(INC)/Entity/Wall.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/WhistleMan.o: $(SRC)/Entity/WhistleMan.cpp $(INC)/Entity/WhistleMan.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/InputManager.o: $(SRC)/Management/InputManager.cpp $(INC)/Management/InputManager.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Game.o: $(SRC)/Game/Game.cpp $(INC)/Game/Game.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Attractor.o: $(SRC)/Physic/Attractor.cpp $(INC)/Physic/Attractor.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Bound.o: $(SRC)/Physic/Bound.cpp $(INC)/Physic/Bound.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Force.o: $(SRC)/Physic/Force.cpp $(INC)/Physic/Force.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/Friction.o: $(SRC)/Physic/Friction.cpp $(INC)/Physic/Friction.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/World.o: $(SRC)/World/World.cpp $(INC)/World/World.h
	$(CC) -c $< -o $@ $(CFLAGS)


$(LIB)/libpoly2tri.a: $(OUT)/shapes.o $(OUT)/advancing_front.o $(OUT)/cdt.o $(OUT)/sweep_context.o $(OUT)/sweep.o
	ar -rv $@ -o $^
$(OUT)/shapes.o: $(P2T)/common/shapes.cpp $(P2T)/common/shapes.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/advancing_front.o: $(P2T)/sweep/advancing_front.cpp $(P2T)/sweep/advancing_front.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/cdt.o: $(P2T)/sweep/cdt.cpp $(P2T)/sweep/cdt.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/sweep_context.o: $(P2T)/sweep/sweep_context.cpp $(P2T)/sweep/sweep_context.h
	$(CC) -c $< -o $@ $(CFLAGS)
$(OUT)/sweep.o: $(P2T)/sweep/sweep.cpp $(P2T)/sweep/sweep.h
	$(CC) -c $< -o $@ $(CFLAGS)


clean:
	rm -f $(OUT)/*

.PHONY: all clean
