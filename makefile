all:
	make -C Libraries/lua
	make -C Server

clean:
	make -C Server clean
	make -C Libraries/lua clean