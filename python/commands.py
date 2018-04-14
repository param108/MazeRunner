import httplib
import json
import time
import sys

MOVE_DELAY = 1

def ReturnHandler(status):
    if status == -1:
        print "Cant move that way"
        sys.exit(-1)

    if status == 1:
        print "Well done!"
        sys.exit(1)

    if status == 0:
        return 0


def FORWARD():
    print("MOVING FORWARD")
    time.sleep(MOVE_DELAY)
    conn  = httplib.HTTPConnection("localhost",8080)
    conn.request("POST","localhost:8080","{\"action\":\"FORWARD\"}")
    resp = conn.getresponse()
    data = resp.read()
    obj = json.loads(data)
    return ReturnHandler(obj["status"])

def TURN_RIGHT():
    print("TURNING RIGHT")
    time.sleep(MOVE_DELAY)
    conn  = httplib.HTTPConnection("localhost",8080)
    conn.request("POST","localhost:8080","{\"action\":\"TURN_RIGHT\"}")
    resp = conn.getresponse()
    data = resp.read()
    obj = json.loads(data)
    return ReturnHandler(obj["status"])

def TURN_LEFT():
    print("TURNING LEFT")
    time.sleep(MOVE_DELAY)
    conn  = httplib.HTTPConnection("localhost",8080)
    conn.request("POST","localhost:8080","{\"action\":\"TURN_LEFT\"}")
    resp = conn.getresponse()
    data = resp.read()
    obj = json.loads(data)
    return ReturnHandler(obj["status"])
