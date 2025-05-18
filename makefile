COMPILE_CMD = x86_64-w64-mingw32-g++
LINK_CMD = x86_64-w64-mingw32-g++
OBJ_DIR = bin/obj
OUT_DIR = bin/out
DEBUG_CC_FLAGS = -ggdb -c -Wall
RELEASE_CC_FLAGS = -O3 -c -Wall
DEBUG_LNK_FLAGS_POST = -ggdb -static-libgcc -static-libstdc++ -static
RELEASE_LNK_FLAGS_POST = -static-libgcc -static-libstdc++ -static

all: \
	$(OUT_DIR)/debug/launcher.exe \
	$(OUT_DIR)/release/launcher.exe \

clean:
	rm -rf bin

.PHONY: all clean

# ----------------------------------------------------------------------
# launcher

REWINDOW_SRC = \
	src/launcher/commandLine.cpp \
	src/launcher/error.cpp \
	src/launcher/main.cpp \
	src/launcher/parser.cpp \
	src/launcher/shortcuts.cpp \

REWINDOW_DEBUG_OBJ = $(subst src,$(OBJ_DIR)/debug,$(patsubst %.cpp,%.o,$(REWINDOW_SRC)))

$(OUT_DIR)/debug/launcher.exe: $(REWINDOW_DEBUG_OBJ)
	$(info $< --> $@)
	@mkdir -p $(OUT_DIR)/debug
	@$(LINK_CMD) -o $@ $(REWINDOW_DEBUG_OBJ) $(DEBUG_LNK_FLAGS_POST)

$(REWINDOW_DEBUG_OBJ): $(OBJ_DIR)/debug/%.o: src/%.cpp
	$(info $< --> $@)
	@mkdir -p $(OBJ_DIR)/debug/launcher
	@$(COMPILE_CMD) $(DEBUG_CC_FLAGS) $< -o $@

REWINDOW_RELEASE_OBJ = $(subst src,$(OBJ_DIR)/release,$(patsubst %.cpp,%.o,$(REWINDOW_SRC)))

$(OUT_DIR)/release/launcher.exe: $(REWINDOW_RELEASE_OBJ)
	$(info $< --> $@)
	@mkdir -p $(OUT_DIR)/release
	@$(LINK_CMD) -o $@ $(REWINDOW_RELEASE_OBJ) $(RELEASE_LNK_FLAGS_POST)

$(REWINDOW_RELEASE_OBJ): $(OBJ_DIR)/release/%.o: src/%.cpp
	$(info $< --> $@)
	@mkdir -p $(OBJ_DIR)/release/launcher
	@$(COMPILE_CMD) $(RELEASE_CC_FLAGS) $< -o $@
