CXXFLAGS = -O0 -g  -Wall -I ../.. -pthread
LDFLAGS = -lpthread -lxihoo -L.
BASE_SRC = ../../logging/Logging.cc ../../logging/LogStream.cc ../../thread/Thread.cc ../../datetime/Timestamp.cc
xihoo_SRC = $(notdir $(LIB_SRC) $(BASE_SRC))
OBJS = $(patsubst %.cc,%.o,$(xihoo_SRC))

libxihoo.a: $(BASE_SRC) $(LIB_SRC)
	g++ $(CXXFLAGS) -c $^
	ar rcs $@ $(OBJS)

$(BINARIES): libxihoo.a
	g++ $(CXXFLAGS) -o $@ $(filter %.cc,$^) $(LDFLAGS)

clean:
	rm -f $(BINARIES) *.o *.a core

