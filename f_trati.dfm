object Form_trati: TForm_trati
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = [biSystemMenu]
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1087#1086#1082#1091#1087#1082#1080
  ClientHeight = 371
  ClientWidth = 443
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
    Width = 423
    Height = 351
    Caption = #1044#1072#1085#1085#1099#1077' '#1087#1086#1082#1091#1087#1082#1080
    TabOrder = 0
    object Label1: TLabel
      Left = 28
      Top = 114
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
      Top = 32
      Width = 32
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = ' '#1044#1072#1090#1072
    end
    object Label3: TLabel
      Left = 26
      Top = 278
      Width = 72
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
    end
    object Label4: TLabel
      Left = 26
      Top = 196
      Width = 30
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1062#1077#1085#1072
    end
    object Label5: TLabel
      Left = 28
      Top = 155
      Width = 49
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1055#1088#1086#1076#1091#1082#1090
    end
    object Label6: TLabel
      Left = 28
      Top = 73
      Width = 58
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1050#1086#1084#1087#1072#1085#1080#1103
    end
    object Label7: TLabel
      Left = 26
      Top = 237
      Width = 88
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086'/'#1045#1076
    end
    object Edit_prim: TEdit
      Left = 144
      Top = 275
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      AutoSize = False
      MaxLength = 35
      TabOrder = 6
      OnChange = Edit_cenaChange
    end
    object Button1: TButton
      Left = 26
      Top = 312
      Width = 75
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 7
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 161
      Top = 312
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 8
      OnClick = FormShow
    end
    object Button3: TButton
      Left = 286
      Top = 312
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 9
      OnClick = Button3Click
    end
    object n_prod_vid: TComboBox
      Left = 144
      Top = 111
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      Style = csDropDownList
      DropDownCount = 40
      TabOrder = 2
      OnChange = n_prod_vidChange
    end
    object Edit_cena: TEdit
      Left = 144
      Top = 193
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      MaxLength = 10
      TabOrder = 4
      OnChange = Edit_cenaChange
      OnKeyPress = Edit_cenaKeyPress
    end
    object n_prod: TComboBox
      Left = 144
      Top = 152
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      Style = csDropDownList
      DropDownCount = 30
      TabOrder = 3
      OnChange = n_prodChange
    end
    object n_org: TComboBox
      Left = 144
      Top = 70
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      Style = csDropDownList
      DropDownCount = 40
      TabOrder = 1
      OnChange = n_orgChange
    end
    object DateTimePicker_trati: TDateTimePicker
      Left = 144
      Top = 29
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      Date = 41051.000000000000000000
      Time = 41051.000000000000000000
      DateFormat = dfLong
      TabOrder = 0
      OnChange = Edit_cenaChange
    end
    object Edit_kol_ed: TEdit
      Left = 144
      Top = 234
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      MaxLength = 35
      TabOrder = 5
      OnChange = Edit_cenaChange
    end
    object BitBtn1: TBitBtn
      Left = 374
      Top = 70
      Width = 25
      Height = 21
      Hint = #1054#1090#1082#1088#1099#1090#1100' '#1086#1082#1085#1086' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103' '#1082#1086#1084#1087#1072#1085#1080#1080
      Caption = '+'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 10
      TabStop = False
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      Left = 374
      Top = 111
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
      TabOrder = 11
      TabStop = False
      OnClick = BitBtn2Click
    end
    object BitBtn3: TBitBtn
      Left = 374
      Top = 152
      Width = 25
      Height = 21
      Hint = #1054#1090#1082#1088#1099#1090#1100' '#1086#1082#1085#1086' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103' '#1087#1088#1086#1076#1091#1082#1090#1072
      Caption = '+'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 12
      TabStop = False
      OnClick = BitBtn3Click
    end
  end
end
