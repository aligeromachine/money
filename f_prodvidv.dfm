object Form_prodvidv: TForm_prodvidv
  Left = 0
  Top = 0
  Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '#1090#1080#1087#1086#1074' '#1087#1088#1086#1076#1091#1082#1090#1086#1074
  ClientHeight = 602
  ClientWidth = 475
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
    475
    602)
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 475
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
  object DBGrid1: TDBGrid
    Left = -1
    Top = 23
    Width = 477
    Height = 579
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = dmod1.s_prodvid
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
        Expanded = False
        FieldName = 'nom'
        Title.Alignment = taCenter
        Title.Caption = #8470
        Width = 40
        Visible = True
      end
      item
        Alignment = taLeftJustify
        Expanded = False
        FieldName = 'name_prod_vid'
        Title.Caption = '  '#1058#1080#1087' '#1087#1088#1086#1076#1091#1082#1090#1072
        Width = 400
        Visible = True
      end>
  end
  object Edit1: TEdit
    Left = 136
    Top = 1
    Width = 208
    Height = 21
    Hint = #1055#1086#1080#1089#1082' '#1080' '#1089#1086#1088#1090#1080#1088#1086#1074#1082#1072
    Alignment = taCenter
    MaxLength = 10
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    TextHint = #1058#1080#1087' '#1087#1088#1086#1076#1091#1082#1090#1072
    OnChange = Edit1Change
  end
end
