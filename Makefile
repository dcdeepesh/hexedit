OBJECTS = Base.o Buffer.o Color.o hexedit.o Marker.o Table.o
CXXFLAGS = -Wall -Wextra -Wshadow -pedantic -lcurses
CXX = g++

hexedit: $(OBJECTS)
	$(CXX) -o hexedit $(OBJECTS) $(CXXFLAGS)

Buffer.o: Buffer.cpp Buffer.h
Base.o: Base.cpp Base.h
Color.o: Color.cpp Color.h
Marker.o: Marker.cpp Marker.h Global.h Buffer.h Table.h Color.h Base.h Util.h
Table.o: Table.cpp Table.h Global.h Buffer.h Color.h Base.h Util.h
hexedit.o: hexedit.cpp Marker.h Global.h Buffer.h Table.h Color.h Base.h Util.h

.PHONY: clean
clean:
	rm -rf $(OBJECTS) hexedit

.PHONY: compile
compile: $(OBJECTS)

.PHONY: run
run: hexedit
	./hexedit

.PHONY: binary
binary: hexedit
	rm -rf $(OBJECTS)