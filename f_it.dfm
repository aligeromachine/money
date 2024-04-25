object Form_it: TForm_it
  Left = 0
  Top = 0
  Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1080
  ClientHeight = 601
  ClientWidth = 897
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 905
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Verdana'
  Font.Style = [fsItalic]
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShortCut = FormShortCut
  OnShow = FormShow
  DesignSize = (
    897
    601)
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = -2
    Top = 40
    Width = 900
    Height = 562
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = dmod1.DS_it
    DrawingStyle = gdsGradient
    GradientEndColor = clSilver
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Verdana'
    TitleFont.Style = [fsItalic]
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'data_tr'
        Title.Alignment = taCenter
        Title.Caption = #1044#1072#1090#1072
        Title.Color = clMoneyGreen
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name_org'
        Title.Alignment = taCenter
        Title.Caption = #1050#1086#1084#1087#1072#1085#1080#1103
        Title.Color = clMoneyGreen
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name_prod_vid'
        Title.Alignment = taCenter
        Title.Caption = #1058#1080#1087' '#1087#1088#1086#1076#1091#1082#1090#1072
        Title.Color = clMoneyGreen
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name_prod'
        Title.Alignment = taCenter
        Title.Caption = #1055#1088#1086#1076#1091#1082#1090
        Title.Color = clMoneyGreen
        Width = 150
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'cena_tr'
        Title.Alignment = taCenter
        Title.Caption = #1062#1077#1085#1072
        Title.Color = clMoneyGreen
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'kol_ed_tr'
        Title.Alignment = taCenter
        Title.Caption = #1050#1086#1083'-'#1074#1086'/'#1045#1076
        Title.Color = clMoneyGreen
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'prim_tr'
        Title.Alignment = taCenter
        Title.Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
        Title.Color = clMoneyGreen
        Width = 105
        Visible = True
      end>
  end
  object GroupBox4: TGroupBox
    Left = 6
    Top = 1
    Width = 885
    Height = 35
    Hint = #1048#1090#1086#1075#1086#1074#1072#1103' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1103
    Margins.Left = 1
    Margins.Top = 0
    Margins.Right = 1
    Margins.Bottom = 1
    Anchors = [akLeft, akTop, akRight]
    Caption = #1048#1058#1054#1043#1048
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    ParentBackground = False
    ParentColor = False
    ParentFont = False
    TabOrder = 1
    object Label2: TLabel
      Left = 515
      Top = 15
      Width = 51
      Height = 13
      Caption = #1056#1072#1089#1093#1086#1076' :'
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsItalic]
      ParentColor = False
      ParentFont = False
    end
    object sum_tr: TLabel
      Left = 579
      Top = 13
      Width = 45
      Height = 16
      Margins.Left = 10
      Margins.Right = 100
      Caption = #1089#1091#1084#1084#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Verdana'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 702
      Top = 15
      Width = 93
      Height = 13
      Caption = #1059#1095#1090#1077#1085#1085#1099#1077' '#1044#1085#1080' :'
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsItalic]
      ParentColor = False
      ParentFont = False
    end
    object sum_day: TLabel
      Left = 808
      Top = 13
      Width = 45
      Height = 16
      Margins.Left = 10
      Margins.Right = 100
      Caption = #1089#1091#1084#1084#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Verdana'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
    end
    object ProgressBar1: TProgressBar
      Left = 50
      Top = 15
      Width = 439
      Height = 14
      TabOrder = 0
      Visible = False
    end
  end
  object MainMenu1: TMainMenu
    Images = Form_trativ.ImageList1
    Left = 640
    Top = 112
    object C1: TMenuItem
      Caption = 'C'#1086#1088#1090#1080#1088#1086#1074#1082#1072
      object N2: TMenuItem
        Caption = #1050#1086#1084#1087#1072#1085#1080#1080
        ImageIndex = 9
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #1058#1080#1087' '#1087#1088#1086#1076#1091#1082#1090#1072
        ImageIndex = 9
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = #1055#1088#1086#1076#1091#1082#1090
        ImageIndex = 9
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #1062#1077#1085#1072
        ImageIndex = 9
        OnClick = N5Click
      end
      object N6: TMenuItem
        Caption = #1044#1072#1090#1072
        ImageIndex = 9
        OnClick = N6Click
      end
    end
    object EXCEL3: TMenuItem
      Caption = #1054#1090#1095#1077#1090#1099' EXCEL'
      object EXCEL1: TMenuItem
        Caption = #1057#1090#1072#1090#1080#1089#1090#1080#1082#1072' '#1094#1077#1085
        ImageIndex = 12
        OnClick = EXCEL1Click
      end
      object EXCEL2: TMenuItem
        Caption = #1044#1080#1085#1072#1084#1080#1082#1072' '#1094#1077#1085
        ImageIndex = 11
        OnClick = EXCEL2Click
      end
    end
    object N7: TMenuItem
      Caption = #1050#1072#1083#1100#1082#1091#1083#1103#1090#1086#1088
      OnClick = N7Click
    end
    object N1: TMenuItem
      Caption = #1042#1099#1093#1086#1076
      ShortCut = 123
      OnClick = N1Click
    end
  end
end
