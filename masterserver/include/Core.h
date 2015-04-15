/* 
 * File:   Core.h
 * Author: Sergio Gallardo Sales (maktub82dev@outlook.com) @maktub82
 *
 * Created on November 7, 2013, 11:11 PM
 */

#ifndef MASTERNUMS_H
#define	MASTERNUMS_H

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
        EntityNone,
        EntityWall,
        EntityPlayer,
        EntityEnemy,
        EntityFireDoor,
        EntityExitDoor,
        EntityDataGen,
        EntityDot,
        EntityGun
    };
    
}
#endif	/* MASTERNUMS_H */

