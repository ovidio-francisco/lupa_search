drop database if exists Test_SO;
create database Test_SO;
use Test_SO;

drop function if exists lupa_in_mysql;

create function lupa_in_mysql 
	returns STRING 
    SONAME 'liblupa_mysql.so';
    
select lupa_in_mysql("Olá Ovídio José, uniso") as upper;

