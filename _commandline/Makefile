cm = g++ -std=c++11

a.out: User.o Group.o Document.o File.o Folder.o Core.o Interface.o CommandHandle.o MyExeptions.o main.cpp
	$(cm) main.cpp User.o Group.o Document.o File.o Folder.o Core.o Interface.o CommandHandle.o MyExeptions.o -o drive.exe
User.o: User.hpp User.cpp
	$(cm) -c User.cpp
Group.o: Group.hpp Group.cpp
	$(cm) -c Group.cpp
Document.o: Document.hpp Document.cpp
	$(cm) -c Document.cpp
File.o: File.hpp File.cpp
	$(cm) -c File.cpp
Folder.o: Folder.hpp Folder.cpp
	$(cm) -c Folder.cpp
Core.o: Core.hpp Core.cpp
	$(cm) -c Core.cpp
Interface.o: Interface.hpp Interface.cpp
	$(cm) -c Interface.cpp
CommandHandle.o: CommandHandle.hpp CommandHandle.cpp
	$(cm) -c CommandHandle.cpp
MyExeptions.o: MyExeptions.hpp MyExeptions.cpp
	$(cm) -c MyExeptions.cpp

clean:
	find . -type f | xargs touch
	rm -rf $(OBJS)
	rm -rf *.o drive.exe