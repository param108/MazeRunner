import httplib
import json
import commands

def FORWARD():
    ret = commands.FORWARD()
    if ret == -1:
        print "Can't go that way!"
        sys.exit(-1)


def TURN_RIGHT():
    ret = commands.TURN_RIGHT()
    if ret == -1:
        print "Can't go that way!"
        sys.exit(-1)

def TURN_LEFT():
    ret = commands.TURN_LEFT()
    if ret  == -1:
        print "Can't go that way!"
        sys.exit(-1)





FORWARD()
FORWARD()
TURN_LEFT()
