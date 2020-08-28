—борка проекта сервера "Server" осуществл€етс€ с помощью cmake/MinGW:

mkdir Build_Server
cd Build_Server
cmake ../Server -G "MinGW Makefiles"
mingw32-make


--------------------------------------------------------------------

—борка проекта клиента "Client" осуществл€етс€ с помощью make/gcc:

make