# ========================================
# ПУТИ
# ========================================
CC = ccache gcc
BUILD_DIR = build
RAYLIB_PATH = C:/clibs/raylib/src
TARGET = game.exe

# ========================================
# АВТОМАТИЧЕСКИЙ ПОИСК .c
# ========================================
SRCS = $(shell find . -name "*.c" -not -path "./$(BUILD_DIR)/*" | sed 's/^\.\///')

# ========================================
# ОБЪЕКТНЫЕ ФАЙЛЫ
# ========================================
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# ========================================
# ПУТИ К .h (ОГРАНИЧЕННЫЕ)
# ========================================
INC_DIRS = $(shell find . -name "*.h" -not -path "./$(BUILD_DIR)/*" -exec dirname {} \; | sort -u)
INCLUDES = $(addprefix -I, $(INC_DIRS))

# ========================================
# ФЛАГИ (ОПТИМИЗИРОВАННЫЕ)
# ========================================
CFLAGS = -g -O0 -pipe -Wall $(INCLUDES) -I$(RAYLIB_PATH) -MMD -MP
LDFLAGS = -L$(RAYLIB_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole

# ========================================
# ПАРАЛЛЕЛЬНАЯ СБОРКА
# ========================================
MAKEFLAGS += -j$(NUMBER_OF_PROCESSORS)

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

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run