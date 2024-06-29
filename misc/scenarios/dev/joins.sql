database drop table_test;
database create table_test;
database use table_test;

schema table_schema01 { field1: String; field2: Integer; };
schema table_schema02 { str: String; obj: table_schema01; };

create table sometable based on table_schema02;

insert into sometable objects [  
  { "str": "val1", "obj": { "field1": "val11", "field2": "1" } }  
  { "str": "val2", "obj": { "field1": "val22", "field2": "2" } }
];
