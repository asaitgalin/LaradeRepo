unit HomeLibrary_Query;

interface

const
  SQL_CreateBooksTable = 'CREATE TABLE Books (ID INTEGER PRIMARY KEY AUTOINCREMENT, sName TEXT COLLATE UNICODE, ' +
                       'sAuthor TEXT COLLATE UNICODE, iYear INTEGER, sPublisher TEXT COLLATE UNICODE, ' +
                       'sPlace TEXT COLLATE UNICODE, sGroup TEXT COLLATE UNICODE);';

  SQL_InsertValue = 'INSERT INTO Books VALUES (NULL, "%s", "%s", "%d", "%s", "%s", "%s");';
  SQL_RemoveValue = 'DELETE FROM Books WHERE ID=';
  // Select
  SQL_SelectAllValues = 'SELECT * FROM Books;';
  SQL_SelectDistinctiveValues = 'SELECT DISTINCT %s FROM Books;';
  SQL_SelectFilterValues = 'SELECT * FROM Books WHERE ';
  SQL_UpdateValue = 'UPDATE Books SET sName="%s", sAuthor="%s", iYear="%d", sPublisher="%s", ' +
                   'sPlace="%s", sGroup="%s" WHERE ID=';

implementation

end.
