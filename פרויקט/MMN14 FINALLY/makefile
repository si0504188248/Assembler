# Define the compiler
CC = gcc

# Define compilation flags
CFLAGS = -Wall -IHeaders

# Define the source and header directories
SRC_DIR = Sources
HDR_DIR = Headers
OBJ_DIR = Objects

# Create the object directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

# Define the list of source files
SRCS = $(SRC_DIR)/MyMain.c \
       $(SRC_DIR)/MyCode.c \
       $(SRC_DIR)/MyData.c \
       $(SRC_DIR)/MyMacro.c \
       $(SRC_DIR)/MyPrint.c \
       $(SRC_DIR)/MyFunctions.c \
       $(SRC_DIR)/MyListFunctions.c \
       $(SRC_DIR)/FirstPass.c \
       $(SRC_DIR)/SecondPass.c

# Define the list of object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Define the name of the final executable
TARGET = assembler

# Default target to build the program
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

# Rule to compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the build
clean:
	rm -f $(TARGET) $(OBJ_DIR)/*.o

# Rule to remove all generated files (optional)
distclean: clean
	rm -f *~

.PHONY: all clean distclean
