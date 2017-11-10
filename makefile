CC= g++ 
#PLATFORM= -DCYGWIN		# uncomment for cygwin
LDFLAGS= -lncurses -lrt	# libraries need for dragonfly
INCPATH=			# path to engine includes
ENG= 				# dragonfly engine
GAMESRC= event.cpp\
     eventstep.cpp\
     eventkeyboard.cpp\
     eventmouse.cpp\
     eventcollision.cpp\
     eventout.cpp\
     clock.cpp\
     manager.cpp\
     inputmanager.cpp\
     gamemanager.cpp\
     graphicsmanager.cpp\
     worldmanager.cpp \
     logmanager.cpp \
     position.cpp\
     object.cpp \
     objectlist.cpp \
     objectlistiterator.cpp\
     mushroom.cpp\
     player.cpp\
     bullet.cpp\
     centnode.cpp\
     gamecontrol.cpp

GAME= game.cpp
EXECUTABLE= game	
OBJECTS= $(GAMESRC:.cpp=.o)

all: $(GAMESRC) $(EXECUTABLE) makefile

$(EXECUTABLE):  $(OBJECTS) $(GAME) 
	$(CC) -g $(GAME) $(OBJECTS)  -o $@  $(LDFLAGS) 

.cpp.o: 
	$(CC) -c $(DEBUG)  $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE
