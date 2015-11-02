#CXXFLAGS += -Wall -static -g -O2 -fPIC

bin_PROGRAMS = example1 echoserver

INCLUDES = -I../deps
CPPFLAGS = -std=c++0x
LDFLAGS  = -L../lib -lae -lrt

example1_SOURCES          = example1.cpp

echoserver_SOURCES        = echoserver.cpp
