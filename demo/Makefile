# demo/Makefile

# 定义编译器
CC = gcc
CXX = g++

# 定义编译选项
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g -std=c++11

# 上层目录路径
TOP_DIR = ..

# 包含上层目录的头文件路径
INCLUDES = -I$(TOP_DIR)/include -I$(TOP_DIR)

# 链接选项
LDFLAGS = -L$(TOP_DIR)/lib

# 目标文件
TARGET = demo_app

# 查找上层目录中的源文件
TOP_CPP_SRCS = $(wildcard $(TOP_DIR)/*.cpp)
TOP_CC_SRCS = $(wildcard $(TOP_DIR)/*.cc)
TOP_C_SRCS = $(wildcard $(TOP_DIR)/*.c)

# demo目录中的源文件
DEMO_CPP_SRCS = $(wildcard *.cpp)
DEMO_CC_SRCS = $(wildcard *.cc)
DEMO_C_SRCS = $(wildcard *.c)

# 所有源文件
ALL_CPP_SRCS = $(TOP_CPP_SRCS) $(DEMO_CPP_SRCS)
ALL_CC_SRCS = $(TOP_CC_SRCS) $(DEMO_CC_SRCS)
ALL_C_SRCS = $(TOP_C_SRCS) $(DEMO_C_SRCS)

# 生成对应的目标文件
TOP_CPP_OBJS = $(TOP_CPP_SRCS:.cpp=.o)
TOP_CC_OBJS = $(TOP_CC_SRCS:.cc=.o)
TOP_C_OBJS = $(TOP_C_SRCS:.c=.o)

DEMO_CPP_OBJS = $(DEMO_CPP_SRCS:.cpp=.o)
DEMO_CC_OBJS = $(DEMO_CC_SRCS:.cc=.o)
DEMO_C_OBJS = $(DEMO_C_SRCS:.c=.o)

ALL_OBJS = $(TOP_CPP_OBJS) $(TOP_CC_OBJS) $(TOP_C_OBJS) \
           $(DEMO_CPP_OBJS) $(DEMO_CC_OBJS) $(DEMO_C_OBJS)

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 编译上层目录的 C++ 文件 (.cpp)
$(TOP_DIR)/%.o: $(TOP_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 编译上层目录的 C++ 文件 (.cc)
$(TOP_DIR)/%.o: $(TOP_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 编译上层目录的 C 文件
$(TOP_DIR)/%.o: $(TOP_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 编译 demo 目录的 C++ 文件 (.cpp)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 编译 demo 目录的 C++ 文件 (.cc)
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 编译 demo 目录的 C 文件
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 清理编译产物
clean:
	rm -f $(ALL_OBJS) $(TARGET)
	rm -f $(TOP_DIR)/*.o

# 伪目标
.PHONY: all clean

# 显示变量信息（用于调试）
debug:
	@echo "TOP_CPP_SRCS: $(TOP_CPP_SRCS)"
	@echo "TOP_CC_SRCS: $(TOP_CC_SRCS)"
	@echo "TOP_C_SRCS: $(TOP_C_SRCS)"
	@echo "DEMO_CPP_SRCS: $(DEMO_CPP_SRCS)"
	@echo "ALL_OBJS: $(ALL_OBJS)"