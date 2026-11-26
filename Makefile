CXX ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -pedantic -O2
SOURCES := main.cpp Estructuras.cpp GrafoCampus.cpp SistemaAlerta360.cpp Pruebas.cpp MapaVisual.cpp UbicacionesCampus.cpp
HEADERS := Incidencia.h Estructuras.h GrafoCampus.h SistemaAlerta360.h MapaVisual.h UbicacionesCampus.h MapaPlantilla.inc MapaCampusImagen.inc MapaCampusLimpio.inc

ifeq ($(OS),Windows_NT)
TARGET := alerta360.exe
else
TARGET := alerta360
endif

.PHONY: all test clean
all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test: $(TARGET)
	./$(TARGET) --pruebas

clean:
ifeq ($(OS),Windows_NT)
	if exist $(TARGET) del /Q $(TARGET)
else
	rm -f $(TARGET)
endif
