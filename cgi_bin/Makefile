FIND_PATH=-L/home/centos/Desktop/httpd/sql_connect -lsql_connect -L/usr/lib/mysql -lmysqlclient -I/home/centos/Desktop/httpd/sql_connect

.PHONY:all
all:debug_cgi math_cgi register_cgi show_student_cgi

debug_cgi:debug_cgi.c
	gcc -o $@ $^
math_cgi:math_cgi.cpp
	g++ -o $@ $^
show_student_cgi:show_student_cgi.cpp
	g++ -o $@ $^ $(FIND_PATH) -g

register_cgi:register_cgi.cpp
	g++ -o $@ $^ $(FIND_PATH)

.PHONY:output
output:
	cp debug_cgi ../output/htdocs/cgi_bin
	cp math_cgi ../output/htdocs/cgi_bin
	cp show_student_cgi ../output/htdocs/cgi_bin
	cp register_cgi ../output/htdocs/cgi_bin

.PHONY:clean
clean:
	rm -rf debug_cgi math_cgi show_student_cgi register_cgi




