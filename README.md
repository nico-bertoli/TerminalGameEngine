An engine for creating 2D terminal-based games, built without any graphics libraries.

- Framerate-independent simulation (delta-time based)
- Efficient rendering (only the changing parts of the terminal are reprinted)
- Particle system
- Collision system (OnCollisionEnter/Exit)
- Sorting layer system
- Easy to add new levels / objects
- Backgrounds support

Note: for now this works on Windows only (project depends on Windows terminal API)

[Youtube Trailer](https://www.youtube.com/watch?v=TqpGVI95oNU&ab_channel=Nicol%C3%B2Bertoli)

<img src="screenshots/screen1.png" style="height:500px; max-width:100%;">
<img src="screenshots/screen2.png" style="height:250px; max-width:100%;">
<img src="screenshots/screen3.png" style="height:250px; max-width:100%;">


#
<b>How to build (cmake):</b>

Enter EngineDemo/build and run this commands:
- cmake -S ../ -O ./
- cmake --build .

#
This project uses SFML (Simple and Fast Multimedia Library). https://www.sfml-dev.org

SFML is developed by Laurent Gomila and contributors.
Copyright (C) 2007-2023 Laurent Gomila - laurent@sfml-dev.org
SFML is licensed under the zlib/libpng license.
