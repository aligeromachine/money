object Form_date: TForm_date
  Left = 0
  Top = 0
  AutoSize = True
  BorderIcons = [biSystemMenu]
  Caption = #1055#1077#1088#1080#1086#1076' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1103' '#1087#1086#1082#1091#1087#1086#1082
  ClientHeight = 191
  ClientWidth = 255
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
  OnShortCut = FormShortCut
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroup1: TRadioGroup
    Left = 10
    Top = 10
    Width = 235
    Height = 171
    Caption = #1054#1090#1086#1073#1088#1072#1078#1072#1090#1100' '#1087#1086#1082#1091#1087#1082#1080' '#1089' '
    TabOrder = 0
    OnClick = RadioButton1Click
  end
  object RadioButton1: TRadioButton
    Left = 24
    Top = 34
    Width = 177
    Height = 17
    Margins.Left = 10
    Margins.Top = 10
    Margins.Right = 10
    Margins.Bottom = 10
    Caption = '1 '#1103#1085#1074#1072#1088#1103' '#1090#1077#1082#1091#1097#1077#1075#1086' '#1075#1086#1076#1072
    Checked = True
    TabOrder = 1
    TabStop = True
    OnClick = RadioButton1Click
  end
  object RadioButton2: TRadioButton
    Left = 24
    Top = 71
    Width = 177
    Height = 17
    Margins.Left = 10
    Margins.Top = 10
    Margins.Right = 10
    Margins.Bottom = 10
    Caption = '1 '#1095#1080#1089#1083#1072' '#1090#1077#1082#1091#1097#1077#1075#1086' '#1084#1077#1089#1103#1094#1072
    TabOrder = 2
    OnClick = RadioButton1Click
  end
  object RadioButton3: TRadioButton
    Left = 24
    Top = 108
    Width = 177
    Height = 17
    Margins.Left = 10
    Margins.Top = 10
    Margins.Right = 10
    Margins.Bottom = 10
    Caption = ' '#1087#1085' '#1090#1077#1082#1091#1097#1077#1081' '#1085#1077#1076#1077#1083#1080
    TabOrder = 3
    OnClick = RadioButton1Click
  end
  object RadioButton4: TRadioButton
    Left = 24
    Top = 145
    Width = 177
    Height = 17
    Margins.Left = 10
    Margins.Top = 10
    Margins.Right = 10
    Margins.Bottom = 10
    Caption = ' '#1079#1072' '#1074#1089#1077' '#1074#1088#1077#1084#1103
    TabOrder = 4
    OnClick = RadioButton1Click
  end
end
