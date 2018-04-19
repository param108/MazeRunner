### Getting loopy

If you solved all the assignments in the previous lesson, you should have written a lot of commands. Many of the commands should have been repeated like

```
f()
f()
f()
```

One of the most important things to remember when writing code is *Dont Repeat Yourself*.

There are many ways you can avoid repeating yourself. One of these methods is a **loop**.

A loop repeats the commands in the loop a number of times. This means instead of writing a command many times, you can just write a loop.

### Loop syntax

The way to write loops in python is
```
for i in range(0,N):
    line1
    line2
```

For now we can ignore most of the parts of the `for` loop. The only important part is `N`. Replace this with the number of times to loop the commands.

The lines `line1` and `line2` are inside the loop. The important thing here is the 4 spaces before each line. Lines without 4 spaces would not be considered inside the loop.

So in this example, if N = 4
```
for i in range(0,4):
    line1
    line2
```

Then the commands which would actually run are
```
line1
line2
line1
line2
line1
line2
line1
line2
```

So whatever is in the loop, runs 4 times. Also see that the lines are still run in sequence in the loop. line1, line2 etc.

### Using a loop

So wherever you are using the same command repeatedly one after the other, there you can use a loop. Look at the programs you have written already.

```
f()
f()
f()
```

this can be replaced with

```
for i in range(0,3):
    f()
```

### Loops in Loops

You can even put loops within loops, but you must change `i` to something else.
```
for i in range(0,4):
    for j in range(0,5):
        line1
```

In this example, line1 will run 5 times in the inner loop and the inner loop itself will run 4 times. So that means line1 will run 20 times!

### Assignments

For the assignments lessons/2/maze2a.txt, lessons/2/maze2b.txt, lessons/2/maze2c.txt, lessons/2/maze2d.txt 

Try not to repeat your code, instead use a `for` loop.

Hint: In maze2b and maze2c you can use a loop within a loop.
