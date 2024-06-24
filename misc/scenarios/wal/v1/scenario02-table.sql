database drop Scenario_WAL_DB;
database create Scenario_WAL_DB;
database use Scenario_WAL_DB;

schema Scenario_WAL_Schema { name: string; salary: float; };
drop structure Scenario_WAL_table;
create table Scenario_WAL_table based on Scenario_WAL_Schema;

rename database from Scenario_WAL_DB to Scenario_WAL_DB_RENAME;
rename database from Scenario_WAL_DB_RENAME to Scenario_WAL_DB;
rename structure from Scenario_WAL_table to Scenario_WAL_table_RENAME;
rename structure from Scenario_WAL_table_RENAME to Scenario_WAL_table;
rename field from Scenario_WAL_table::salary to Scenario_WAL_table::salary_RENAME;
rename field from Scenario_WAL_table::salary_RENAME to Scenario_WAL_table::salary;

schema Scenario_WAL_Schema_dummy1 { name: string; };
drop structure Scenario_WAL_table_dummy1;
create table Scenario_WAL_table_dummy1 based on Scenario_WAL_Schema_dummy1;
schema Scenario_WAL_Schema_dummy2 { somefield: string; dummy1: dummy1; };
drop structure Scenario_WAL_table_dummy2;
create table Scenario_WAL_table_dummy2 based on Scenario_WAL_Schema_dummy2;
rebind Scenario_WAL_table_dummy2::dummy1 to Scenario_WAL_table_dummy1;
migrate structure Scenario_WAL_table_dummy2 to Scenario_WAL_Schema_dummy1 using [ somefield => name ];

insert into Scenario_WAL_table objects [ {"name":"Bob","salary":"4000"} {"name":"George","salary":"4500"} {"name":"Akshan","salary":"1000000"} ];
select from structure Scenario_WAL_table where ( 1 == 1 ) fields [ salary, name ];

update structure Scenario_WAL_table where ( name == Akshan ) modify [ salary => 2000000 ];
select from structure Scenario_WAL_table where ( 1 == 1 ) fields [ salary, name ];

truncate structure Scenario_WAL_table;
select from structure Scenario_WAL_table where ( 1 == 1 ) fields [ salary, name ];

insert into Scenario_WAL_table objects [ {"name":"Bob","salary":"4000"} {"name":"George","salary":"4500"} {"name":"Akshan","salary":"1000000"} ];
select from structure Scenario_WAL_table where ( 1 == 1 ) fields [ salary, name ];
delete from structure Scenario_WAL_table where ( 1 == 1 );
select from structure Scenario_WAL_table where ( 1 == 1 ) fields [ salary, name ];

user remove SomeUser;
user create SomeUser password passwd;
user remove SomeUser;
user create SomeUser password passwd;
user create SomeUser password passwd;
grant [  update, delete ] to SomeUser on Scenario_WAL_table;
revoke [ update, delete ] from SomeUser on Scenario_WAL_table;
commit;
savepoint d4b2758da0205c1e0aa9512cd188002a;
rollback d4b2758da0205c1e0aa9512cd188002a;
