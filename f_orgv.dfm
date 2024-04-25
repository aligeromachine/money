object Form_orgv: TForm_orgv
  Left = 0
  Top = 0
  Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '#1082#1086#1084#1087#1072#1085#1080#1081
  ClientHeight = 603
  ClientWidth = 626
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
    626
    603)
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 626
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
    Top = 24
    Width = 628
    Height = 580
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = dmod1.s_org
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
        PickList.Strings = (
          '9')
        ReadOnly = False
        Title.Alignment = taCenter
        Title.Caption = #8470
        Title.Color = clSkyBlue
        Width = 40
        Visible = True
      end
      item
        Alignment = taLeftJustify
        Expanded = False
        FieldName = 'name_org'
        Title.Caption = '  '#1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
        Title.Color = clSkyBlue
        Width = 300
        Visible = True
      end
      item
        Alignment = taLeftJustify
        Expanded = False
        FieldName = 'adress_org'
        Title.Caption = '  '#1040#1076#1088#1077#1089
        Title.Color = clSkyBlue
        Width = 250
        Visible = True
      end>
  end
  object Edit1: TEdit
    Left = 126
    Top = 1
    Width = 211
    Height = 21
    Hint = #1055#1086#1080#1089#1082' '#1080' '#1089#1086#1088#1090#1080#1088#1086#1074#1082#1072
    Alignment = taCenter
    MaxLength = 10
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    TextHint = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
    OnChange = Edit1Change
  end
end
