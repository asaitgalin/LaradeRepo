unit MySqlite;

interface

uses
  Windows, Classes, SysUtils, MyStringUtils;

type
  HSQLCONTEXT = Pointer;
  HSQLDB = Pointer;
  HSQLSTMT = Pointer;
  HSQLVALUE = Pointer;

  { TMySqlTable }

  TMySqlTable = class(TObject)
  private
    FColumns: TStringList;
    FQuery: HSQLSTMT;
  protected
    function GetFieldIndex(const AName: WideString): Integer;
    procedure UpdateColumns;
  public
    constructor Create(AQuery: HSQLSTMT); virtual;
    destructor Destroy; override;
    function NextRecord: Boolean;
    // Read
    function ReadString(AIndex: Integer): WideString; overload;
    function ReadString(const AName: WideString): WideString; overload;
    function ReadInteger(AIndex: Integer): Integer; overload;
    function ReadInteger(const AName: WideString): Integer; overload;
  end;

  { TMySqlBase }

  TMySqlBase = class(TObject)
  private
    FDataBase: HSQLDB;
    FLastQuery: WideString;
    FShowErrors: Boolean;
  protected
    function CheckError(AError: Integer): Boolean;
    procedure ErrorMessage(AMsg: PWideChar);
    function PrepareQuery(const AQuery: WideString; var AStmt: HSQLSTMT): Boolean;
  public
    constructor Create(const AFile: WideString); virtual;
    destructor Destroy; override;
    function ExecQuery(const AQuery: WideString): Boolean; overload;
    function ExecQuery(const AQuery: WideString; out ATable: TMySqlTable): Boolean; overload;
    property ShowErrors: Boolean read FShowErrors write FShowErrors;
  end;

implementation

const
  sqlite_dll = 'sqlite3.dll';

const
  // Values
  SQLITE_INTEGER = 1;
  SQLITE_FLOAT   = 2;
  SQLITE_TEXT	   = 3;
  SQLITE_BLOB	   = 4;
  SQLITE_NULL	   = 5;

  SQLITE_OK         = 0;
  SQLITE_ROW        = 100;

  SQLITE_UTF16         = 4;

  SQLErrorMessage   = 'SQLite Error: ' + CRLF + '%s'  + CRLF + 'Last query:' + CRLF + '%s';

type
  TSQLCompare = function (AUserData: Pointer; P1Size: Integer; P1: PWideChar; P2Size: Integer; P2: PWideChar): Integer; cdecl;
  TSQLFunction = procedure (AContext: HSQLCONTEXT; ACount: Integer; AVars: PPointerArray); cdecl;
  TSQLFunctionFinal = procedure (AContext: HSQLCONTEXT); cdecl;
  TSQLDestroyText = procedure (P: PWideChar); cdecl;

// Misc
function sqlite3_close(ADataBase: HSQLDB): Integer; cdecl; external sqlite_dll;
function sqlite3_finalize(AStmt: HSQLSTMT): Integer; cdecl; external sqlite_dll;
function sqlite3_open16(AFile: PWideChar; var ADataBase: HSQLDB): Integer; cdecl; external sqlite_dll;
function sqlite3_prepare16_v2(ADataBase: HSQLDB; AQuery: PWideChar; ALen: Integer;
  var AStmt: HSQLSTMT; var ATail: PWideChar): Integer; cdecl; external sqlite_dll;
function sqlite3_step(AStmt: HSQLSTMT): Integer; cdecl; external sqlite_dll;
function sqlite3_errmsg16(ADataBase: HSQLDB): PWideChar; cdecl; external sqlite_dll;
function sqlite3_column_count(AStatement: HSQLSTMT): Integer; cdecl; external sqlite_dll;
function sqlite3_create_collation16(ADataBase: HSQLDB; AName: PWideChar; ATextType: Integer; AUserData: Pointer; ACompareProc: TSQLCompare): Integer; cdecl; external sqlite_dll;
function sqlite3_busy_timeout(ADataBase: HSQLDB; AMs: Integer): Integer; cdecl; external sqlite_dll;
function sqlite3_create_function16(ADataBase: HSQLDB; const AName: PWideChar; AArg, AEnc: Integer;
  AUserData: Pointer; AFunc, AStep: TSQLFunction; AFinal: TSQLFunctionFinal): Integer; cdecl; external sqlite_dll;

// Read
function sqlite3_column_int(AStatement: HSQLSTMT; AColumn: Integer): Integer; cdecl; external sqlite_dll;
function sqlite3_column_name16(AStatement: HSQLSTMT; ID: Integer): PWideChar; cdecl; external sqlite_dll;
function sqlite3_column_text16(AStatement: HSQLSTMT; AColumn: Integer): PWideChar; cdecl; external sqlite_dll;
function sqlite3_column_bytes16(AStatement: HSQLSTMT; AColumn: Integer): Integer; cdecl; external sqlite_dll;

// Values
function sqlite3_value_bytes16(AValue: HSQLVALUE): Integer; cdecl; external sqlite_dll;
function sqlite3_value_text16(AValue: HSQLVALUE): PWideChar; cdecl; external sqlite_dll;
function sqlite3_value_type(AValue: HSQLVALUE): Integer; cdecl; external sqlite_dll;

// Result
procedure sqlite3_result_text16(AContext: HSQLCONTEXT; P: PWideChar; ASize: Integer; ADestroyCallback: TSQLDestroyText); cdecl; external sqlite_dll;
procedure sqlite3_result_value(AContext: HSQLCONTEXT; AValue: HSQLVALUE); cdecl; external sqlite_dll;

// Strings

