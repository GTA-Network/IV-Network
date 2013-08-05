CC=g++
CFLAGS=-m32 -std=c++11 -c -D_SERVER -D_LINUX -fpermissive -w -I../Shared -I../Network/Core -I../Libraries -I../Network/Core/RakNet -I../Libraries/Squirrel -I.
SOURCES=$(wildcard *.cpp)
SOURCES+=../Shared/CString.cpp ../Shared/SharedUtility.cpp ../Shared/Threading/CMutex.cpp ../Shared/Threading/CThread.cpp
SOURCES+=../Shared/CLogFile.cpp ../Shared/CSettings.cpp ../Shared/Network/CBitStream.cpp
SOURCES+=../Network/Core/CNetworkServer.cpp ../Shared/CXML.cpp
SOURCES+=$(wildcard ../Network/Core/RakNet/*.cpp)
SOURCES+=$(wildcard ../Libraries/tinyxml/*.cpp)
SOURCES+=$(wildcard ../Libraries/Squirrel/*.cpp)
SOURCES+=$(wildcard ../Shared/Scripting/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../Binary/ivmp-svr

all: $(SOURCES) dir $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -m32 -lpthread -ldl -o $@

dir:
	mkdir ../Binary

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -Rf $(OBJECTS) $(EXECUTABLE)