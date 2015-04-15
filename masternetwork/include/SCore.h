#pragma once

namespace Map {
    enum Direction {
        Up,
        Down,
        Left,
        Right,
        UpRight,
        UpLeft,
        DownRight,
        DownLeft,
        None
    };
    
    
}

namespace Entities {
    
    enum EntityType {
        EntityNone = 0,
        EntityWall = 1,
        EntityPlayer = 2,
        EntityEnemy = 3,
        EntityFireDoor = 4,
        EntityExitDoor = 5,
        EntityDataGen = 6,
        EntityDot = 7,
        EntityGun = 8
    };
    
}

