# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Pega todos os arquivos .cpp da pasta atual
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Nome do executável
TARGET = ProjetoSimas

# Regra principal
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compilação de cada .cpp para .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f *.o $(TARGET)
