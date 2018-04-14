import httplib
import json
import commands

def f():
    commands.FORWARD()


def r():
    commands.TURN_RIGHT()
    
def l():
    commands.TURN_LEFT()


for i in range(0, 15):
    f()

l()

for i in range(0,15):
    f()

l()

for i  in range (0,17):
    f()

r()

for i in range(0,19):
    f()


r()

for i in range(0,23):
    f()

l() 

for i in range(0,21):
    f()

l()

for i in range(0,21):
    f()

r()

for i in range(0,4):
    f()
