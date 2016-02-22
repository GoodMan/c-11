.SURFIXES: .cpp .c .o

CPPFLAGS=-g -Wall -std=c++11
LDFLAGS=

.cpp.o:
	$(CXX) $(CPPFLAGS) $(USERFLAGS) -o $@ -c $<


USERFLAGS=-fconstexpr-depth=2000000
USERFLAGS+=-DCHAP1

OBJ=$(subst .cpp,.o,$(SRC))
TARGET=$(subst .cpp,,$(SRC))

OBJS=Widget.o
OBJS+=$(OBJ)

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

clean:
	$(RM) -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

