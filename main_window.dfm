object MainWindow: TMainWindow
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1057#1080#1075#1085#1072#1090#1091#1088#1085#1099#1081' '#1087#1086#1080#1089#1082' '#1087#1086' '#1089#1077#1082#1090#1086#1088#1072#1084
  ClientHeight = 562
  ClientWidth = 466
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
  object lblClusterInfo: TLabel
    Left = 279
    Top = 531
    Width = 46
    Height = 13
    Caption = #1050#1083#1072#1089#1090#1077#1088':'
  end
  object lblFsType: TLabel
    Left = 25
    Top = 59
    Width = 36
    Height = 13
    Caption = #1058#1080#1087' '#1060#1057
  end
  object vstFindingSectors: TVirtualStringTree
    Left = 24
    Top = 128
    Width = 417
    Height = 385
    Header.AutoSizeIndex = -1
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    ScrollBarOptions.ScrollBars = ssVertical
    ScrollBarOptions.ScrollBarStyle = sbm3D
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
        Width = 247
        WideText = #1057#1080#1075#1085#1072#1090#1091#1088#1072
      end>
  end
  object tedName: TEdit
    Left = 136
    Top = 24
    Width = 54
    Height = 21
    TabOrder = 1
    Text = '\\.\J:'
  end
  object btnSearch: TButton
    Left = 25
    Top = 89
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 2
    OnClick = btnSearchClick
  end
  object btnStop: TButton
    Left = 115
    Top = 89
    Width = 75
    Height = 25
    Caption = #1057#1090#1086#1087
    TabOrder = 3
    OnClick = btnStopClick
  end
  object pbSearchingStatus: TProgressBar
    Left = 136
    Top = 530
    Width = 137
    Height = 13
    TabOrder = 4
  end
  object RadioGroup1: TRadioGroup
    Left = 196
    Top = 17
    Width = 245
    Height = 73
    Caption = #1052#1077#1090#1086#1076' '#1086#1073#1093#1086#1076#1072' '#1082#1083#1072#1089#1090#1077#1088#1086#1074
    TabOrder = 5
  end
  object radAll: TRadioButton
    Left = 207
    Top = 40
    Width = 90
    Height = 17
    Caption = #1042#1089#1077' '#1082#1083#1072#1089#1090#1077#1088#1072
    TabOrder = 6
  end
  object radRange: TRadioButton
    Left = 207
    Top = 63
    Width = 66
    Height = 17
    Caption = #1044#1080#1072#1087#1072#1079#1086#1085
    TabOrder = 7
  end
  object tedStartCluster: TEdit
    Left = 279
    Top = 63
    Width = 66
    Height = 21
    TabOrder = 8
    Text = '0'
  end
  object tedStopCluster: TEdit
    Left = 368
    Top = 63
    Width = 65
    Height = 21
    TabOrder = 9
    Text = '0'
  end
  object cbFsType: TComboBox
    Left = 80
    Top = 56
    Width = 110
    Height = 21
    TabOrder = 10
    Text = 'NTFS'
  end
end
