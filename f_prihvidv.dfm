object Form_prihvidv: TForm_prihvidv
  Left = 0
  Top = 0
  Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '#1090#1080#1087#1086#1074' '#1087#1086#1083#1091#1095#1077#1082
  ClientHeight = 231
  ClientWidth = 292
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
    292
    231)
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 292
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
  end
  object DBGrid1: TDBGrid
    Left = -1
    Top = 24
    Width = 294
    Height = 208
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = dmod1.s_prihvid
    DrawingStyle = gdsGradient
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleHotTrack]
    ReadOnly = True
    TabOrder = 1
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
        FieldName = 'name_prih_vid'
        Title.Alignment = taCenter
        Title.Caption = #1058#1080#1087' '#1087#1086#1083#1091#1095#1082#1080
        Width = 250
        Visible = True
      end>
  end
end
