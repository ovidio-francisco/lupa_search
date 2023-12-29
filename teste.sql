drop database if exists Test_SO;
create database Test_SO;
use Test_SO;


drop function if exists lupa_similarity;
create function lupa_similarity 
	returns real
    SONAME 'liblupa_mysql.so';


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
select lupa_similarity("Olá Ovídio José", "Olá uniso") as Simi;
select lupa_similarity("maça banana goiaba goiaba banana",
					   "goiaba uva maça maça") as Simi;


