CXX = g++ -Wall -std=c++11 

LDFLAGS = -lSDL2 -lSDL2_image
EXE = bounce

all: $(EXE)

SOURCE=*.cpp

$(EXE): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o$(EXE) $(LDFLAGS)

clean:

	rm -f $(MYPROGRAM)