#!/usr/bin/python2.7

from PLManBot import *


res = GameStatus()
while (not res.finished()):
    right = PLMan.see('right')
    left = PLMan.see('left')
    up = PLMan.see('up')
    upLeft = PLMan.see('upleft')
    upRight = PLMan.see('upright')
    down = PLMan.see('down')

    if (down.isExit()):
        res = PLMan.move('down')

    if (upRight.isFireDoorGenerator()):
        res = PLMan.move('none')
        say('Learning: ' + str(upRight.numbers))
    else:
        if (left.isDot()):
            res = PLMan.move('left')
        elif (down.isDot()):
            res = PLMan.move('down')
        elif (up.isDot() and not upLeft.isEnemy() and not upRight.isEnemy()):
            res = PLMan.move('up')
        elif (right.isDot()):
            res = PLMan.move('right')
        else:
            if (down.isEnemy()):
                res = PLMan.move('down')
            elif (right.isEnemy()):
                res = PLMan.move('right')
            elif (left.isEnemy()):
                res = PLMan.move('left')
            elif (up.isEnemy()):
                res = PLMan.move('up')
            else:
                res = PLMan.move('right')

if (res.hasWin()):
    say('Win!!!\n')
else:
    say("Something was wrong and YOU LOSE! :( \n")
