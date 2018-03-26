object MainWindow: TMainWindow
  Left = 0
  Top = 0
  Caption = #1057#1080#1075#1085#1072#1090#1091#1088#1085#1099#1081' '#1087#1086#1080#1089#1082' '#1087#1086' '#1089#1077#1082#1090#1086#1088#1072#1084
  ClientHeight = 552
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
    Top = 530
    Width = 57
    Height = 13
    Caption = 'lblStatusBar'
  end
  object lblCurrentClusterNumber: TLabel
    Left = 381
    Top = 531
    Width = 6
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
  end
  object lblTotalClustersCount: TLabel
    Left = 403
    Top = 531
    Width = 6
    Height = 13
    Caption = '0'
  end
  object lblSlash: TLabel
    Left = 393
    Top = 531
    Width = 4
    Height = 13
    Caption = '/'
  end
  object vstFindingSectors: TVirtualStringTree
    Left = 24
    Top = 96
    Width = 417
    Height = 417
    Header.AutoSizeIndex = -1
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowTreeLines, toShowVertGridLines, toThemeAware, toUseBlendedImages, toFullVertGridLines]
    TreeOptions.SelectionOptions = [toFullRowSelect]
    OnGetText = vstFindingSectorsGetText
    Columns = <
      item
        Position = 0
        Width = 170
        WideText = #1053#1086#1084#1077#1088' '#1050#1083#1072#1089#1090#1077#1088#1072
      end
      item
        Position = 1
        Width = 240
        WideText = #1057#1080#1075#1085#1072#1090#1091#1088#1072
      end>
  end
  object tedName: TEdit
    Left = 136
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '\\.\J:'
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
    Left = 288
    Top = 22
    Width = 49
    Height = 25
    Caption = 'sqlite'
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
  object btnStop: TButton
    Left = 366
    Top = 57
    Width = 75
    Height = 25
    Caption = #1057#1090#1086#1087
    TabOrder = 4
  end
  object pbSearchingStatus: TProgressBar
    Left = 144
    Top = 519
    Width = 137
    Height = 24
    TabOrder = 5
  end
end
