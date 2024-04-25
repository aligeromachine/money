object Form_prod: TForm_prod
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = [biSystemMenu]
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1087#1088#1086#1076#1091#1082#1090#1072
  ClientHeight = 171
  ClientWidth = 434
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
    Width = 414
    Height = 151
    Caption = #1044#1072#1085#1085#1099#1077' '#1087#1088#1086#1076#1091#1082#1090#1072
    TabOrder = 0
    object Label1: TLabel
      Left = 26
      Top = 32
      Width = 80
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1058#1080#1087' '#1087#1088#1086#1076#1091#1082#1090#1072
    end
    object Label2: TLabel
      Left = 26
      Top = 73
      Width = 86
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
    end
    object Edit_name: TEdit
      Left = 144
      Top = 70
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      MaxLength = 35
      TabOrder = 1
      OnChange = n_prodvidChange
    end
    object Button1: TButton
      Left = 26
      Top = 114
      Width = 75
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 158
      Top = 114
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 3
      OnClick = FormShow
    end
    object Button3: TButton
      Left = 286
      Top = 114
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 4
      OnClick = Button3Click
    end
    object n_prodvid: TComboBox
      Left = 144
      Top = 29
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      Style = csDropDownList
      DropDownCount = 40
      TabOrder = 0
      OnChange = n_prodvidChange
    end
    object BitBtn1: TBitBtn
      Left = 374
      Top = 29
      Width = 25
      Height = 21
      Hint = #1054#1090#1082#1088#1099#1090#1100' '#1086#1082#1085#1086' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103' '#1090#1080#1087#1072' '#1087#1088#1086#1076#1091#1082#1090#1072
      Caption = '+'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      TabStop = False
      OnClick = BitBtn1Click
    end
  end
end
