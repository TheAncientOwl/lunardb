database drop joins_db;
database create joins_db;
database use joins_db;
schema document_join_schema01 { field1: String; field2: Integer; };
schema document_join_schema02 { str: String; obj: document_join_schema01; };
create collection somedocument_join based on document_join_schema02;
insert into somedocument_join objects [  
  { "str": "val1", "obj": { "field1": "val11", "field2": "1" } }  
  { "str": "val2", "obj": { "field1": "val22", "field2": "2" } }
];
select from structure somedocument_join where ( 1 == 1 ) fields [ str, obj, obj.field1, obj.field2 ];
update structure somedocument_join where ( str == val2 ) modify [ obj.field1 => val33, obj.field2 => obj.field2 + 1 ];
select from structure somedocument_join where ( 1 == 1 ) fields [ str, obj, obj.field1, obj.field2 ];
update structure somedocument_join where ( obj.field1 == val33 ) modify [ obj.field1 => val44, obj.field2 => obj.field2 + 1 ];
select from structure somedocument_join where ( 1 == 1 ) fields [ str, obj, obj.field1, obj.field2 ];
