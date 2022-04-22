PROJ_NAME=obstacle_detection

TARGET=atmega328(Arduino UNO)

OPTIMISE = -Os

BUILD_DIR = build

PROJ_PATH = $(BUILD_DIR)/$(PROJ_NAME)

# All Source code files
source = project_main.c\
source/go_forward.c\
source/go_backward.c\
source/go_left.c\
source/go_right.c\
source/stop_all.c

# All header file paths
INCLUDE = -I include

# Find out the OS and configure the variables accordingly
ifdef OS	# All configurations for Windwos OS
# Delete command 
   RM = rm -rf
# Move command
   MOV = Move-Item
# Correct the path based on OS
   FixPath = $(subst /,\,$1)
# Name of the compiler used
   CC = avr-gcc.exe
# Name of the elf to hex file converter used
   AVR_OBJ_CPY = avr-objcopy.exe
else #All configurations for Linux OS
   ifeq ($(shell uname), Linux)
# Delete command
    RM = rm -rf
# Move command
   MOV = mv	
# Correct the path based on OS
    FixPath = $1				
# Name of the compiler used
	CC = avr-gcc
# Name of the elf to hex file converter used
	AVR_OBJ_CPY = avr-objcopy 
   endif
endif

# Command to make to consider these names as targets and not as file names in folder
.PHONY:all analysis clean doc

all: $(PROJ_PATH).elf
	# Generate hex file from elf file
	$(AVR_OBJ_CPY) -j .text -j .data -O ihex $(call FixPath,$(PROJ_PATH).elf) $(call FixPath,$(PROJ_PATH).hex)
  $avr -gcc -wall -g -Os -mmcu=atmega328 -0 main.bin main.c
$(PROJ_PATH).elf: $(SRC) $(BUILD_DIR)
	# Generate elf file from object file
	$(CC) -g -Wall $(OPTIMISE) -mmcu=$(TARGET) -o $(call FixPath,$(PROJ_PATH).elf) $(INC) $(SRC)

$(BUILD_DIR):
	# Create new build folder if not present
	mkdir build

analysis: $(SRC)
# Analyse the code using Cppcheck command line utility
	cppcheck --enable=all $^

doc:
# Build the code code documentation using Doxygen command line utility
	make -C documentation

clean:
# Remove all the build files and generated document files
	$(RM) $(call FixPath,$(BUILD_DIR))
	make -C documentation clean
