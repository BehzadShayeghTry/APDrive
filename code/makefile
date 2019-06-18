CC=g++
STD=-std=c++11 # -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: maindir/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c maindir/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: maindir/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c maindir/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/Core.o: core/Core.cpp core/Core.hpp core/User.hpp core/Document.hpp core/Folder.hpp core/Group.hpp
	$(CC) $(CF) -c core/Core.cpp -o $(BUILD_DIR)/Core.o

$(BUILD_DIR)/Document.o: core/Document.cpp core/User.hpp core/Folder.hpp core/Group.hpp
	$(CC) $(CF) -c core/Document.cpp -o $(BUILD_DIR)/Document.o

$(BUILD_DIR)/File.o: core/File.cpp core/Document.hpp
	$(CC) $(CF) -c core/File.cpp -o $(BUILD_DIR)/File.o

$(BUILD_DIR)/Folder.o: core/Folder.cpp core/Document.hpp
	$(CC) $(CF) -c core/Folder.cpp -o $(BUILD_DIR)/Folder.o

$(BUILD_DIR)/User.o: core/User.cpp core/Folder.hpp core/Group.hpp
	$(CC) $(CF) -c core/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Group.o: core/Group.cpp core/User.hpp
	$(CC) $(CF) -c core/Group.cpp -o $(BUILD_DIR)/Group.o

$(BUILD_DIR)/main.o: maindir/main.cpp core/Core.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp maindir/handlers.hpp maindir/my_server.hpp
	$(CC) $(CF) -c maindir/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/Core.o $(BUILD_DIR)/Document.o $(BUILD_DIR)/File.o $(BUILD_DIR)/Folder.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/User.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/Core.o $(BUILD_DIR)/Document.o $(BUILD_DIR)/File.o $(BUILD_DIR)/Folder.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/User.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
