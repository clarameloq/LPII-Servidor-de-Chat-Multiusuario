CXX = g++

CXXFLAGS = -std=c++17 -Wall

LDFLAGS = -pthread

TARGET = test_logger

SOURCES = tslog.cpp test_logger.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -f $(TARGET) $(OBJECTS) chat.log