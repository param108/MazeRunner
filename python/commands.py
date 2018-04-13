import httplib
import json
import time


MOVE_DELAY = 3

def FORWARD():
    print("MOVING FORWARD")
    time.sleep(MOVE_DELAY)
    conn  = httplib.HTTPConnection("localhost",8080)
    conn.request("POST","localhost:8080","{\"action\":\"FORWARD\"}")
    resp = conn.getresponse()
    data = resp.read()
    obj = json.loads(data)
    return obj["status"]

def TURN_RIGHT():
    print("TURNING RIGHT")
    time.sleep(MOVE_DELAY)
    conn  = httplib.HTTPConnection("localhost",8080)
    conn.request("POST","localhost:8080","{\"action\":\"TURN_RIGHT\"}")
    resp = conn.getresponse()
    data = resp.read()
    obj = json.loads(data)
    return obj["status"]

def TURN_LEFT():
    print("TURNING LEFT")
    time.sleep(MOVE_DELAY)
    conn  = httplib.HTTPConnection("localhost",8080)
    conn.request("POST","localhost:8080","{\"action\":\"TURN_LEFT\"}")
    resp = conn.getresponse()
    data = resp.read()
    obj = json.loads(data)
    return obj["status"]
