CC := gcc
CFLAGS := -fcommon -w -D _GNU_SOURCE
INC := -Iheader
TARGET := LinuxOS

# 소스 파일 경로
SRC_DIRS := source system

# 소스 파일과 객체 파일
SRCS := $(wildcard source/*.c system/*.c)
OBJS := $(SRCS:source/%.c=%.o)
OBJS := $(OBJS:system/%.c=%.o)

# 규칙 정의
$(TARGET): $(OBJS)
        $(CC) $(OBJS) -o $(TARGET)

%.o: source/%.c
        $(CC) $(CFLAGS) $(INC) -c $< -o $@

%.o: system/%.c
        $(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
        rm -f $(OBJS) $(TARGET)

.PHONY: clean
