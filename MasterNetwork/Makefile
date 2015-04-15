# Makefile for Irrlicht Examples
# It's usually sufficient to change just the target name and source file list
# and be sure that CXX is set to a valid compiler

# Name of the executable created (.exe will be added automatically if necessary)
Target := MasterNetwork
# List of source files, separated by spaces
Sources := src/C*.cpp
SourcesMain := src/main.cpp
# Path to Irrlicht directory, should contain include/ and lib/
IrrlichtHome := ../..
# Path for the executable. Note that Irrlicht.dll should usually also be there for win32 systems
BinPath = ../bin

# general compiler settings (might need to be set when compiling the lib, too)
# preprocessor flags, e.g. defines and include paths
USERCPPFLAGS = 
# compiler flags such as optimization flags
USERCXXFLAGS = -O3 -ffast-math -DCLOG_NO_LOGGING
#USERCXXFLAGS = -g -Wall -ggdb -DCLOG_NO_LOGGING
# linker flags such as additional libraries and link paths
USERLDFLAGS = -lenet -ljsoncpp

####
#no changes necessary below this line
####

CPPFLAGS = $(USERCPPFLAGS) -Iinclude/
CXXFLAGS = $(USERCXXFLAGS) 
LDFLAGS = $(USERLDFLAGS)


# name of the binary - only valid for targets which set SYSTEM
DESTPATH = $(BinPath)/$(Target)

all:
	$(warning Building...)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(Sources) $(LDFLAGS)
	ar rcs lib/lib$(Target).a *.o 
	@$(RM) *.o 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SourcesMain) -o $(DESTPATH) -Llib/ -l$(Target) $(LDFLAGS)

network:
	$(warning Building...)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(Sources) $(LDFLAGS)
	ar rcs lib/lib$(Target).a *.o 
	@$(RM) *.o 
	
test:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SourcesMain) -o $(DESTPATH) -Llib/ -l$(Target) $(LDFLAGS)

clean: clean_linux clean_win32
	$(warning Cleaning...)

clean_linux clean_win32:
	@$(RM) $(DESTPATH)

.PHONY: all clean clean_linux clean_win32

#multilib handling
ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif
#solaris real-time features
ifeq ($(HOSTTYPE), sun4)
LDFLAGS += -lrt
endif
