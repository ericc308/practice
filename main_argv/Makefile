#https://www.gnu.org/software/make/manual/html_node/index.html#SEC_Contents

SRCS = $(shell ls *.cpp)


OBJS = $(SRCS:.cpp=.o)
APP = ./argv.exe

# LDFLAGS += -lfftw3 -lsqlite3 -lpthread

all: $(APP) 

$(APP): $(OBJS)
	$(CXX)  -o $(APP) $(OBJS) $(LDFLAGS)

$(OBJS):
	$(CXX) -c  $(SRCS) $(LDFLAGS)

.PHONY: clean format debug

clean:
	# $(MAKE) -C test clean
	rm -rf $(OBJS) $(APP) 

format:
	clang-format -assume-filename=.clang-format -i $(SRCS)

debug:
	$(APP)  [1,10]
