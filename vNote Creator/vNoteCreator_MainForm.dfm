object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'vNote Creator v.1.0.1.15'
  ClientHeight = 296
  ClientWidth = 514
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object sbOpen: TMySkinButton
    Left = 377
    Top = 8
    Width = 129
    Height = 25
    SkinSource.SkinTheme = stMain
    Caption = #1054#1090#1082#1088#1099#1090#1100' txt'
    OnClick = sbOpenClick
  end
  object sbAbout: TMySkinButton
    Left = 377
    Top = 230
    Width = 129
    Height = 25
    SkinSource.SkinTheme = stMain
    Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
    OnClick = sbAboutClick
  end
  object sbSave: TMySkinButton
    Left = 377
    Top = 39
    Width = 129
    Height = 25
    SkinSource.SkinTheme = stMain
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' vnt'
    OnClick = sbSaveClick
  end
  object sbQuit: TMySkinButton
    Left = 377
    Top = 261
    Width = 129
    Height = 25
    SkinSource.SkinTheme = stMain
    Caption = #1042#1099#1093#1086#1076
    OnClick = sbQuitClick
  end
  object slbLUID: TMySkinLabel
    Left = 377
    Top = 139
    Width = 39
    Height = 15
    SkinSource.SkinTheme = stMain
    Transparent = True
    Caption = 'LUID:'
  end
  object sbClear: TMySkinButton
    Left = 377
    Top = 70
    Width = 129
    Height = 25
    SkinSource.SkinTheme = stMain
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    OnClick = sbClearClick
  end
  object sbSend: TMySkinButton
    Left = 377
    Top = 101
    Width = 129
    Height = 25
    SkinSource.SkinTheme = stMain
    Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100' '#1087#1086' BT'
    DropDownMenu = spDevices
    Style = sbsDropDown
  end
  object smText: TMySkinMemo
    Left = 8
    Top = 8
    Width = 363
    Height = 278
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    SkinSource.SkinTheme = stMain
  end
  object ssLUID: TMySkinSpin
    Left = 377
    Top = 160
    Width = 129
    Height = 17
    SkinSource.SkinTheme = stMain
    TabOrder = 1
    MaxValue = 1000
    Value = 27
    DesignSize = (
      129
      17)
  end
  object stMain: TMySkinTheme
    ContentColor = 14933984
    TabsBorderColor = clGray
    TabsContentColor = clWhite
    TabsHeaderColor = 14737632
    Left = 390
    Top = 190
  end
  object fdOpenSave: TMyFileDialog
    Title = #1042#1099#1073#1086#1088' txt '#1092#1072#1081#1083#1072
    Left = 425
    Top = 190
  end
  object spDevices: TMySkinPopup
    SkinSource.SkinTheme = stMain
    Left = 460
    Top = 190
  end
end
