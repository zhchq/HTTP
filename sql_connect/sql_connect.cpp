#include "sql_connect.h"
sql_connecter::sql_connecter(const std::string &_host,\
		const std::string &_user,\
		const std::string &_passwd,\
		const std::string &_db)
{
	this->mysql_base = mysql_init(NULL);
	this->res = NULL;
	this->host = _host;
	this->user = _user;
	this->passwd = _passwd;
	this->db   = _db;
}

bool sql_connecter::begin_connect()
{
	if( mysql_real_connect(mysql_base, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), 3306, NULL, 0) == NULL){
		//std::cerr<<"connect error"<<std::endl;
		return false;
	}else{
		//std::cout<<"connect done..."<<std::endl;
	}
	return true;
}

bool sql_connecter::close_connect()
{
	mysql_close(mysql_base);
	//std::cout<<"connect close..."<<std::endl;
}

bool sql_connecter::select_sql(std::string field_name[],std::string _out_data[][5], int &_out_row)
{
	std::string sql = "SELECT * FROM student_five_class";
	if(mysql_query(mysql_base, sql.c_str()) == 0){
		//std::cout<<"query success!"<<std::endl;
	}else{
		//std::cerr<<"query failed!"<<std::endl;
	}
	res = mysql_store_result(mysql_base);
	int row_num = mysql_num_rows(res);
	int field_num = mysql_num_fields(res);
	_out_row = row_num;

	//std::cout<<mysql_num_rows(res)<<std::endl;
	//std::cout<<mysql_num_fields(res)<<std::endl;

	//MYSQL_FIELD *	STDCALL mysql_fetch_field(MYSQL_RES *result);
	//fields name
	MYSQL_FIELD *fd = NULL;
	int i = 0;
	for(; fd = mysql_fetch_field(res); ){
		//std::cout<<fd->name<<"\t";
		field_name[i++] = fd->name;
	}
	//std::cout<<std::endl;
	//MYSQL_ROW	STDCALL mysql_fetch_row(MYSQL_RES *result);
	for(int index=0; index < row_num; index++){
    	MYSQL_ROW _row = mysql_fetch_row(res);
    	if(_row){
    		int start = 0;
    		for(; start < field_num; start++){
				_out_data[index][start] = _row[start];
    			//std::cout<<_row[start]<<"\t";
    		}
    		//std::cout<<std::endl;
    	}
	}
	return true;
}

bool sql_connecter::insert_sql(const std::string &data)
{
    std::string buf="create database if not exists ";
    buf+=db;
    buf+=";";
    if(mysql_query(mysql_base,buf.c_str()))
    {
        printf("%s,%d:error %u: %s\n",__FILE__,__LINE__,mysql_errno(mysql_base),mysql_error(mysql_base));
        exit(1);
    }
    buf.clear();
    buf+="use ";
    buf+=db;
    buf+=";";
    cout<<"buf: "<<buf<<"<br/>"<<endl;
    if(mysql_query(mysql_base,buf.c_str()))
    {
        printf("%s,%d:error %u: %s\n",__FILE__,__LINE__,mysql_errno(mysql_base),mysql_error(mysql_base));
        exit(1);
    }
    buf="create table if not exists ";
    buf+="student_five_class (name char(10) not null,age int,school char(10),hobby char(10),primary key(name));";
    if(mysql_query(mysql_base,buf.c_str()))
    {
        printf("%s,%d:error %u: %s\n",__FILE__,__LINE__,mysql_errno(mysql_base),mysql_error(mysql_base));
        exit(1);
    }
    cout<<"FFFFFFFFFFFFFFFFFFF<br/>"<<endl;
	std::string sql = "INSERT INTO student_five_class (name, age, school, hobby) values ";
	sql += "(";
	sql +=data;
	sql +=");";
    cout<<"sql: "<<sql<<endl;
	if(mysql_query(mysql_base, sql.c_str()) == 0){
		//std::cout<<"query success!"<<std::endl;
		return true;
	}else{
        printf("%s,%d:error %u: %s\n",__FILE__,__LINE__,mysql_errno(mysql_base),mysql_error(mysql_base));
		//std::cerr<<"query failed!"<<std::endl;
		return false;
	}
}

sql_connecter::~sql_connecter()
{
	close_connect();
	if(res != NULL){
		free(res);
	}
}

void sql_connecter::show_info()
{
	std::cout<<mysql_get_client_info()<<std::endl;
}

#ifdef _DEBUG_
int main()
{
	std::string _sql_data[1024][5];
	std::string header[5];
	int curr_row = -1;
	const std::string _host = "192.168.2.130";
	const std::string _user = "dandan";
	const std::string _passwd = "123456";
	const std::string _db   = "remote_db";
	const std::string data  = "'hill', 24, 'xgd', 'sleep'";
	sql_connecter conn(_host, _user, _passwd, _db);
	conn.begin_connect();
	conn.select_sql(header,_sql_data, curr_row);
	sleep(1);
	for(int i = 0; i<5; i++){
		std::cout<<header[i]<<"\t";
	}
	std::cout<<std::endl;

	for(int i = 0; i<curr_row; i++){
		for(int j=0; j<5; j++){
			std::cout<<_sql_data[i][j]<<"\t";
		}
		std::cout<<std::endl;
	}
	//conn.show_info();
}
#endif
