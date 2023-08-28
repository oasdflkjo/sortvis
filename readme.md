now we have a little more structure in this program

we have a somewhat dynamic gui and adding a new sorting algo seems to be quite easy

```bash
gcc -Wall main.c algos.c debug.c platform_sleep.c -I"C:\Raylib\include" -L"C:\Raylib\lib" -o main -lraylib -lopengl32 -lgdi32 -lwinmm
```

- `gcc`: This is the name of the compiler you are using, which is the GNU Compiler Collection.

- `-Wall`: This is a compiler option that enables most of the commonly used warning messages. It's a good practice to use this to catch potential issues in your code.

- `main.c algos.c debug.c platform_sleep.c`: These are the source files you're compiling.

- `-I"C:\Raylib\include"`: The `-I` option is used to specify directories where the compiler should look for header files. In this case, it's looking in the Raylib `include` directory.

- `-L"C:\Raylib\lib"`: The `-L` option is used to specify directories where the linker should look for library files. Here, it's looking in the Raylib `lib` directory.

- `-o main`: The `-o` option is used to specify the name of the output file. In this case, the output executable will be named `main`.

- `-lraylib -lopengl32 -lgdi32 -lwinmm`: These are libraries you're linking against. The `-l` option is used to specify a library.
    - `-lraylib`: Links against the Raylib library.
    - `-lopengl32`: Links against the OpenGL library (for 32-bit systems).
    - `-lgdi32`: Links against the Windows GDI library.
    - `-lwinmm`: Links against the Windows Multimedia library.

The above command compiles the source files, links them with the specified libraries, and produces an executable named `main`.
