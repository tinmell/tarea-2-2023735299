CXX = g++
CXXFLAGS = -std=c++17 -O2

TARGET = programa

SRCS = general.cpp algorithms/brute-force.cpp algorithms/greedy1.cpp algorithms/greedy2.cpp algorithms/dynamic-programming.cpp

INPUT_DIR = data/inputs
MEAS_DIR = data/measurements
OUT_DIR = data/outputs

all: build clean run

build:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	@echo "Limpiando outputs..."
	@rm -rf $(MEAS_DIR)/*.txt
	@rm -f $(OUT_DIR)/MaxSatisfaccion.txt
	@mkdir -p $(MEAS_DIR)
	@mkdir -p $(OUT_DIR)

run:
	@echo "Ejecutando tests..."
	@for file in $$(ls $(INPUT_DIR)/*.txt | sort -V); do \
		echo "Running $$file"; \
		./$(TARGET) $$file < $$file; \
	done