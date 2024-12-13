# POKESLUG
The POKESLUG project is developed on MingW64 using Msys2 and Visual Studio Code is used as the editor.

## Necessary Dependencies

The following dependencies are necessary to run the game. If you don't have any of them, you need to install them.

- ### Programs
    The following programs are required:
    
    - Visual Studio Code [https://code.visualstudio.com/](https://code.visualstudio.com/)
    - Msys2 (Windows) 
    [https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe](https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe)

    Do not modify any option during installation or the configurations may vary. Once installed, it is necessary to add the following directories to the Windows path and restart.

        C:\msys64\mingw64\bin

        C:\msys64\usr\bin

    - Github Desktop [https://desktop.github.com/](https://desktop.github.com/)
    - Git [https://git-scm.com/](https://git-scm.com/)

- ### Libraries
    The following libraries must be installed in the Msys2 terminal:
    - DevTools [https://code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw)
        ```sh
        pacman -S --needed base-devel mingw-w64-x86_64-toolchain
        ```
    - SFML [https://packages.msys2.org/package/mingw-w64-x86_64-sfml](https://packages.msys2.org/package/mingw-w64-x86_64-sfml)
        ```sh
        pacman -S mingw-w64-x86_64-sfml
        ```
    - Box2D for physics simulations [https://box2d.org/documentation/](https://box2d.org/documentation/) [https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64](https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64)
        ```sh
        pacman -S mingw-w64-x86_64-box2d
        ```

## Run Games
To be able to run the game, follow these steps:
- Install all the dependencies described above.
- In the VS Code terminal, enter the `make run` command with the name of the game file, in this case, enter: `make runmundo-`
![alt text](Pikachu_MS2.png)

#### LICENSE
The following code is a tribute project to the video game Metal Slug and Pokémon, and by no means seeks to profit or generate income from the code. The purpose of the code is purely educational and for entertainment.
