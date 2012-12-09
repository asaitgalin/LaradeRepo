unit MyStringUtils;

interface

uses
  Classes, SysUtils, Windows;

type

  { TMyParser }

  TMyParser = class(TObject)
  private
    FCurrentBlockIndex: Integer;
    FCursor: Integer;
    FData: WideString;
    FDataLen: Integer;
    FDelims: WideString;
  protected
    procedure ExtractCustomBlock(out AValue: PWideChar; out AValueLen: Integer);
    function GetSymbol(out W: WideChar): Boolean;
    function IsDelim(W: WideChar): Boolean;
    function IsSpace(W: WideChar): Boolean;
    procedure SkipSpaces;
  public
    constructor Create(const AData, ADelims: WideString); virtual;
    property CurrentBlockIndex: Integer read FCurrentBlockIndex;
    function ExtractBlock(out AValue: PWideChar; out AValueLen: Integer): Boolean;
  end;

  // Strings

  TMyStringEncoding = (seUTF16, seUTF8, seANSI);

const
  Utf16BOM: array[0..1] of Byte = ($FF, $FE);
  Utf16BOMSize = 2;

  Utf8BOM: array[0..2] of Byte = ($EF, $BB, $BF);
  Utf8BOMSize = 3;

  CRLF = #13#10;
  CRLFSize = 4;

function StringDetectEncoding(const S: RawByteString; out PrefixSize: Byte): TMyStringEncoding;
function StringToRect(const S: WideString): TRect;
function RectToStr(R: TRect): WideString;
function WideAllocStr(const S: WideString): PWideChar;

implementation

{ TMyParser }

constructor TMyParser.Create(const AData, ADelims: WideString);
begin
  FCurrentBlockIndex := -1;
  FData := AData;
  FDataLen := Length(FData);
  FDelims := ADelims;
  FCursor := 1;
end;

procedure TMyParser.ExtractCustomBlock(out AValue: PWideChar; out AValueLen: Integer);
var
  ALastCursor: Integer;
  W: WideChar;
begin
  AValueLen := 0;
  ALastCursor := FCursor;
  while GetSymbol(W) and not IsDelim(W) do
    Inc(FCursor);
  AValue := @FData[ALastCursor];
  AValueLen := FCursor - ALastCursor;
end;

function TMyParser.ExtractBlock(out AValue: PWideChar; out AValueLen: Integer): Boolean;
begin
  AValueLen := 0;
  if FCursor <= FDataLen then
  begin
    SkipSpaces;
    ExtractCustomBlock(AValue, AValueLen);
    Inc(FCurrentBlockIndex);
    SkipSpaces;
  end;
  Result := (AValueLen > 0);
end;

function TMyParser.GetSymbol(out W: WideChar): Boolean;
begin
  Result := False;
  if FCursor <= FDataLen then
  begin
    W := FData[FCursor];
    Result := True;
  end;
end;

function TMyParser.IsDelim(W: WideChar): Boolean;
var
  I: Integer;
begin
  Result := False;
  for I := 1 to Length(FDelims) do
    if W = FDelims[I] then Result := True;
end;

function TMyParser.IsSpace(W: WideChar): Boolean;
begin
  Result :=  (W = ' ') or (W = #9) or (W = #13) or (W = #10);
end;

procedure TMyParser.SkipSpaces;
var
  W: WideChar;
begin
  while GetSymbol(W) and (IsSpace(W) or IsDelim(W)) do
    Inc(FCursor);
end;

// Strings

function StringDetectEncoding(const S: RawByteString; out PrefixSize: Byte): TMyStringEncoding;
begin
  PrefixSize := 0;
  Result := seANSI;
  if (Byte(S[1]) = Utf16BOM[0]) and (Byte(S[2]) = Utf16BOM[1]) then
  begin
    PrefixSize := Utf16BOMSize;
    Result := seUTF16;
  end;
  if (Byte(S[1]) = Utf8BOM[0]) and (Byte(S[2]) = Utf8BOM[1]) and (Byte(S[3]) = Utf8BOM[2]) then
  begin
    PrefixSize := Utf8BOMSize;
    Result := seUTF8;
  end;
end;

function StringToRect(const S: WideString): TRect;
var
  AParser: TMyParser;
  AValue: PWideChar;
  AValueLen: Integer;
  ATemp: WideString;
begin
  Result := Rect(0, 0, 0, 0);
  AParser := TMyParser.Create(S, ',');
  try
    while AParser.ExtractBlock(AValue, AValueLen) do
    begin
      SetString(ATemp, AValue, AValueLen);
      case AParser.CurrentBlockIndex of
        0: Result.Left := StrToInt(ATemp);
        1: Result.Top := StrToInt(ATemp);
        2: Result.Right := StrToInt(ATemp);
        3: Result.Bottom := StrToInt(ATemp);
      end;
    end;
  finally
    AParser.Free;
  end;
end;

function RectToStr(R: TRect): WideString;
begin
  Result := IntToStr(R.Left) + ',' + IntToStr(R.Top) + ',' +
            IntToStr(R.Right) + ',' + IntToStr(R.Bottom);
end;

function WideAllocStr(const S: WideString): PWideChar;
var
  ALen: Integer;
begin
  ALen := Length(S);
  Result := AllocMem((ALen + 1) * SizeOf(WideChar));
  ZeroMemory(Result, (ALen + 1) * SizeOf(WideChar));
  Move(S[1], Result^, ALen * SizeOf(WideChar));
end;

end.
