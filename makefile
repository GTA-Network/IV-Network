all:
	make -C Libraries/tinyxml
	make -C Libraries/Squirrel
	make -C Server/Core
	make -C Network/Core

clean:
	make -C Libraries/tinyxml clean
	make -C Libraries/Squirrel clean
	make -C Server/Core clean
	make -C Network/Core clean