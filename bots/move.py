#!/usr/bin/python2.7

from PLManBot import *


res = GameStatus()
while (not res.finished()):
    say("iter\n")
    right = PLMan.see('right')
    left = PLMan.see('left')
    up = PLMan.see('up')
    upLeft = PLMan.see('upleft')
    upRight = PLMan.see('upright')
    downRight = PLMan.see('downright')
    downLeft = PLMan.see('downleft')
    down = PLMan.see('down')

    if down.isEnemy() or downRight.isEnemy() or downLeft.isEnemy():
        res = PLMan.move('none')
    else:
        res = PLMan.move('down')

if (res.hasWin()):
    say('Win!!!\n')
else:
    say("Something was bad and YOU LOSE! :( \n")
