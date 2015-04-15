# Subdirectorio src: main.cc
# Subdirectorio lib: Aplicacion.cc Posicion.cc Punto.cc Menu.cc ItemDeMenu.cc
# Subdirectorio include: Aplicacion.h Posicion.h Punto.h Menu.h ItemDeMenu.h
.PHONY= doc clean

CC=g++
#OPTIONS= -ggdb -g -Wall
OPTIONS = -O3 -ffast-math
OUTPUTDIR=../bin
LIBDIR=lib
INCLUDEDIR=include
MYLIBS=-L../MasterNetwork/lib -lMasterNetwork -L../3rdparty/enet -lenet -ljsoncpp -ldl -lpthread
ENET=../3rdparty/enet/include
JSON=../3rdparty/jsoncpp0.6.0_rc2/include
NETWORK=../MasterNetwork/include
OBJ_S=Entity.o Object.o Character.o Player.o  cnetworkserverdispatcherJSON.o \
 Server.o MasterMan.o MasterManAPI.o Client.o MapReader.o Dot.o Wall.o ExitDoor.o \
    Bot.o Barredor.o Gun.o FireDoor.o DataGen.o
ALLINCLUDES=-I$(INCLUDEDIR) -I$(ENET)  -I$(NETWORK) -I$(JSON)

OBJ = $(patsubst %,$(LIBDIR)/%,$(OBJ_S))

.PHONY: all clean doc

all: TestMasterMan MasterServer TestJson PruebaMemoriaMan

PruebaMemoriaMan: ./src/PruebaMemoriaMan.cpp $(OBJ)
	$(CC) $(OPTIONS) $(ALLINCLUDES) ./src/PruebaMemoriaMan.cpp $(OBJ) $(MYLIBS) -o $(OUTPUTDIR)/PruebaMemoriaMan
	
MasterServer: ./src/MasterServer.cpp $(OBJ)
	$(CC) $(OPTIONS) $(ALLINCLUDES) ./src/MasterServer.cpp $(OBJ) $(MYLIBS) -o $(OUTPUTDIR)/MasterServer
	
#MasterClient: ./src/MasterClient.cpp $(OBJ)
#	$(CC) $(OPTIONS) $(ALLINCLUDES) ./src/MasterClient.cpp $(OBJ) $(MYLIBS) -o $(OUTPUTDIR)/MasterClient
	
TestMasterMan: ./src/TestMasterMan.cpp $(OBJ)
	$(CC) $(OPTIONS) $(ALLINCLUDES) ./src/TestMasterMan.cpp $(OBJ) $(MYLIBS) -o $(OUTPUTDIR)/TestMasterMan
	
TestJson: ./src/TestJson.cpp $(OBJ)
	$(CC) $(OPTIONS) $(ALLINCLUDES) ./src/TestJson.cpp $(OBJ) $(MYLIBS) -o $(OUTPUTDIR)/TestJson

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) -c $(ALLINCLUDES) -o  $@ $<

clean:
	rm -f $(OBJ)
	rm -f $(OUTPUTDIR)/TestMasterMan $(OUTPUTDIR)/MasterClient $(OUTPUTDIR)/MasterServer $(OUTPUTDIR)/TestJson
