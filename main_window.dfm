object MainWindow: TMainWindow
  Left = 0
  Top = 0
  Caption = #1057#1080#1075#1085#1072#1090#1091#1088#1085#1099#1081' '#1087#1086#1080#1089#1082' '#1087#1086' '#1089#1077#1082#1090#1086#1088#1072#1084
  ClientHeight = 560
  ClientWidth = 465
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblPath: TLabel
    Left = 24
    Top = 27
    Width = 95
    Height = 13
    Caption = #1055#1091#1090#1100' '#1082' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1091
  end
  object lblStatusBar: TLabel
    Left = 24
    Top = 528
    Width = 57
    Height = 13
    Caption = 'lblStatusBar'
  end
  object vstFindingSectors: TVirtualStringTree
    Left = 24
    Top = 96
    Width = 417
    Height = 417
    Header.AutoSizeIndex = 0
    Header.MainColumn = -1
    TabOrder = 0
    Columns = <>
  end
  object tedName: TEdit
    Left = 136
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '\\.\C:'
  end
  object btnSearch: TButton
    Left = 24
    Top = 57
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 2
    OnClick = btnSearchClick
  end
  object checkSqlite: TCheckBox
    Left = 136
    Top = 57
    Width = 49
    Height = 25
    Caption = 'sqlite'
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
end
