Для компиляции на WSL(Windows Subsystem for Linux) использовался установленный с 
помощью следующей команды toolchain:
sudo apt install gcc-aarch64-linux-gnu

Сборка производилась следующим образом:
aarch64-linux-gnu-gcc [source file .s/.c] -o [output file .o/ ] -static
Пример:
aarch64-linux-gnu-gcc ./aarch64.s -0 1 -static

Для запуска транслированного двоичного кода использовался эмулятор qemu:
Установка:
sudo apt install qemu-user
Использование:
qemu-[system] [assembler file]
В моём случае:
qemu-aarch64 ./1