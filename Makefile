CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -pthread

# Principal: o servidor
SERVER_TARGET = chat_server
SERVER_SOURCES = main.cpp Server.cpp ClientHandler.cpp tslog.cpp
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)

# Teste: o logger
TEST_TARGET = test_logger
TEST_SOURCES = test_logger.cpp tslog.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

all: $(SERVER_TARGET)

$(SERVER_TARGET): $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(SERVER_TARGET) $(SERVER_OBJECTS) $(LDFLAGS)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_TARGET) $(TEST_TARGET) $(SERVER_OBJECTS) $(TEST_OBJECTS) *.log