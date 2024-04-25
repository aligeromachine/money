object Form_org: TForm_org
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1082#1086#1084#1087#1072#1085#1080#1080
  ClientHeight = 603
  ClientWidth = 416
  Color = clBtnFace
  Constraints.MaxWidth = 432
  Constraints.MinHeight = 400
  Constraints.MinWidth = 432
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
  DesignSize = (
    416
    603)
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 10
    Top = 10
    Width = 396
    Height = 583
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = #1044#1072#1085#1085#1099#1077' '#1082#1086#1084#1087#1072#1085#1080#1080
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
    DesignSize = (
      396
      583)
    object Label1: TLabel
      Left = 26
      Top = 32
      Width = 86
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077
    end
    object Label2: TLabel
      Left = 26
      Top = 73
      Width = 36
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1040#1076#1088#1077#1089
    end
    object Label3: TLabel
      Left = 26
      Top = 114
      Width = 99
      Height = 39
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Alignment = taCenter
      Caption = #1057#1074#1103#1079#1100' '#1082#1086#1084#1087#1072#1085#1080#1081' '#1089' '#1090#1080#1087#1086#1084' '#1087#1088#1086#1076#1091#1082#1090#1086#1074
      WordWrap = True
    end
    object Label4: TLabel
      Left = 44
      Top = 181
      Width = 57
      Height = 26
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Alignment = taCenter
      Caption = #1042#1099#1076#1077#1083#1080#1090#1100' '#1074#1089#1077
      Color = clGreen
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsItalic]
      ParentColor = False
      ParentFont = False
      WordWrap = True
    end
    object Label5: TLabel
      Left = 44
      Top = 253
      Width = 66
      Height = 26
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Alignment = taCenter
      Caption = #1057#1085#1103#1090#1100' '#1074#1099#1076#1077#1083#1077#1085#1080#1077
      Color = clGreen
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsItalic]
      ParentColor = False
      ParentFont = False
      WordWrap = True
    end
    object Edit_name: TEdit
      Left = 144
      Top = 29
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      MaxLength = 35
      TabOrder = 0
      OnChange = Edit_nameChange
    end
    object Edit_adress: TEdit
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
      OnChange = Edit_nameChange
    end
    object Button1: TButton
      Left = 26
      Top = 546
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 3
      OnClick = Button1Click
      ExplicitTop = 331
    end
    object Button2: TButton
      Left = 158
      Top = 546
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 4
      OnClick = FormShow
      ExplicitTop = 331
    end
    object Button3: TButton
      Left = 286
      Top = 546
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 5
      OnClick = Button3Click
      ExplicitTop = 331
    end
    object sv: TCheckListBox
      Left = 144
      Top = 111
      Width = 217
      Height = 422
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      OnClickCheck = svClickCheck
      Anchors = [akLeft, akTop, akBottom]
      ItemHeight = 13
      TabOrder = 2
      OnClick = svClick
    end
    object Button4: TButton
      Left = 37
      Top = 211
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = #1054#1050
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 6
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 37
      Top = 282
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 7
      OnClick = Button5Click
    end
  end
end
