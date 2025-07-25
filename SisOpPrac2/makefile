#############
#
# Makefile generico
# Autor: PaikLC
#
#############

#DEBUG	=	1
# Definimos los programas que compilaran por nosotros
CC				= gcc.exe

# Las cosas a compilara
TARGET			= main
OBJS			= $(TARGET).o ./wfile/windowsFiles.o ./inputs/customInputs.o createFiles.o permissionsFiles.o listFiles.o copyFiles.o

ifdef DEBUG
NAME			= main_DBG.exe
else
NAME			= main.exe
endif


# Las opciones de compilacion
CFLAGS			= -Wall -Wextra -Wpedantic
LDFLAGS			= 
DEBUG_FLAGS		= -g -O1
RELEASE_FLAGS	= -s -O2

ifdef DEBUG
CFLAGS			+= $(DEBUG_FLAGS)
else
CFLAGS			+= $(RELEASE_FLAGS)
endif


all: $(NAME)

# Compilar el programa listo para ser compilado para windows...
$(NAME).exe: $(OBJS)
	$(CC) -o $(NAME).exe $(OBJS) $(LDFLAGS)


# Compilar el programa para linux...
$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

# Compilar .c ¿Para que es el $*.o? ¿Renombrar?
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $*.o

#Trabajar con el .rc
%.o: %.rc
	windres -i $< -o $*.o

# Limpiar las cosas
.PHONY clean:
	rm -r *.o
	rm -r *.exe