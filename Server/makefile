CC=g++
CFLAGS=-m32 -std=gnu++11 -c -D_SERVER -D_LINUX -fpermissive -w -I../Shared -I../Libraries -I../Libraries/RakNet -I../Libraries/Squirrel -I.
SOURCES=$(wildcard *.cpp)
SOURCES+=$(wildcard Scripting/Natives/*.cpp)
SOURCES+=$(wildcard Entity/*.cpp)
SOURCES+=$(wildcard Network/*.cpp)
SOURCES+=../Shared/CString.cpp ../Shared/SharedUtility.cpp ../Shared/Threading/CMutex.cpp ../Shared/Threading/CThread.cpp
SOURCES+=../Shared/CLogFile.cpp ../Shared/CSettings.cpp ../Shared/Network/CBitStream.cpp
SOURCES+=../Shared/CXML.cpp
SOURCES+=$(wildcard ../Libraries/RakNet/*.cpp)
SOURCES+=$(wildcard ../Libraries/tinyxml/*.cpp)
SOURCES+=$(wildcard ../Libraries/Squirrel/*.cpp)
SOURCES+=$(wildcard ../Shared/Scripting/*.cpp)
SOURCES+=$(wildcard ../Shared/Scripting/Natives/*.cpp)
SOURCES+=$(wildcard ../Shared/Scripting/ResourceSystem/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
LUA_OBJECTS=$(wildcard ../Libraries/lua/*.o)
EXECUTABLE=../Files/ivn-svr

all: $(SOURCES) dir $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LUA_OBJECTS) -m32 -lpthread -ldl -o $@

dir:
	mkdir -p ../Files

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -Rf $(OBJECTS) $(EXECUTABLE)