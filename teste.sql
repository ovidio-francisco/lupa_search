--  drop database if exists Test_SO;
--  create database Test_SO;
--  use Test_SO;


--  drop function if exists lupa_similarity;
--  create function lupa_similarity 
	--  returns real
    --  SONAME 'liblupa_mysql.so';


--  drop function if exists lupa_clear;
--  create function lupa_clear 
	--  returns STRING 
    --  SONAME 'liblupa_mysql.so';


--  drop function if exists lupa_phoneticBr ;
--  create function lupa_phoneticBr 
	--  returns STRING 
    --  SONAME 'liblupa_mysql.so';
   

select lupa_clear     ("Olá Ovídio José, uniso") as Clear;
select lupa_phoneticBr("Olá Ovídio José, uniso") as Phonetic;
select lupa_similarity("Olá Ovídio José", "Olá uniso") as Simi;
select lupa_similarity("maça banana goiaba goiaba banana",
					   "goiaba uva maça maça") as Simi;

-- medium: full sentence
SELECT lupa_clear('O rato roeu a roupa do rei de Roma e a rainha com raiva resolveu remendar') as Clear;

-- larger: paragraph
SELECT lupa_clear('A inteligência artificial tem transformado a maneira como interagimos com a tecnologia. Sistemas de processamento de linguagem natural permitem que máquinas compreendam e gerem texto humano com precisão crescente.') as Clear;

-- stress: repeated long string
SELECT lupa_clear(REPEAT('Ação é tão simples quanto parece ser ', 50)) as Clear;

-- edge cases
SELECT lupa_clear('') as Empty;
SELECT lupa_clear(NULL) as 'Null';
SELECT lupa_clear('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA') as 'Long';
