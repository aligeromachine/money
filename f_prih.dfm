object Form_prih: TForm_prih
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = [biSystemMenu]
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1087#1086#1083#1091#1095#1082#1080
  ClientHeight = 287
  ClientWidth = 458
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
    Width = 438
    Height = 267
    Caption = #1044#1072#1085#1085#1099#1077' '#1087#1086#1083#1091#1095#1082#1080
    TabOrder = 0
    object Label1: TLabel
      Left = 26
      Top = 73
      Width = 74
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1058#1080#1087' '#1087#1086#1083#1091#1095#1082#1080
    end
    object Label3: TLabel
      Left = 26
      Top = 32
      Width = 28
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1044#1072#1090#1072
    end
    object Label4: TLabel
      Left = 26
      Top = 196
      Width = 72
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
    end
    object Label6: TLabel
      Left = 26
      Top = 114
      Width = 38
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1057#1091#1084#1084#1072
    end
    object Label2: TLabel
      Left = 26
      Top = 155
      Width = 110
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1085#1072' '#1082#1072#1088#1090#1091
    end
    object Edit_sum: TEdit
      Left = 166
      Top = 111
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      MaxLength = 9
      TabOrder = 2
      OnChange = n_prihvidChange
      OnKeyPress = Edit_sumKeyPress
    end
    object Button1: TButton
      Left = 26
      Top = 232
      Width = 75
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 5
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 166
      Top = 232
      Width = 80
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 6
      OnClick = FormShow
    end
    object Button3: TButton
      Left = 308
      Top = 232
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 7
      OnClick = Button3Click
    end
    object n_prihvid: TComboBox
      Left = 166
      Top = 70
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      Style = csDropDownList
      DropDownCount = 20
      TabOrder = 1
      OnChange = n_prihvidChange
    end
    object Edit_prim: TEdit
      Left = 166
      Top = 193
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      AutoSize = False
      MaxLength = 35
      TabOrder = 4
      OnChange = n_prihvidChange
    end
    object DateTimePicker_prih: TDateTimePicker
      Left = 166
      Top = 27
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
      OnChange = n_prihvidChange
    end
    object BitBtn1: TBitBtn
      Left = 396
      Top = 70
      Width = 25
      Height = 21
      Hint = #1054#1090#1082#1088#1099#1090#1100' '#1086#1082#1085#1086' '#1076#1086#1073#1072#1074#1083#1077#1085#1080#1103' '#1090#1080#1087#1072' '#1087#1086#1083#1091#1095#1082#1080
      Caption = '+'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
      TabStop = False
      OnClick = BitBtn1Click
    end
    object visa: TComboBox
      Left = 166
      Top = 152
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      Style = csDropDownList
      DropDownCount = 20
      TabOrder = 3
      OnChange = n_prihvidChange
    end
  end
end
