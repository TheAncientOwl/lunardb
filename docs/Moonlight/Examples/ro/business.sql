-- 1. DATABASE
database create FirmăDeCurieratBD;
database use FirmăDeCurieratBD;

-- 2. SCHEMA
schema Persoană_V0 {
    nume: String;
    prenume: String;
    nr_telefon: String;
};

schema Persoană_V1 inherits Persoană_V0 {
    CNP: String;
    data_naștere: DateTime;
    email: String;
};

schema Angajat inherits Persoană_V1 {
    data_angajare: DateTime;
    salariu: Float;
    funcție: String;
};

schema Client inherits Persoană_V1 {};

schema PersoanăDeContact inherits Persoană_V0 {};

schema Adresă {
    județ: String;
    oraș: String;
    detalii: String;
};

schema Colet {
    curier: Angajat;
    client: Client;
    persoană_contact: PersoanăDeContact;
    adresă_livrare: Adresă;
    adresă_facturare: Adresă;
    greutate_grame: Integer;
    preț_expediere: Float;
};

schema ȘedințăSuport {
    operator: Angajat;
    client: Client;
    dată: DateTime;
    descriere: String;
};

-- 3. CREATE

create tables from [ Colet, ȘedințăSuport ] using format "%TypeName%_Data";

create documents from [ Colet, ȘedințăSuport ] using format "%TypeName%_NOSQL";
create tables from [ Angajat, Client, Adresă ] using format "%TypeName%_SQL";

-- 4. REBIND
rebind Colet_NOSQL::curier to Angajat_SQL clean;
rebind Colet_NOSQL::client to Client_SQL clean;
rebind Colet_NOSQL::adresă_livrare to Adresă_SQL clean;
rebind Colet_NOSQL::adresă_facturare to Adresă_SQL clean;

rebind ȘedințăSuport_NOSQL::operator to Angajat_SQL clean;
rebind ȘedințăSuport_NOSQL::client to Client_SQL clean;

-- 5. MIGRATE
schema ȘedințăSuportExtinsă inherits ȘedințăSuport {
    durata: String;
};

migrate structure ȘedințăSuport_NOSQL to ȘedințăSuportExtinsă using [
    dată => dată_ședință
];

-- 6. INSERT
insert into Angajat_SQL objects [
    {
        "nume": "Avramescu",
        "prenume": "Ion",
        "nr_telefon": "0729304928",
        "CNP": "5003009292012",
        "data_naștere": 22/10/1997,
        "email": "ion.avramescu@email.com",
        "data_angajare": 15/05/2020,
        "salariu": 5400.00,
        "funcție": "Curier"
    }
];

-- 7. SELECT
select from Angajat_SQL
    where (lower(funcție) like "Curier" and salariu between 5000 and 5500)
    fields [ nume, prenume, data_naștere, data_angajare, salariu ]
    order by [ salariu desc, data_angajare desc, data_naștere asc ];

-- 8. TRUNCATE
truncate structure Angajat_SQL;

-- 9. DROP
drop structure Angajat_SQL;

-- 10. DELETE
delete from Angajat_SQL
    where (lower(funcție) like "Curier" and salariu between 5000 and 5500);

-- 11. UPDATE
update structure Angajat_SQL
    where (lower(funcție) like "Curier" and salariu between 5000 and 5500)
    modify [
        salariu => salariu + salariu * 5 / 100;
    ];

-- 12. USER
user create PopescuIon;
user remove PopescuIon;

-- 13. GRANT
grant [ insert, update ] 
    to PopescuIon
    on Angajat_SQL;

-- 14. REVOKE
grant [ insert, update ] 
    from PopescuIon
    on Angajat_SQL;

-- 15. RENAME
rename structure from Angajat_SQL to Angajati_SQL;
rename field from Angajați_SQL::funcție to Angajati_SQL::funcție_angajat;
rename database from FirmăDeCurieratBD to FirmăDeCurierat_BD;

-- 16. COMMIT, ROLLBACK, SAVEPOINT
// tranzacții realizate...
commit;
rollback; // (1)
// alte tranzacții în derulare (2)
savepoint hash-tranzacții-set-1; // (3)
// alte tranzactii în derulare (4)
rollback hash-tranzacții-set-1; // (5)
