CC=g++
CFLAGS=-m32 -std=c++11 -c -D_SERVER -D_LINUX -fpermissive -w -I../Shared -I../Network/Core -I../Libraries -I../Network/Core/RakNet -I../Libraries/Squirrel -I.
SOURCES=$(wildcard *.cpp)
SOURCES+=$(wildcard Scripting/Natives/*.cpp)
SOURCES+=$(wildcard Entity/*.cpp)
SOURCES+=$(wildcard Network/*.cpp)
SOURCES+=../Shared/CString.cpp ../Shared/SharedUtility.cpp ../Shared/Threading/CMutex.cpp ../Shared/Threading/CThread.cpp
SOURCES+=../Shared/CLogFile.cpp ../Shared/CSettings.cpp ../Shared/Network/CBitStream.cpp
SOURCES+=../Network/Core/CNetworkServer.cpp ../Shared/CXML.cpp
SOURCES+=$(wildcard ../Network/Core/RakNet/*.cpp)
SOURCES+=$(wildcard ../Libraries/tinyxml/*.cpp)
SOURCES+=$(wildcard ../Libraries/Squirrel/*.cpp)
SOURCES+=$(wildcard ../Shared/Scripting/*.cpp)
SOURCES+=$(wildcard ../Shared/Scripting/Natives/*.cpp)
SOURCES+=$(wildcard ../Shared/Scripting/ResourceSystem/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
LUA_OBJECTS=$(wildcard ../Libraries/lua/*.o)
EXECUTABLE=../Binary/ivmp-svr

all: $(SOURCES) dir $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LUA_OBJECTS) -m32 -lpthread -ldl -o $@

dir:
	mkdir -p ../Binary

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -Rf $(OBJECTS) $(EXECUTABLE)