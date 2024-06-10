
# Bomber Man

This project is all about creating a game like the classic Bomber Man that every one knows but mainly done in C++.
## Installation

Install Bomber Man from the following GitHub link :
https://github.com/LaLoutree/FrenchTeam

Now the project is installed, all you need to do is to generate the makefile then the executable file.

```bash
cmake .
make
```
    
## Programming language

- Raylib, used to implement an effect of "3D" while playing, as well as to do the global interface.
- C++, used to compute everything to run well the project. For instance updating the position of the player when changing it (when pressing directionnal buttons), or its power-ups' value (when picking up one on the map when touching it).
## Authors

- [@minipichUwU (Yannick ZHENG)](https://github.com/minipichUwU) who mainly implemented the power-ups of the player.
- [@clhenryng (Henry NGUYEN)](https://github.com/clhenryng) who mainly implemented the engine of the project.
- [@akshayyyr (Akshay RAMAEL)](https://github.com/akshayyyr) who mainly implemented the player.
- [@NachosRumble (Théo CHARBONNIER)](https://github.com/NachosRumble) who mainly implemented the map.
- [@LaLoutree (Bastien DESERT)](https://github.com/LaLoutree) who mainly implemented the bomb management.
- [@??? (Paul ROZENKRAZ)](https://github.com/???) who mainly implemented the User's Interface.


## Appendix

While doing the project, we noticed that the power-ups and the map was pretty much linked together, since the spawning of the power-ups depends of the location of the breakable wall in the map. Hence we decided to implement of the power-ups of the player (done by Yannick ZHENG) and the map (done by Théo CHARBONNIER) in the same file located at "src/Game/Object/Platform/Map/Map.cpp".

