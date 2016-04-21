CC              = gcc
CFLAGS          = -I src -Wall -lelf
AR              = ar
ARFLAGES        = -crv
NAME            = cut
TARGET          = lib$(NAME).a
TEST_TARGET     = test.out
HEADERS         = $(wildcard ./src/*.h)
CPATH           = $(wildcard ./src/*.c)
TEST_CPATH      = $(wildcard ./test/*.c)
CFILES          = $(notdir $(CPATH))
TEST_CFILES     = $(notdir $(TEST_CPATH))
OBJS            = $(patsubst %.c, %.o, $(CFILES))
TEST_OBJS       = $(patsubst %.c, %.o, $(TEST_CFILES))
INCLUDE_DIR     = /usr/local/include/$(NAME)
LIB_DIR         = /usr/local/lib
VPATH           = src:test

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGES) $@ $?
    
.PHONY: test
test: $(TEST_OBJS) $(TARGET)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $^
	./$(TEST_TARGET)
    
.PHONY: install
install: $(TARGET) $(HEADERS)
	-mkdir -p $(INCLUDE_DIR)
	cp -r $(HEADERS) $(INCLUDE_DIR)
	cp $(TARGET) $(LIB_DIR)
    
$(OBJS):      $(CFILES)
$(TEST_OBJS): $(TEST_CFILES)

.PHONY: clean
clean:
	-rm -rf $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)