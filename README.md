# POKESLUG
El pryecto POKESLUG esta desarrollado sobre MingW64 utilizanod Msys2 y como editor se esta usando Visual Studio Code

## Dependencias necesarias

A continuacion se listan las dependencias necesarias para correr el juego. En caso de no contar con alguna, es necesario instalarlas.

- ### Programas
    Se requieren los siguientes programas
    
    - Visual Studio Code https://code.visualstudio.com/
    - Msys2 (Windows) 
    https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe 

    No modificar ningua opcion al momento de intalacion o podrian variar las configuraciones. Una vez instalado es necesario agregar los siguientes directorios al path de windows y reiniciar.

        C:\msys64\mingw64\bin

        C:\msys64\usr\bin

    - Github Desktop https://desktop.github.com/
    - Git https://git-scm.com/
- ### Librerias
    Las siguientes librerias deben de instalarse en la terminal de Msys2
    - DevTools https://code.visualstudio.com/docs/cpp/config-mingw
            pacman -S --needed base-devel mingw-w64-x86_64-toolchain
    - SFML https://packages.msys2.org/package/mingw-w64-x86_64-sfml
            pacman -S mingw-w64-x86_64-sfml
    - Box2D simulaciones de fisica https://box2d.org/documentation/ https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64
            pacman -S mingw-w64-x86_64-box2d

## Ejecutar juegos
Para poder ejecutar el juego siga los siguientes pasos
- Instalar todas las dependencias descritas anteriormente
- En la terminal de VS Code, ingresar el comando make run con el nombre del archivo del juego, para este caso ingresar: make runmundo

#### LICENCIA
El siguiente codigo es un proyecto homenaje al videojuego Metal Slug y Pókemon, por lo que por ningun motivo se busca lucrar o generar ingresos con el codigo. El fin del codigo es meramente educacional y de entretenimiento. 
