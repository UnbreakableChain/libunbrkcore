CXX = c99 
CXXFLAGS = -Wall -Wextra
TESTFLAGS = `pkg-config --cflags --libs glib-2.0`
INC=./include
SRC=./src
OBJ=./obj
BIN=./bin
TEST=./tests
TESTBIN=$(BIN)/tests
DOXIFILE=./doc/doxys/Doxyfile.in


# Build release
release: CXXFLAGS += -O3
release: $(BIN)/libunbrkcore.a

# Build debug
debug: CXXFLAGS += -g
debug: $(BIN)/libunbrkcore.a

# Build library 
$(BIN)/libunbrkcore.a: $(OBJ)/ub_date.o $(OBJ)/ub_chain.o
	mkdir -p $(BIN)
	ar rc $@ $^ 

$(OBJ)/ub_chain.o: $(SRC)/ub_chain.c $(INC)/ub_date.h $(INC)/ub_link.h $(INC)/ut/uthash.h
	mkdir -p $(OBJ)
	$(CXX) -I$(INC) $(CXXFLAGS) -c -o $@ $<

$(OBJ)/ub_date.o: $(SRC)/ub_date.c $(INC)/ub_date.h
	mkdir -p $(OBJ)
	$(CXX) -I$(INC) $(CXXFLAGS) -c -o $@ $<

# Clean
clean:
	rm $(BIN)/* $(INC)/~* $(OBJ)/*.o


# Build documentation
doc: $(INC)/* $(DOXIFILE)
	doxygen $(DOXIFILE)


# Build and run tests
tests: $(TESTBIN)/ub_date_tests $(TESTBIN)/ub_chain_tests

$(TESTBIN)/ub_date_tests: $(TEST)/ub_date_tests.c debug 
	$(CXX) -I$(INC) $(CXXFLAGS) -o $@ $< -L$(BIN) -lunbrkcore $(TESTFLAGS)
	$@ 

$(TESTBIN)/ub_chain_tests: $(TEST)/ub_chain_tests.c debug 
	$(CXX) -I$(INC) $(CXXFLAGS)  -o $@ $< -L$(BIN) -lunbrkcore $(TESTFLAGS)
	$@ 
