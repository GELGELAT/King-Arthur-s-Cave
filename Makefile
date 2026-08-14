CC = gcc
RAYLIB_PATH = C:/clibs/raylib/src

CFLAGS = -g -Wall -Wextra -Wpedantic -std=c99 -I$(RAYLIB_PATH) -MMD -MP
LDFLAGS = -L$(RAYLIB_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm

# ========== ВЫБОР РЕЖИМА ==========
ifeq ($(BUILD),deb)
    CFLAGS += -g -O0 -DDEBUG
    TARGET = game_d.exe
else
    CFLAGS += -O2 -DNDEBUG
    TARGET = game.exe
endif

# ========== ИСХОДНИКИ ==========
SRCS = main.c allocator.c renderer.c structurs.c updater.c initialization.c generators.c misc.c texturs.c enemy_logic.c fog.c player_logic.c items_logic.c actions_work.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

# ========== ЦЕЛИ ==========
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Подключаем автоматические зависимости
-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) *.exe

run: $(TARGET)
	./$(TARGET)

debug:
	$(MAKE) BUILD=t

.PHONY: all clean run debug