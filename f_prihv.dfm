object Form_prihv: TForm_prihv
  Left = 0
  Top = 0
  Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '#1087#1086#1083#1091#1095#1077#1082
  ClientHeight = 607
  ClientWidth = 516
  Color = clBtnFace
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
    516
    607)
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 516
    Height = 29
    Caption = 'ToolBar1'
    Images = Form_trativ.ImageList1
    TabOrder = 1
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
    object ToolButton1: TToolButton
      Left = 77
      Top = 0
      Width = 8
      Caption = 'ToolButton1'
      ImageIndex = 66
      Style = tbsSeparator
    end
    object ToolButton8: TToolButton
      Left = 85
      Top = 0
      Hint = #1054#1090#1095#1077#1090' Excel (F12)'
      Caption = 'ToolButton8'
      ImageIndex = 11
      ParentShowHint = False
      ShowHint = True
      OnClick = ToolButton8Click
    end
    object ToolButton6: TToolButton
      Left = 108
      Top = 0
      Width = 8
      Caption = 'ToolButton6'
      ImageIndex = 2
      Style = tbsSeparator
    end
    object Edit1: TEdit
      Left = 116
      Top = 0
      Width = 172
      Height = 22
      Hint = #1055#1086#1080#1089#1082' '#1087#1086' '#1085#1072#1079#1074#1072#1085#1080#1102' '#1090#1080#1087#1072
      Alignment = taCenter
      MaxLength = 15
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      TextHint = #1058#1080#1087' '#1087#1086#1083#1091#1095#1082#1080
      OnChange = Edit1Change
    end
    object ToolButton9: TToolButton
      Left = 288
      Top = 0
      Width = 8
      Caption = 'ToolButton9'
      ImageIndex = 4
      Style = tbsSeparator
    end
    object ToolButton11: TToolButton
      Left = 296
      Top = 0
      Hint = #1057#1091#1084#1084#1072' '#1085#1072' '#1082#1072#1088#1090#1086#1095#1082#1072#1093
      Caption = 'ToolButton11'
      ImageIndex = 13
      ParentShowHint = False
      ShowHint = True
      OnClick = ToolButton11Click
    end
    object ToolButton10: TToolButton
      Left = 319
      Top = 0
      Width = 8
      Caption = 'ToolButton10'
      ImageIndex = 4
      Style = tbsSeparator
    end
    object ToolButton7: TToolButton
      Left = 327
      Top = 0
      Hint = #1042#1099#1093#1086#1076
      Caption = 'ToolButton7'
      ImageIndex = 3
      ParentShowHint = False
      ShowHint = True
      OnClick = ToolButton7Click
    end
    object ToolButton12: TToolButton
      Left = 350
      Top = 0
      Width = 8
      Caption = 'ToolButton12'
      ImageIndex = 4
      Style = tbsSeparator
    end
  end
  object DBGrid1: TDBGrid
    Left = -2
    Top = 65
    Width = 519
    Height = 543
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = dmod1.s_prih
    DrawingStyle = gdsGradient
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleHotTrack]
    ReadOnly = True
    TabOrder = 0
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
        Alignment = taCenter
        Expanded = False
        FieldName = 'data_prih'
        Title.Alignment = taCenter
        Title.Caption = #1044#1072#1090#1072
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name_prih_vid'
        Title.Caption = '  '#1058#1080#1087' '#1087#1086#1083#1091#1095#1082#1080
        Width = 174
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'sum_prih'
        Title.Alignment = taCenter
        Title.Caption = #1057#1091#1084#1084#1072
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'prim_prih'
        Title.Alignment = taCenter
        Title.Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
        Width = 100
        Visible = True
      end>
  end
  object GroupBox1: TGroupBox
    Left = 6
    Top = 25
    Width = 135
    Height = 34
    Margins.Top = 0
    Margins.Right = 5
    Margins.Bottom = 1
    Caption = ' '#1044#1086#1093#1086#1076' '#1074#1077#1089#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    ParentBackground = False
    ParentFont = False
    TabOrder = 2
    object sum_p1: TLabel
      Left = 20
      Top = 16
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
    Left = 151
    Top = 25
    Width = 135
    Height = 34
    Margins.Left = 5
    Margins.Top = 0
    Margins.Right = 5
    Margins.Bottom = 1
    Caption = ' '#1044#1086#1093#1086#1076' '#1079#1072' '#1075#1086#1076
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    ParentBackground = False
    ParentFont = False
    TabOrder = 3
    object sum_p2: TLabel
      Left = 20
      Top = 16
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
  object GroupBox3: TGroupBox
    Left = 296
    Top = 25
    Width = 135
    Height = 34
    Margins.Left = 5
    Margins.Top = 0
    Margins.Right = 5
    Margins.Bottom = 1
    Caption = ' '#1044#1086#1093#1086#1076' '#1079#1072' '#1084#1077#1089#1103#1094
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    ParentBackground = False
    ParentFont = False
    TabOrder = 4
    object sum_p3: TLabel
      Left = 20
      Top = 16
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
end
