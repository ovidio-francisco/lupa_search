drop database if exists Test_SO;
create database Test_SO;
use Test_SO;

drop function if exists lupa_clear;
create function lupa_clear 
	returns STRING 
    SONAME 'liblupa_mysql.so';


drop function if exists lupa_phoneticBr ;
create function lupa_phoneticBr 
	returns STRING 
    SONAME 'liblupa_mysql.so';
    
select lupa_clear     ("Olá Ovídio José, uniso") as Clear;
select lupa_phoneticBr("Olá Ovídio José, uniso") as Phonetic;

