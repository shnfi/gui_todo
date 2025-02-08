# GUI todo application
a GUI todo application written in c++ and qt. [Wikipedia](https://en.wikipedia.org/wiki/Qt_(software))

## How to run ?
1. clone the project into your computer .
2. navigate to the project's directory .
3. make the project .
```bash
qmake -project
```
4. edit the `gui_todo.pro` file .
```bash
vi gui_todo.pro
```
5. add this line under the `# Input` section .
```
QT += core gui widgets
```
6. then simply run the `build.sh` script to compile the project .
```bash
./build.sh
```
7. run the application .
```bash
./todo
```
