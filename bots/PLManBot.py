#!/usr/bin/python2.7

import sys
import json


def say(txt):
    sys.stderr.write('PLBot >> '+txt)
    sys.stderr.flush()


class Entity:
    class Types():
        generator = 6
        tree = 1
        dot = 7
        enemy = 3
        empty = 0
        fireDoor = 4

    typeEntity = "None"
    alive = False

    def __init__(self, JSONObject):
        self.typeEntity = JSONObject["typeEntity"]
        self.alive = JSONObject["alive"]
        if (self.typeEntity == self.Types.generator):
            self.numbers = JSONObject["attributes"][0]["value"].split(';')
            self.numbers = map(float, self.numbers)

    def isEnemy(self):
        return self.typeEntity == 3

    def isTree(self):
        return self.typeEntity == 1

    def isDot(self):
        return self.typeEntity == 7

    def isEmpty(self):
        return self.typeEntity == 0

    def isFireDoorGenerator(self):
        return self.typeEntity == self.Types.generator

    def isFireDoor(self):
        return self.typeEntity == 4

    def isExit(self):
        return self.typeEntity == 5


class GameData:
    value = ""

    def __init__(self, JSONObject):
        self.value = JSONObject["value"]


class GameStatus:
    value = "continue"

    def __init__(self, JSONObject=None):
        if (JSONObject):
            self.value = JSONObject["value"]

    def finished(self):
        return self.value != "continue"

    def hasWin(self):
        return self.value == "win"

    def hasLose(self):
        return self.value == "lose"


class PLManParser:
    @classmethod
    def parseCommand(cls, command):
        try:
            objectLoad = json.loads(command)
        except ValueError:
            return GameStatus()

        if objectLoad["type"] == "visual_entity":
            return Entity(objectLoad)
        elif objectLoad["type"] == "custom_data":
            if objectLoad["key"] == "status":
                return GameStatus(objectLoad)
            else:
                return GameData(objectLoad)
        else:
            return objectLoad


class PLMan:
    @classmethod
    def command(cls, cm):
        sys.stdout.write(cm+'\n')
        sys.stdout.flush()
        pipeBlocked = True
        res = "\n"

        while(pipeBlocked or res == "\n"):
            try:
                res = sys.stdin.readline()
                sys.stdin.flush()
                pipeBlocked = False
            except IOError:
                pass
        return PLManParser.parseCommand(res[:(len(res) - 1)])

    @classmethod
    def see(cls, direction):
        return cls.command('see '+direction)

    @classmethod
    def move(cls, direction):
        return cls.command('move '+direction)

    @classmethod
    def use(cls, direction):
        return cls.command('use '+direction)
