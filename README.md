### Maze Runner

A simple terminal application to teach children to program in python. Though the first cut is completely focussed on python, the structure can be used for any programming language which can run a http client.

The server shows a simple maze view where '#' are walls, 'X' is the destination and '>' is the hero. It accepts 3 json commands over http.

1. `FORWARD`
```
{
"action": "FORWARD"
}
```
2. `TURN_LEFT`
```
{
"action":"TURN_LEFT"
}
```
3. `TURN_RIGHT`
```
{
"action":"TURN_RIGHT"
}
```
4. `WHATS_NEXT`
```
{
"action":"WHATS_NEXT"
}
```
Accordingly the server moves the hero on the screen if possible and returns a response of the form
```
{
"action":"TURN_RIGHT",   // whatever was sent by the client
"status": [0|1|-1],
"next": ["WALL"|"X"|"BLANK"|"HERO"] // only for WHATS_NEXT
}
```

**Status Values**
* 0 - Success
* 1 - You have reached the destination
* -1 - You have tried an invalid move, no change has been made to the game board.

### Setup
You will need `libncurses` and `libmicrohttpd` to build the application apart from the sundry c++ compiler. Please note this executable uses c++11 standards.

Run this command to build the mazeServer executable

` make mazeServer`

### Modus Operandi

![mazerunnertotalsetup](https://user-images.githubusercontent.com/331871/38767497-14063036-4000-11e8-911f-2a2e4a274aa2.png)

1. Open the mazeServer in a large terminal (greater than 75 columns and 35 rows). 
2. Generate the maze using `DRAW` mode below Or just use an existing lesson.
3. Run the mazeServer in server mode specifying the maze file you want to try.
4. Copy the `template.py` to file of your choice in the same directory and open it in an editor. The editor should be simple enough for your child to save and edit. I used `gnome-text-editor` because it  has a nice big `save` button.
5. Open one more terminal (can have just 3 lines) and navigate to the python directory in the repository.
6. Once your child has made her first edits  and saved just run the following command.

`python <filename>`

7. You should see the hero move.
8. After discussing what needs to change or what more needs to be done, reset the mazeServer by pressing `z`
9. Ask your child to make more changes and go to step (6).


### Components

1. `MazeServer` is the C++ server and ncurses view. It can be used in 2 modes
  1. Draw
  2. Server
2. `Python code` is the python code which you can use as a template to teach.

#### MazeServer - Draw mode

```
     mazeServer -d [-f<filename>]
```

`-f` allows you specify an existing map for editting. *Please note the tool only overwrites!*. If no `-f` is specified, the default file is `mazemap.txt` in the current directory`. Default size of the maze is 75 columns by 30 lines, so make sure your terminal is appropriately sized.

Draw mode allows you to draw the maze (walls) and place the hero and destination. There are some rough edges still, so make sure you add only one hero and one destination. (unless you update the code to handle more of them). 

Commands available are single key commands (all commands are lowercase letters)
1. `Arrow Keys` to move the cursor
1. `x` place the destination at the point where the cursor currently is
1. `u` place the hero at the cursor facing up '^'
1. `d` place the hero at the cursor facing  down 'v'
1. `l` place the hero at the cursor facing left '<'
1. `r` place the hero at the cursor facing right '>'
1. `<SPC>` place a blank at the cursor ' ' use this to remove a misplaced hero or wall.
1. `w` place a wall segment at cursor '#'
1. `s` save the maze to the file mentioned in `-f` argument or `mazemap.txt`
1. `z` refresh the screen
1. `q` quit drawing session

In this mode you can create the gameboard

#### MazeServer - Server mode
```
    mazeServer -s [-f<filename>] [-p port]
```

`-p` sets the port on which the server will listen, if this is not mentioned the port is 8080. The python template files assume presently that the server is on 8080. So use this carefully.

`-f` tells the mazeServer to pickup the maze from the file mentioned. If this is not mentioned then a blank maze is setup (probably not what you want). There are sample mazes in the `lessons` directory.

In this mode, you will see the maze you loaded, but now using the cursor moves the *Hero* '>'. The server will also start listening on 8080 port for commands (as mentioned in the first part of this readme)

Allowed commands
1. `up arrow key` - move hero forward if possible
1. `left arrow key` - turn the hero to *her* left
1. `right arrow key` - turn the hero to *his* right
1. `q` - quit
1. `z` - reset the maze to initial condition

#### Python templates
`commands.py`, `template.py` These provide the python interface to send commands to the server. You should copy template.py to a new file when your child takes up a maze challenge.

4 commands are provided
1. f() - move one step in the direction the hero is facing. 
1. l() - turn hero to _his_ left
1. r() - turn hero to _her_ right
1. whats_next() - returns the item in the block in front of the hero. Returns a string "HERO","WALL","BLANK","X". "X"" is the destination

When you run the code written by your child it will do each step after a delay of one second and print out what it is doing. This allows your child to turn to the server window and see their commands executing. You may need to tell them what to look for.

### Whats next ?

The idea is to generate more mazes and lesson plans. The available lessons so far are
1. lesson 1
Simple use of commands and importance of sequence in commands.

2. lesson 2: loops
I told my daughter about simple range based for loops and she decided how many steps are required. The file `first.py` is her solution to the first problem (maze2a.txt).
