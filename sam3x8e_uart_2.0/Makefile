################################################################################
#                                 GOD MAKEFILE                                 #
################################################################################

# Binairy name
TARGET 		= sim

# Directories
BINDIR          = bin
OBJDIR          = obj
INCDIR          = inc
SRCDIR          = src

# Compiling options
CC 		= g++ -std=c++11
CFLAGS 		= -I /net/s/leodumez/systemC_project/systemc-2.3.1/include

LD_LIBRARY_PATH = /net/s/leodumez/systemC_project/systemc-2.3.1/lib-linux64

# Link options
LINKER 		= $(CC) -o
LFLAGS 		=  -L/net/s/leodumez/systemC_project/systemc-2.3.1/lib-linux64 -lsystemc

# Variables
BIN             = $(BINDIR)/$(TARGET)
SOURCES        := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES       := $(wildcard $(INCDIR)/*.h)
OBJECTS        := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Rm option
RM 		= rm -f

############################### COMPILING RULES  ###############################

all : $(BIN)
$(BIN) : $(OBJECTS)
	$(LINKER) $@ $(OBJECTS) $(LFLAGS)

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

export LD_LIBRARY_PATH=/net/s/leodumez/systemC_project/systemc-2.3.1/lib-linux64
################################### CLEANER ####################################
.PHONY: clean
clean :
	@$(RM) $(OBJECTS)
	@$(RM) $(SRCDIR)/*~
	@$(RM) $(INCDIR)/*~
	@$(RM) *~

fclean : clean
	@$(RM) $(BINDIR)/$(TARGET)

################################################################################
