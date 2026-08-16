# ========================================
# ПУТИ
# ========================================
CC = gcc
BUILD_DIR = build
RAYLIB_PATH = C:/clibs/raylib/src
TARGET = game.exe

# ========================================
# АВТОМАТИЧЕСКИЙ ПОИСК .c ФАЙЛОВ
# ========================================
SRCS = $(shell find . -name "*.c" -not -path "./$(BUILD_DIR)/*")

# ========================================
# ОБЪЕКТНЫЕ ФАЙЛЫ
# ========================================
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

# ========================================
# АВТОМАТИЧЕСКИЙ ПОИСК .h ФАЙЛОВ
# ========================================
INC_DIRS = $(shell find . -name "*.h" -not -path "./$(BUILD_DIR)/*" -exec dirname {} \; | sort -u)
INCLUDES = $(addprefix -I, $(INC_DIRS))

# ========================================
# ФЛАГИ
# ========================================
CFLAGS = -g -Wall $(INCLUDES) -I$(RAYLIB_PATH)
LDFLAGS = -L$(RAYLIB_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole

# ========================================
# ЦЕЛИ
# ========================================
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) -g -O0 -DDEBUG" all

.PHONY: all clean run debug