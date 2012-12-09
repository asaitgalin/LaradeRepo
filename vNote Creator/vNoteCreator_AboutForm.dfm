object AboutForm: TAboutForm
  Left = 480
  Top = 431
  BorderStyle = bsDialog
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 206
  ClientWidth = 362
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
  object sbClose: TMySkinButton
    Left = 128
    Top = 172
    Width = 121
    Height = 25
    SkinSource.SkinTheme = MainForm.stMain
    Caption = 'OK'
    ModalResult = 1
  end
  object sgbInfo: TMySkinGroupBox
    Left = 8
    Top = 8
    Width = 343
    Height = 153
    SkinSource.SkinTheme = MainForm.stMain
    TabOrder = 0
    object slbName: TMySkinLabel
      Left = 10
      Top = 10
      Width = 116
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = 'vNote Creator'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
    end
    object slbVersion: TMySkinLabel
      Left = 10
      Top = 25
      Width = 96
      Height = 21
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = #1042#1077#1088#1089#1080#1103': 1.0.1.15'
    end
    object slbAuthor: TMySkinLabel
      Left = 10
      Top = 60
      Width = 156
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = #1040#1074#1090#1086#1088': '#1040#1085#1076#1088#1077#1081' '#1057#1072#1080#1090#1075#1072#1083#1080#1085
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
    end
    object slbMail: TMySkinLabel
      Left = 10
      Top = 75
      Width = 176
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = #1055#1086#1095#1090#1072': andrey.saitgalin@gmail.com'
    end
    object slbUses: TMySkinLabel
      Left = 10
      Top = 105
      Width = 151
      Height = 15
      SkinSource.SkinTheme = MainForm.stMain
      Transparent = True
      Caption = #1069#1090#1072' '#1087#1088#1086#1075#1088#1072#1084#1084#1072' '#1080#1089#1087#1086#1083#1100#1079#1091#1077#1090':'
    end
    object slbControls: TMySkinBBLabel
      Left = 10
      Top = 121
      Width = 245
      Height = 16
      SkinSource.SkinTheme = MainForm.stMain
      TabOrder = 0
      Text = 
        'MySkins Library (Artem Izmaylov, [url="http://www.aimp.ru"]www.a' +
        'imp.ru[/url])'
    end
  end
end
