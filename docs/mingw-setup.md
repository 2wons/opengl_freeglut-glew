## setup mingw64
1. Download GCC 13.2.0 (with MCF threads) win64 from [winlibs](https://winlibs.com/#:~:text=UCRT%20runtime-,GCC%2013.2.0%20(with%20MCF%20threads),-%2B%20LLVM/Clang/LLD)
   ![image](https://github.com/6undae/opengl-freeglut-nocmake/assets/91067593/63665bbb-d54a-4235-9717-eb6cd9ceb083)
2. extract the zip then put `mingw64` folder to your `C:` drive
   ![image](https://github.com/6undae/opengl-freeglut-nocmake/assets/91067593/9b2a6a06-5fc0-4860-a946-3d176a4d5814)
3. copy the path of the bin folder
   ![2uGfn5g15G](https://github.com/6undae/opengl-freeglut-nocmake/assets/91067593/1b3060f2-a16d-45db-b63f-48c3010e5bc8)
4. paste the copied bin path in your `$PATH` evnironement variable
  ![ojS9w4OKBn](https://github.com/6undae/opengl-freeglut-nocmake/assets/91067593/6b259230-ffc5-486a-9d14-24a96080b35a)
5. verify gcc by opening cmd and enter `g++ --version`. it should return a similar output like below
![image](https://github.com/6undae/opengl-freeglut-nocmake/assets/91067593/ef20c35a-4848-4879-8d9f-7f3b53118a71)

if you get something like 
```g++' is not recognized as an internal or external command, operable program or batch file.```
restart your pc, and try step 5 again