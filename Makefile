OBJDIR = obj
OBJS = $(OBJDIR)/dbus_main.o $(OBJDIR)/pfmain.o
CC = g++
CFLAGS = -Wall -o -g

BUILD_DIR = /home/hh/hhwork/autolink/demoh/

ifneq ($(BUILD_DIR),)    #如果BUILD_DIR变量不能于空
saved-output := $(BUILD_DIR) #定义saved-output变量等于BUILD_DIR变量

# Attempt to create a output directory.
$(shell [ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR}) #[]代表test，-d是否是文件夹。如果没有BUILD_DIR文件夹，则创建。-p为强制。

# Verify if it was successful.
BUILD_DIR := $(shell cd $(BUILD_DIR) && /bin/pwd) ＃进入目录并打印出路径
$(if $(BUILD_DIR),,$(error output directory "$(saved-output)" does not exist)) #如果不存在BUILD_DIR则输出错误信息
endif # ifneq ($(BUILD_DIR),)
#target:prerequisites
#command

TARGET1 = DNS.out
TARGET2 = xmit.out
TARGET3 = recv.out

SRC_FILE1=simple_DNS.cpp
SRC_FILE2=socket_cln.cpp
SRC_FILE3=socket_ser.cpp



DBUS_CFLAGS =
DBUS_GLIB_CFLAGS =
DBUS_LIBS =
DBUS_GLIB_LIBS =
MIDW_CFLAGS =

INIP_CFLAGS =

INC_DIRS = \
        $(DBUS_CFLAGS)                          \
        $(DBUS_GLIB_CFLAGS)                     \
        $(MIDW_CFLAGS)                          \
        $(INIP_CFLAGS)

SYMBOLS =

LIBS = \
        $(DBUS_LIBS)                            \
        $(DBUS_GLIB_LIBS)                       \
        -lpthread                   


all: clean default


default:
	$(CC) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILE1) -o $(TARGET1) $(LIBS)
	$(CC) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILE2) -o $(TARGET2) $(LIBS)
	$(CC) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILE3) -o $(TARGET3) $(LIBS)



clean:
	rm -rf *.o $(TARGET1) $(TARGET2) $(TARGET3)
