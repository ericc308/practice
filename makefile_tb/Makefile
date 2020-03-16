#https://www.gnu.org/software/make/manual/html_node/index.html#SEC_Contents

SRCS = $(shell ls *.cpp)
# TEST_PATH = $(shell find /usr/src/googletest/googletest) 
# ifdef TEST_PATH
# $(info find /usr/src/googletest/googletest)
# TEST_PATH = /usr/src/googletest/googletest
# else
# $(info cannot find /usr/src/googletest/googletest)
# TEST_PATH = /home/ycj/googletest/googletest
# $(info change gtest path  to $(TEST_PATH))
# endif

TEST_PATH = /home/ycj/googletest/googletest
ifeq (,$(shell find /home/ycj/googletest/googletest))
TEST_PATH = /usr/src/googletest/googletest
$(info change gtest path  to $(TEST_PATH))
endif


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
