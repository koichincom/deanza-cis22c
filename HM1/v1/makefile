# コンパイラの設定
CXX = g++
CXXFLAGS = -Wall -g

# ソースファイルと実行ファイルの設定
SRCS = HM1B-Problem.cpp
TARGET = HM1B-Problem

# デフォルトのターゲット
all: $(TARGET)

# 実行ファイルを生成
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# クリーンアップ
clean:
	rm -f $(TARGET)
