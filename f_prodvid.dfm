object Form_prodvid: TForm_prodvid
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = [biSystemMenu]
  Caption = #1044#1072#1073#1072#1074#1083#1077#1085#1080#1077' '#1090#1080#1087#1072' '#1087#1088#1086#1076#1091#1082#1090#1072
  ClientHeight = 128
  ClientWidth = 416
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Verdana'
  Font.Style = [fsItalic]
  Padding.Left = 10
  Padding.Top = 10
  Padding.Right = 10
  Padding.Bottom = 10
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShortCut = FormShortCut
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 10
    Top = 10
    Width = 396
    Height = 108
    Caption = #1044#1072#1085#1085#1099#1077' '#1090#1080#1087#1072' '#1087#1088#1086#1076#1091#1082#1090#1072
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsItalic]
    ParentBackground = False
    ParentColor = False
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 26
      Top = 32
      Width = 56
      Height = 13
      Caption = #1053#1072#1079#1074#1072#1085#1080#1077
    end
    object Edit_name: TEdit
      Left = 144
      Top = 29
      Width = 217
      Height = 21
      MaxLength = 35
      TabOrder = 0
      OnChange = Edit_nameChange
    end
    object Button1: TButton
      Left = 26
      Top = 67
      Width = 75
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 158
      Top = 67
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 2
      OnClick = FormShow
    end
    object Button3: TButton
      Left = 286
      Top = 67
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 3
      OnClick = Button3Click
    end
  end
end
