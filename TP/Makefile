# Definição das pastas do projeto
SRCDIR := src
OBJDIR := obj
BINDIR := bin
INCDIR := include

# Compilador e flags
CXX := g++
CXXFLAGS := -I$(INCDIR)

# Lista de arquivos fonte
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Lista de arquivos objetos a serem gerados
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Nome do executável
TARGET := $(BINDIR)/resolvedor

# Regra default (gera o executável)
run: $(TARGET)
	$(TARGET) < entrada.txt > saida.txt

# Regra de compilação dos arquivos objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regra de linkagem do executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Limpa os arquivos objetos e o executável
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

# Remove apenas os arquivos objetos
cleanobj:
	rm -f $(OBJDIR)/*.o
