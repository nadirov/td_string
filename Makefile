TARGET = td_string
TEST_TARGET = td_string_test
USAGE_TARGET = td_string_usage

CFLAGS =
LDFLAGS =

.PHONY : all
all : test

.PHONY : test
test : $(TEST_TARGET)

$(TEST_TARGET) : $(TEST_TARGET).o $(TARGET).o

$(TEST_TARGET).o : $(TEST_TARGET).c

.PHONY : usage
usage : $(USAGE_TARGET)

$(USAGE_TARGET) : $(USAGE_TARGET).o $(TARGET).o

$(USAGE_TARGET).o : $(USAGE_TARGET).c

$(TARGET).o : $(TARGET).c

.PHONY : clean
clean :
	rm -rf $(TEST_TARGET) $(TEST_TARGET).o $(USAGE_TARGET) $(USAGE_TARGET).o $(TARGET).o

