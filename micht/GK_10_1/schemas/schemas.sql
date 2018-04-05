-- Horizontale Fragmentierung
-- Kriterien: Erstes Halbjahr 2009; Nettoamount > 300

DROP SCHEMA IF EXISTS horizontal;

CREATE SCHEMA horizontal;

DROP TABLE IF EXISTS horizontal.firstHalfYearBigger300;
CREATE TABLE horizontal.firstHalfYearBigger300 AS (SELECT * FROM orders WHERE netamount > 300 AND orderdate < '2009-07-01');

DROP TABLE IF EXISTS horizontal.secondHalfYearBigger300;
CREATE TABLE horizontal.secondHalfYearBigger300 AS (SELECT * FROM orders WHERE netamount > 300 AND orderdate >= '2009-07-01');

DROP TABLE IF EXISTS horizontal.firstHalfYearSmaller300;
CREATE TABLE horizontal.firstHalfYearSmaller300 AS (SELECT * FROM orders WHERE netamount <= 300 AND orderdate < '2009-07-01');

DROP TABLE IF EXISTS horizontal.secondHalfYearSmaller300;
CREATE TABLE horizontal.secondHalfYearSmaller300 AS (SELECT * FROM orders WHERE netamount <= 300 AND orderdate >= '2009-07-01');

-- Vertikale Fragmentierung
-- Nur Preise mit Titel und ID

DROP SCHEMA IF EXISTS vertical;

CREATE SCHEMA vertical;

DROP TABLE IF EXISTS vertical.shelfProducts;
CREATE TABLE vertical.shelfProducts AS (SELECT prod_id, title, price FROM products);

DROP TABLE IF EXISTS vertical.otherProducts;
CREATE TABLE vertical.otherProducts AS (SELECT prod_id, category, actor, special, common_prod_id  FROM products);


-- Kombinierte Fragmentierung
-- Horizontal: Erstes Halbjahr 2009; Nettoamount > 300
-- Vertikal: Steuergelder mit Totalamount
-- Nützlich für staatliche Analysen 

DROP SCHEMA IF EXISTS combined CASCADE;

CREATE SCHEMA combined;

DROP TABLE IF EXISTS combined.firstHalfYearBigger300Tax;
CREATE TABLE combined.firstHalfYearBigger300Tax AS (SELECT orderid, tax, totalamount FROM orders WHERE netamount > 300 AND orderdate < '2009-07-01');

DROP TABLE IF EXISTS combined.secondHalfYearBigger300Tax;
CREATE TABLE combined.secondHalfYearBigger300Tax AS (SELECT orderid, tax, totalamount FROM orders WHERE netamount > 300 AND orderdate >= '2009-07-01');

DROP TABLE IF EXISTS combined.firstHalfYearSmaller300Tax;
CREATE TABLE combined.firstHalfYearSmaller300Tax AS (SELECT orderid, tax, totalamount FROM orders WHERE netamount <= 300 AND orderdate < '2009-07-01');

DROP TABLE IF EXISTS combined.secondHalfYearSmaller300Tax;
CREATE TABLE combined.secondHalfYearSmaller300Tax AS (SELECT orderid, tax, totalamount FROM orders WHERE netamount <= 300 AND orderdate >= '2009-07-01');

DROP TABLE IF EXISTS combined.otherOrders;
CREATE TABLE combined.otherOrders AS (SELECT orderid, orderdate, customerid, netamount FROM orders);

-- Horizontale Fragmentierung beweis: 
--  Anzahl der Orders vor der Fragmentierung

SELECT COUNT(*) FROM orders;

-- Anzahl Datensätze firstHalfYearBigger300

SELECT COUNT(*) FROM horizontal.firstHalfYearBigger300;

-- Anzahl Datensätze secondHalfYearBigger300

SELECT COUNT(*) FROM horizontal.secondHalfYearBigger300;

-- Anzahl Datensätze firstHalfYearSmaller300

SELECT COUNT(*) FROM horizontal.firstHalfYearSmaller300;

-- Anzahl Datensätze secondHalfYearBigger300

SELECT COUNT(*) FROM horizontal.secondHalfYearSmaller300;
-- Alle zusammenfügen und zählen

SELECT COUNT(*) FROM (SELECT * FROM horizontal.firstHalfYearBigger300 UNION SELECT * FROM horizontal.secondHalfYearBigger300 UNION SELECT * FROM horizontal.firstHalfYearSmaller300 UNION SELECT * FROM horizontal.secondHalfYearSmaller300) AS "sub";
SELECT COUNT(*) FROM orders;



-- Vertikale Fragmentierung beweis:
DROP TABLE IF EXISTS vertical.proofTable;
CREATE Table vertical.proofTable AS (SELECT * FROM vertical.shelfProducts NATURAL JOIN vertical.otherProducts);

-- Originale Tabelle
\d products
-- Beweis tabelle
\d proofTable


-- kombinierte Fragmentierung beweis:
--  Anzahl der Orders vor der Fragmentierung

SELECT COUNT(*) FROM orders;

-- Anzahl Datensätze firstHalfYearBigger300Tax

SELECT COUNT(*) FROM combined.firstHalfYearBigger300Tax;

-- Anzahl Datensätze secondHalfYearBigger300Tax

SELECT COUNT(*) FROM combined.secondHalfYearBigger300Tax;

-- Anzahl Datensätze firstHalfYearSmaller300Tax

SELECT COUNT(*) FROM combined.firstHalfYearSmaller300Tax;

-- Anzahl Datensätze secondHalfYearBigger300Tax

SELECT COUNT(*) FROM combined.secondHalfYearSmaller300Tax;

DROP TABLE IF EXISTS combined.taxOrders;
CREATE Table combined.taxOrders AS (SELECT * FROM combined.firstHalfYearBigger300Tax UNION SELECT * FROM combined.secondHalfYearBigger300Tax UNION SELECT * FROM combined.firstHalfYearSmaller300Tax UNION SELECT * FROM combined.secondHalfYearSmaller300Tax);

DROP TABLE IF EXISTS combined.proofTable;
CREATE TABLE combined.proofTable AS (SELECT * FROM combined.taxOrders NATURAL JOIN combined.otherOrders);

-- Sollte das gleiche Ergebnis wie von SELECT COUNT(*) FROM orders; sein
SELECT COUNT(*) FROM combined.proofTable;

-- Originale Tabelle
\d orders
-- Beweis Tabelle für Spalten
\d combined.proofTable
