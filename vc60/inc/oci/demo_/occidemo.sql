connect scott/tiger

DROP PROCEDURE demo_proc;
DROP FUNCTION demo_fun;

DROP TABLE author_tab;
DROP TABLE publisher_tab;
DROP TABLE publ_address_tab;
DROP TABLE journal_tab;
DROP TABLE article_tab;
DROP TABLE librarian_tab;
DROP TABLE book;
DROP TABLE cover;

DROP TYPE publ_address;
DROP TYPE librarian;
DROP TYPE people_obj;


DROP TABLE electronic_media;
DROP TYPE elheader_typ;
DROP TYPE elecdoc_tab;
DROP TYPE elecdoc_typ;

DROP TABLE foreign_student_tab;
DROP TABLE parttime_stud_tab;
DROP TABLE student_tab;
DROP TABLE people_tab;
DROP TYPE foreign_student;
DROP TYPE parttime_stud;
DROP TYPE student;
DROP TYPE people_typ;

CREATE TABLE author_tab ( 
  author_id NUMBER, 
  author_name VARCHAR2(25) 
); 

INSERT INTO author_tab (author_id, author_name) VALUES (333, 'JOE');
INSERT INTO author_tab (author_id, author_name) VALUES (444, 'SMITH');

CREATE OR REPLACE TYPE publ_address AS OBJECT ( 
  street_no NUMBER, 
  city VARCHAR2(25) 
) 
/ 

CREATE TABLE publisher_tab ( 
  publisher_id NUMBER, 
  publisher_add publ_address 
); 

INSERT INTO publisher_tab (publisher_id, publisher_add) VALUES 
(11, publ_address (121, 'NEW YORK'));

CREATE TABLE publ_address_tab OF publ_address; 

INSERT INTO publ_address_tab VALUES (22, 'BOSTON');
INSERT INTO publ_address_tab VALUES (33, 'BUFFALO');
INSERT INTO publ_address_tab VALUES (44, 'CALIFORNIA');


CREATE OR REPLACE TYPE journal AS TABLE OF VARCHAR2(50) 
/ 
CREATE TABLE journal_tab (jid NUMBER, jname journal) 
NESTED TABLE jname STORE AS journal_store;

INSERT INTO journal_tab (jid, jname) VALUES (22, journal ('NATION', 'TIMES'));
INSERT INTO journal_tab (jid, jname) VALUES (33, journal ('CRICKET', 'ALIVE'));

CREATE OR REPLACE TYPE people_obj AS OBJECT ( 
  ssn NUMBER, 
  name VARCHAR2(25) 
) NOT FINAL; 
/ 

CREATE OR REPLACE TYPE librarian UNDER people_obj( 
   empno NUMBER, 
   sal   NUMBER(7,2), 
   dob   DATE, 
   photo BLOB 
) 
/ 

CREATE TABLE librarian_tab OF librarian; 

INSERT INTO librarian_tab VALUES 
(101, 'DAVE', 1001, 10000, '12-Jan-1970', empty_blob());
INSERT INTO librarian_tab VALUES 
(102, 'BOB', 1002, 12000, '17-Jan-1970', empty_blob());

CREATE TABLE article_tab ( 
  artid NUMBER, 
  artdesc VARCHAR2(4000), 
  artsummary LONG,
  artfeedbk VARCHAR2(2000)
); 

CREATE OR REPLACE PROCEDURE demo_proc (col1 IN NUMBER, col2 IN OUT VARCHAR2,
col3 OUT CHAR) AS
BEGIN 
  col2 := 'IN-OUT';
  col3 := 'OUT'; 
END;
/

CREATE OR REPLACE FUNCTION demo_fun (col1 IN NUMBER,
col2 IN OUT VARCHAR2, col3 OUT CHAR) RETURN CHAR AS 
BEGIN 
  col2 := 'IN-OUT'; col3 := 'OUT'; RETURN 'abcd';
END;
/

CREATE TABLE book (bookid NUMBER, summary VARCHAR2(4000));

CREATE TABLE cover (c1 NUMBER(5), c2 VARCHAR2(20));

DECLARE 
ch1 VARCHAR2(4000) := 'aa'; 
ch2 VARCHAR2(4000):= '';
nu NUMBER := 0; 
BEGIN 
  FOR nu IN 1..11 LOOP
    ch2 := ch1 || ch2; ch1 := ch2; 
  END LOOP; 
  INSERT INTO book (bookid, summary) VALUES (11, ch1); 
END;
/

CREATE TYPE elecdoc_typ AS OBJECT
    ( document_typ      VARCHAR2(32)
    , formatted_doc     BLOB
    ) ;
/
CREATE TYPE elecdoc_tab AS TABLE OF elecdoc_typ;
/

CREATE TYPE elheader_typ AS OBJECT
    ( header_name        VARCHAR2(256)
    , creation_date      DATE
    , header_text        VARCHAR2(1024)
    , logo               BLOB
    );
/

CREATE TABLE electronic_media
    ( product_id        NUMBER(6)
    , ad_id             NUMBER(6)
    , ad_composite      BLOB
    , ad_sourcetext     CLOB
    , ad_finaltext      CLOB
    , ad_fltextn        NCLOB
    , ad_elecdocs_ntab  elecdoc_tab
    , ad_photo          BLOB
    , ad_graphic        BFILE
    , ad_header         elheader_typ
    , press_release     LONG
    ) NESTED TABLE ad_elecdocs_ntab STORE AS elecdocs_nestedtab;
CREATE UNIQUE INDEX printmedia_pk
    ON electronic_media (product_id, ad_id);

ALTER TABLE electronic_media
ADD ( CONSTRAINT printmedia__pk
      PRIMARY KEY (product_id, ad_id)
    ) ;



CREATE TYPE people_typ AS OBJECT
(
  name VARCHAR2(30),
  ssn NUMBER,
  dob DATE
) not final;
/

CREATE TABLE people_tab OF people_typ;

INSERT INTO people_tab VALUES (people_typ('john', 111, '01-Jan-1970'));
INSERT INTO people_tab VALUES (people_typ('jill', 666, '06-Jan-1976'));

CREATE TYPE student UNDER people_typ
(
  stud_id NUMBER,
  teammate REF people_typ
) NOT FINAL;
/

CREATE TABLE student_tab OF student;
INSERT INTO student_tab VALUES ('jimmy',222,'02-Feb-1976',200,
(SELECT REF(a) FROM people_tab a where name='john'));

CREATE TYPE parttime_stud UNDER student
(
  course_id NUMBER,
  partner REF student
)NOT FINAL;
/
CREATE TABLE parttime_stud_tab OF parttime_stud;

INSERT INTO parttime_stud_tab VALUES ('james',333,'03-Feb-1976',300,
(SELECT REF(a) FROM people_tab a where name='john'),3000,
(SELECT REF(a) FROM student_tab a));


CREATE TYPE foreign_student UNDER parttime_stud
(
  country VARCHAR2(30),
  leader REF parttime_stud
);
/
CREATE TABLE foreign_student_tab OF foreign_student;

COMMIT;