function SQLite_VarToText(AValue: Pointer): WideString;
begin
  SetString(Result, sqlite3_value_text16(AValue), sqlite3_value_bytes16(AValue) div SizeOf(WideChar));
end;

// Functions

procedure SQLite_FreeText(P: PWideChar); cdecl;
begin
  FreeMem(P);
end;

function UnicodeCompare(AUserData: Pointer; P1Size: Integer; P1: PWideChar; P2Size: Integer; P2: PWideChar): Integer; cdecl;
begin
  Result := CompareStringW(LOCALE_USER_DEFAULT, NORM_IGNORECASE,
    P1, P1Size div SizeOf(WideChar), P2, P2Size div SizeOf(WideChar)) - CSTR_EQUAL;
end;

procedure UnicodeUpper(AContext: HSQLCONTEXT; ACount: Integer; AVars: PPointerArray); cdecl;
var
  ABuffer: WideString;
begin
  if sqlite3_value_type(AVars^[0]) = SQLITE_TEXT then
  begin
    ABuffer := WideUpperCase(SQLite_VarToText(AVars^[0]));
    sqlite3_result_text16(AContext, WideAllocStr(ABuffer), Length(ABuffer) * SizeOf(WideChar), @SQLite_FreeText);
  end
  else
    sqlite3_result_value(AContext, AVars^[0]);
end;

{ TMySqlTable }

constructor TMySqlTable.Create(AQuery: HSQLSTMT);
begin
  inherited Create;
  FQuery := AQuery;
  FColumns := TStringList.Create;
end;

destructor TMySqlTable.Destroy;
begin
  sqlite3_finalize(FQuery);
  FreeAndNil(FColumns);
  inherited Destroy;
end;

function TMySqlTable.GetFieldIndex(const AName: WideString): Integer;
begin
  if FColumns.Count = 0 then
    UpdateColumns;
  Result := FColumns.IndexOf(AName);
end;

function TMySqlTable.NextRecord: Boolean;
begin
  Result := (sqlite3_step(FQuery) = SQLITE_ROW);
end;

function TMySqlTable.ReadInteger(AIndex: Integer): Integer;
begin
  Result := sqlite3_column_int(FQuery, AIndex);
end;

function TMySqlTable.ReadInteger(const AName: WideString): Integer;
begin
  Result := ReadInteger(GetFieldIndex(AName));
end;

function TMySqlTable.ReadString(AIndex: Integer): WideString;
var
  ASize: Integer;
  S: PWideChar;
begin
  ASize := sqlite3_column_bytes16(FQuery, AIndex);
  S := sqlite3_column_text16(FQuery, AIndex);
  SetString(Result, S, ASize div SizeOf(WideChar));
end;

function TMySqlTable.ReadString(const AName: WideString): WideString;
begin
  Result := ReadString(GetFieldIndex(AName));
end;

procedure TMySqlTable.UpdateColumns;
var
  ACount, I: Integer;
begin
  FColumns.Clear;
  ACount := sqlite3_column_count(FQuery);
  FColumns.Capacity := ACount;
  for I := 0 to ACount - 1 do
    FColumns.Add(sqlite3_column_name16(FQuery, I));
end;

{ TMySqlBase }

constructor TMySqlBase.Create(const AFile: WideString);
begin
  inherited Create;
  if FDataBase = nil then
  begin
    FShowErrors := True;
    CheckError(sqlite3_open16(PWideChar(AFile), FDataBase));
    CheckError(sqlite3_create_collation16(FDataBase, 'UNICODE', SQLITE_UTF16, nil, @UnicodeCompare));
    CheckError(sqlite3_create_function16(FDataBase, 'UPPER', 1, SQLITE_UTF16, nil, @UnicodeUpper, nil, nil));
    sqlite3_busy_timeout(FDataBase, 100);
  end;
end;

destructor TMySqlBase.Destroy;
begin
  sqlite3_close(FDataBase);
  inherited Destroy;
end;

function TMySqlBase.CheckError(AError: Integer): Boolean;
begin
  Result := (AError = SQLITE_OK);
  if not Result then
    ErrorMessage(sqlite3_errmsg16(FDataBase));
end;

procedure TMySqlBase.ErrorMessage(AMsg: PWideChar);
var
  S: WideString;
begin
  if ShowErrors then
  begin
    S := Format(SQLErrorMessage, [AMsg, FLastQuery]);
    MessageBoxW(HWND_DESKTOP, PWideChar(S), nil, MB_ICONERROR or MB_OK);
  end;
end;

function TMySqlBase.ExecQuery(const AQuery: WideString): Boolean;
var
  AStatement: HSQLSTMT;
begin
  Result := PrepareQuery(AQuery, AStatement);
  if Result then
  try
    sqlite3_step(AStatement);
  finally
    sqlite3_finalize(AStatement);
  end;
end;

function TMySqlBase.ExecQuery(const AQuery: WideString; out ATable: TMySqlTable): Boolean;
var
  AStatement: HSQLSTMT;
begin
  Result := PrepareQuery(AQuery, AStatement);
  if Result then
  begin
    Result := (sqlite3_step(AStatement) = SQLITE_ROW);
    if Result then
      ATable := TMySqlTable.Create(AStatement)
    else
      sqlite3_finalize(AStatement);
  end;
end;

function TMySqlBase.PrepareQuery(const AQuery: WideString; var AStmt: HSQLSTMT): Boolean;
var
  ATail: PWideChar;
begin
  AStmt := nil;
  FLastQuery := AQuery;
  Result := CheckError(sqlite3_prepare16_v2(FDataBase, PWideChar(AQuery),
                       Length(AQuery) * SizeOf(WideChar), AStmt, ATail));
end;

end.
