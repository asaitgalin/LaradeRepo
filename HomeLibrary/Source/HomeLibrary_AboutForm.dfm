object AboutForm: TAboutForm
  Left = 440
  Top = 310
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 234
  ClientWidth = 390
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object sbOk: TMySkinButton
    Left = 148
    Top = 197
    Width = 121
    Height = 28
    SkinSource.SkinTheme = MainForm.stMain
    Caption = #1054#1050
    ModalResult = 1
  end
  object sgbInfo: TMySkinGroupBox
    Left = 8
    Top = 8
    Width = 373
    Height = 178
    SkinSource.SkinTheme = MainForm.stMain
    TabOrder = 0
    object slbName: TMySkinLabel
      Left = 8
      Top = 3
      Width = 113
      Height = 26
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = 'HomeLibrary'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
    end
    object slbAuthor: TMySkinLabel
      Left = 8
      Top = 72
      Width = 148
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = 'Author: Andrey Saitgalin'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
    end
    object slbVersion: TMySkinLabel
      Left = 8
      Top = 26
      Width = 253
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = 'ver'
    end
    object slbDate: TMySkinLabel
      Left = 8
      Top = 42
      Width = 75
      Height = 14
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = 'date'
    end
    object slbMail: TMySkinLabel
      Left = 54
      Top = 88
      Width = 142
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      URL = 'mailto:andrey.saitgalin@gmail.com'
      Caption = 'andrey.saitgalin@gmail.com'
    end
    object slbSupport: TMySkinLabel
      Left = 8
      Top = 88
      Width = 45
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = 'Support:'
    end
    object slbThirdParty: TMySkinLabel
      Left = 8
      Top = 114
      Width = 128
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = 'Third-party components:'
    end
    object sbbSQLite: TMySkinBBLabel
      Left = 8
      Top = 135
      Width = 286
      Height = 17
      SkinSource.SkinTheme = MainForm.stMain
      TabOrder = 0
      Text = 
        'SQLite DataBase Engine (D. Richard Hipp, [url="http://www.sqlite' +
        '.org"]www.sqlite.org[/url])'
    end
    object sbbSkinsLibrary: TMySkinBBLabel
      Left = 8
      Top = 151
      Width = 233
      Height = 16
      SkinSource.SkinTheme = MainForm.stMain
      TabOrder = 1
      Text = 
        'MySkins Library (Artem Izmaylov, [url="http://www.aimp.ru"]www.a' +
        'imp.ru[/url])'
    end
  end
end
