database drop joins_db;
database create joins_db;
database use joins_db;
schema table_join_schema01 { field1: String; field2: Integer; };
schema table_join_schema02 { str: String; obj: table_join_schema01; };
create table sometable_join based on table_join_schema02;
insert into sometable_join objects [  
  { "str": "val1", "obj": { "field1": "val11", "field2": "1" } }  
  { "str": "val2", "obj": { "field1": "val22", "field2": "2" } }
];
select from structure sometable_join where ( 1 == 1 ) fields [ str, obj, obj.field1, obj.field2 ];
