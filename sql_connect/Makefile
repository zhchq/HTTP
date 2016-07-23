WORK_PATH=$(shell pwd)

CC=g++
LIB_PATH=-L/usr/lib/mysql
LIB_NAME=-lmysqlclient

sql_connect.a:sql_connect.cpp
	${CC} -c sql_connect.cpp ${LIB_PATH} ${LIB_NAME} -g
	ar -cvr libsql_connect.a  sql_connect.o

.PHONY:clean 
clean:
	rm -f sql_connect.o libsql_connect.a

