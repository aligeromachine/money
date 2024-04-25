object fr_visa: Tfr_visa
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = [biSystemMenu]
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1082#1072#1088#1090#1099
  ClientHeight = 214
  ClientWidth = 454
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
    Width = 434
    Height = 194
    Caption = #1044#1072#1085#1085#1099#1077' '#1082#1072#1088#1090#1099
    TabOrder = 0
    object Label5: TLabel
      Left = 33
      Top = 36
      Width = 125
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1082#1072#1088#1090#1099
    end
    object Label7: TLabel
      Left = 33
      Top = 77
      Width = 53
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #8470' '#1050#1072#1088#1090#1099
    end
    object Label8: TLabel
      Left = 33
      Top = 118
      Width = 38
      Height = 13
      Margins.Left = 14
      Margins.Top = 14
      Margins.Right = 14
      Margins.Bottom = 14
      Caption = #1057#1091#1084#1084#1072
    end
    object visa_n: TEdit
      Left = 181
      Top = 33
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      AutoSize = False
      MaxLength = 35
      TabOrder = 0
      OnChange = visa_nChange
    end
    object visa_nom: TEdit
      Left = 181
      Top = 74
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      AutoSize = False
      MaxLength = 35
      TabOrder = 1
      OnChange = visa_nChange
    end
    object visa_s: TEdit
      Left = 181
      Top = 115
      Width = 217
      Height = 21
      Margins.Left = 10
      Margins.Top = 10
      Margins.Right = 10
      Margins.Bottom = 10
      AutoSize = False
      MaxLength = 9
      TabOrder = 2
      OnChange = visa_nChange
      OnKeyPress = visa_nKeyPress
    end
    object Button1: TButton
      Left = 33
      Top = 156
      Width = 75
      Height = 25
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 178
      Top = 156
      Width = 80
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 4
      OnClick = FormShow
    end
    object Button3: TButton
      Left = 323
      Top = 156
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
      TabOrder = 5
      OnClick = Button3Click
    end
  end
end
