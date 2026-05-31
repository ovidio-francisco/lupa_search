
use Test_LUPA;
--  SELECT nome, lupa_clear(nome) from Peoples where nome like '%Sousa%' limit 10;
--  SELECT nome, lupa_phoneticBr(nome) from Peoples limit 10;
--  SELECT nome, length(nome), lupa_phoneticBr(nome), length(lupa_phoneticBr(nome)) from Peoples where nome like '%Sousa%' limit 10;


--  SELECT nome, length(nome), lupa_phoneticBr(nome), length(lupa_phoneticBr(nome)) from Peoples limit 40;


SELECT nome, length(nome), lupa_phoneticBr(nome), length(lupa_phoneticBr(nome))  
	from Peoples 
	where id in (313 , 660 , 3396 , 4941 , 5710 , 6673 , 7743 , 8190 , 8836 , 9745 , 9987);


