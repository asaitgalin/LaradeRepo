unit HomeLibrary_Version;

// HomeLibrary Version File

interface

// Don't Change: Machine generated text!
// VersionBlockBegin
const
  AIMPVersionID = 1000;
  AIMPVersionBuild = 0031;
  AIMPVersionBuildDate = 1052086101;
  AIMPVersionPrefix = 'Beta 1';
// VersionBlockEnd

function AIMPVersionDate: WideString;
function AIMPVersionFullString: WideString;
function AIMPVersionShortString: WideString;

implementation

uses
  SysUtils, AIMP_BaseSysUtils;

function AIMPVersionDate: WideString;
begin
  Result := FormatDateTime('(dd.MM.yyyy)', FileDateToDateTime(AIMPVersionBuildDate));
end;

function AIMPVersionShortString: WideString;
begin
  Result := WideFormat('v%d.%s%s', [
    AIMPVersionID div 1000, TrackFormat((AIMPVersionID mod 1000) div 10),
    IfThenW(AIMPVersionPrefix <> '', ' ' + AIMPVersionPrefix)]);
end;

function AIMPVersionFullString: WideString;
begin
  Result :=  AIMPVersionShortString + ', build ' + IntToStr(AIMPVersionBuild);
end;

end.
