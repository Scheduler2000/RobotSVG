########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++14 #-Weffc++
LDFLAGS = #-lwsock32 -lWs2_32 for networking (using boost::asio for example)

# Makefile settings - Can be customized.
APPNAME = prog
EXT = .cpp
SRCDIR = src
INCDIR = inc
############## Do not change anything from here downwards or be careful ! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT)) \
	  $(wildcard $(SRCDIR)/console/*$(EXT)) \
	  $(wildcard $(SRCDIR)/fichier/*$(EXT)) \
	  $(wildcard $(SRCDIR)/logger/*$(EXT)) \
	  $(wildcard $(SRCDIR)/util/*$(EXT)) \
	  $(wildcard $(SRCDIR)/svg/*$(EXT)) \
 	  $(wildcard $(SRCDIR)/graphisme/*$(EXT)) \
	  $(wildcard $(SRCDIR)/geometrie/*$(EXT)) \
	  $(wildcard $(SRCDIR)/geometrie/builder/*$(EXT)) \
	  $(wildcard $(SRCDIR)/forme/*$(EXT)) \
	  $(wildcard $(SRCDIR)/robot/*$(EXT)) \
	  $(wildcard $(SRCDIR)/robot/builder/*$(EXT)) \
	  $(wildcard $(SRCDIR)/script/*$(EXT)) \
	   $(wildcard $(SRCDIR)/collision/*$(EXT))


OBJ = $(SRC:.$(EXT)=.o)

# Windows OS variables & settings
DEL = del
EXE = .exe

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -I $(INCDIR)/


#################### Cleaning rules for Windows OS && winrar command #####################
# Cleans complete project
mrproper: clean
	$(DEL) $(APPNAME)$(EXE) $(APPNAME).rar

# Cleans only all files with the extension .o
clean: 
	$(DEL) /S *.o

rar : #To Fix all directory
	rar a $(APPNAME).rar
