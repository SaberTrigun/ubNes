EXE		= ubNes
DIR_SRC	= src
SRC		= main.cpp
SRC		+= $(DIR_SRC)/cpu.cpp
OBJS	= $(addsuffix .o, $(basename $(notdir $(SRC))))
UNAME_S := $(shell uname -s)
RUN = ./$(EXE)

ifeq ($(UNAME_S), Linux)
	ECHO_MESSAGE = "Linux"
endif

%.o:%.cpp
	$(CXX) -c -o $@ $<

%.o:$(DIR_SRC)/%.cpp
	$(CXX) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^

clean:
	rm -f $(EXE) $(OBJS)
