### Lesson 1: Simple Commands

You need to use 3 simple commands to help the hero reach the 'X'
`f()` this tells the hero to step forward
`r()` this tells the hero to turn to his/her right
`l()` this tells the hero to turn to his/her left

These 3 are called `functions` and we need to `call` them. We will learn more about these things later, but for now you just need to understand that to make the hero move you need to type one of these on a new line. For example

```
f()
l()
r()
```

Its important that each is at the beginning of a seperate line.

### Sequences of commands

Computers run sequences of commands. It executes them in order. For example, suppose the hero is facing down (V), then the below `program`,
```
f()
l()
r()
```
would make the hero move like...
1. start
```
v


```

2. `f()`
```

v

```

3. `l()`
```

>

```

4. `r()`
```

v

```

### Bugs

Sometimes the code you write may not reach the hero to the `X`. *DONT WORRY*. Just keep adding to your program until it does reach!
Remember you should reset the board by pressing `z` before you re-run your program. 

Mistakes in programs are usually called **BUGS**.

Another type of mistake you can make is if you hit a wall. When the hero hits a wall your program will stop.

If your program has no *bugs* then you should see "Well done!" on the screen. If you dont see it, then there is a *bug*. Go and squash it!

### Assignments
`./mazeServer -f lessons/1/maze1a.txt -s`

`./mazeServer -f lessons/1/maze1b.txt -s`

`./mazeServer -f lessons/1/maze1c.txt -s`
