object fr_visav: Tfr_visav
  Left = 0
  Top = 0
  Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '#1076#1077#1085#1077#1078#1085#1099#1093' '#1082#1072#1088#1090#1086#1095#1077#1082' '
  ClientHeight = 396
  ClientWidth = 462
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 470
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Verdana'
  Font.Style = [fsItalic]
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  DesignSize = (
    462
    396)
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 462
    Height = 29
    Caption = 'ToolBar1'
    Images = Form_trativ.ImageList1
    TabOrder = 0
    object ToolButton2: TToolButton
      Left = 0
      Top = 0
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' (Insert)'
      Caption = 'ToolButton2'
      ImageIndex = 0
      ParentShowHint = False
      ShowHint = True
      OnClick = ToolButton2Click
    end
    object ToolButton3: TToolButton
      Left = 23
      Top = 0
      Width = 8
      Caption = 'ToolButton3'
      ImageIndex = 0
      Style = tbsSeparator
    end
    object ToolButton4: TToolButton
      Left = 31
      Top = 0
      Hint = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' (Enter)'
      Caption = 'ToolButton4'
      ImageIndex = 1
      ParentShowHint = False
      ShowHint = True
      OnClick = ToolButton4Click
    end
    object ToolButton5: TToolButton
      Left = 54
      Top = 0
      Hint = #1059#1076#1072#1083#1080#1090#1100' (Delete)'
      Caption = 'ToolButton5'
      ImageIndex = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = ToolButton5Click
    end
    object ToolButton6: TToolButton
      Left = 77
      Top = 0
      Width = 8
      Caption = 'ToolButton6'
      ImageIndex = 2
      Style = tbsSeparator
    end
    object ToolButton7: TToolButton
      Left = 85
      Top = 0
      Hint = #1042#1099#1093#1086#1076
      Caption = 'ToolButton7'
      ImageIndex = 3
      ParentShowHint = False
      ShowHint = True
      OnClick = ToolButton7Click
    end
    object ToolButton1: TToolButton
      Left = 108
      Top = 0
      Width = 8
      Caption = 'ToolButton1'
      ImageIndex = 66
      Style = tbsSeparator
    end
  end
  object GroupBox1: TGroupBox
    Left = 161
    Top = 2
    Width = 135
    Height = 31
    Margins.Top = 0
    Margins.Right = 5
    Margins.Bottom = 1
    Caption = ' '#1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1082#1072#1088#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    ParentBackground = False
    ParentFont = False
    TabOrder = 1
    object p1: TLabel
      Left = 50
      Top = 14
      Width = 40
      Height = 13
      Margins.Left = 20
      Margins.Right = 5
      Caption = #1089#1091#1084#1084#1072
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 12863772
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold, fsItalic]
      ParentColor = False
      ParentFont = False
    end
  end
  object GroupBox2: TGroupBox
    Left = 306
    Top = 2
    Width = 135
    Height = 31
    Margins.Left = 5
    Margins.Top = 0
    Margins.Right = 5
    Margins.Bottom = 1
    Caption = ' '#1057#1091#1084#1084#1072' '#1085#1072' '#1082#1072#1088#1090#1072#1093
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    ParentBackground = False
    ParentFont = False
    TabOrder = 2
    object p2: TLabel
      Left = 40
      Top = 14
      Width = 40
      Height = 13
      Margins.Left = 20
      Margins.Right = 5
      Caption = #1089#1091#1084#1084#1072
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 12863772
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold, fsItalic]
      ParentColor = False
      ParentFont = False
    end
  end
  object DBGrid1: TDBGrid
    Left = -1
    Top = 37
    Width = 464
    Height = 360
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = dmod1.s_visa
    DrawingStyle = gdsGradient
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgTitleHotTrack]
    ReadOnly = True
    TabOrder = 3
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Verdana'
    TitleFont.Style = [fsItalic]
    OnDrawColumnCell = DBGrid1DrawColumnCell
    OnDblClick = DBGrid1DblClick
    OnKeyDown = DBGrid1KeyDown
    Columns = <
      item
        Expanded = False
        FieldName = 'visa_n'
        Title.Alignment = taCenter
        Title.Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1082#1072#1088#1090#1086#1095#1082#1080
        Width = 200
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'visa_nom'
        Title.Alignment = taCenter
        Title.Caption = #8470' '#1050#1072#1088#1090#1086#1095#1082#1080
        Width = 125
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'visa_s'
        Title.Alignment = taCenter
        Title.Caption = #1057#1091#1084#1084#1072
        Width = 100
        Visible = True
      end>
  end
end
