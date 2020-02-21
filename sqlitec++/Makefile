SRCS = $(shell ls cpp/*.cpp)
SRCS += main.cpp

OBJS = $(SRCS:.cpp=.o)
APP = ./sqlite_tb

LDFLAGS += -lfftw3 -lsqlite3 -lpthread

all: $(APP) 

$(APP): $(OBJS)
	$(CXX) -o $(APP) $(OBJS) $(LDFLAGS)

.PHONY: clean format debug test

clean:
	$(MAKE) -C test clean
	rm -rf $(OBJS) $(APP)

format:
	clang-format -assume-filename=.clang-format -i $(SRCS)

debug:
	$(APP) 

test: $(OBJS)
	$(MAKE) -C test