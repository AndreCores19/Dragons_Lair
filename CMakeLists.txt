cmake_minimum_required(VERSION 4.1)
project(Dragons_Lair)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dragons_Lair main.cpp
        World.cpp
        World.h
        Region.cpp
        Region.h
        List.h
        BaseError.cpp
        BaseError.h
        OutOfRangeError.h
        FileNotFound.h
        InvalidFormat.h
        Reader.cpp
        Reader.h
        Object.h
        Hunter.cpp
        Object.cpp
        Dragon.h
        Dragon.cpp
        Entity.cpp
        Character.cpp
        FireDragon.cpp
        FireDragon.h
        PoisonDragon.cpp
        PoisonDragon.h
        Bitacora.cpp
        Bitacora.h
        HydraDragon.cpp
        HydraDragon.h
        Weapon.cpp
        Weapon.h
        Potion.cpp
        Potion.h
        Armor.cpp
        Armor.h
        Villager.cpp
        Villager.h
)
