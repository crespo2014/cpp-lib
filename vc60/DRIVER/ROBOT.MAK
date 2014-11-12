# ROBOT.mak - makefile for VxD ROBOT

DEVICENAME = ROBOT
DYNAMIC = 1
FRAMEWORK = C
DEBUG = 1
OBJECTS = robot.OBJ CMOSIO.OBJ

!include $(VTOOLSD)\include\vtoolsd.mak
!include $(VTOOLSD)\include\vxdtarg.mak

robot.OBJ:	robot.c robot.h