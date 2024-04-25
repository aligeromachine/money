object Form_gl: TForm_gl
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #1060#1080#1083#1100#1090#1088
  ClientHeight = 536
  ClientWidth = 710
  Color = 8744289
  Constraints.MaxHeight = 800
  Constraints.MaxWidth = 718
  Constraints.MinHeight = 570
  Constraints.MinWidth = 718
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Verdana'
  Font.Style = [fsItalic]
  Padding.Top = 5
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShortCut = FormShortCut
  OnShow = FormShow
  DesignSize = (
    710
    536)
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 15
    Top = 402
    Width = 680
    Height = 84
    Hint = #1048#1085#1090#1077#1088#1077#1089#1091#1102#1097#1080#1081' '#1087#1077#1088#1080#1086#1076
    Margins.Left = 15
    Margins.Top = 4
    Margins.Right = 15
    Anchors = [akLeft, akBottom]
    Caption = #1056#1072#1089#1095#1077#1090#1085#1099#1081' '#1087#1077#1088#1080#1086#1076', '#1072' '#1090#1072#1082#1078#1077' '#1074#1099#1073#1086#1088' '#1074#1089#1077#1093' '#1082#1088#1086#1084#1077' '#1074#1099#1076#1077#1083#1077#1085#1085#1099#1093
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 3
    object Label1: TLabel
      Left = 53
      Top = 14
      Width = 94
      Height = 13
      Caption = #1053#1072#1095#1072#1083#1100#1085#1072#1103' '#1076#1072#1090#1072
      WordWrap = True
    end
    object Label2: TLabel
      Left = 299
      Top = 14
      Width = 88
      Height = 13
      Caption = #1050#1086#1085#1077#1095#1085#1072#1103' '#1076#1072#1090#1072
      WordWrap = True
    end
    object Label8: TLabel
      Left = 514
      Top = 14
      Width = 131
      Height = 13
      Caption = #1057' '#1084#1086#1084#1077#1085#1090#1072' '#1079#1072#1088#1087#1083#1072#1090#1099' '#1074
      WordWrap = True
    end
    object DateTimePicker_n: TDateTimePicker
      Left = 16
      Top = 33
      Width = 168
      Height = 21
      Date = 41052.567958796290000000
      Time = 41052.567958796290000000
      DateFormat = dfLong
      TabOrder = 0
    end
    object ComboBox_mon: TComboBox
      Left = 496
      Top = 33
      Width = 168
      Height = 21
      Hint = #1057' '#1084#1086#1084#1077#1085#1090#1072' '#1079#1072#1088#1087#1083#1072#1090#1099' '#1074' '#1074#1099#1073#1088#1072#1085#1085#1086#1084' '#1084#1077#1089#1103#1094#1077' '#1087#1083#1102#1089' 30 '#1076#1085#1077#1081
      Style = csDropDownList
      DropDownCount = 12
      TabOrder = 2
      Items.Strings = (
        #1071#1085#1074#1072#1088#1100
        #1060#1077#1074#1088#1072#1083#1100
        #1052#1072#1088#1090
        #1040#1087#1088#1077#1083#1100
        #1052#1072#1081
        #1048#1102#1085#1100
        #1048#1102#1083#1100
        #1040#1074#1075#1091#1089#1090
        #1057#1077#1085#1090#1103#1073#1088#1100
        #1054#1082#1090#1103#1073#1088#1100
        #1053#1086#1103#1073#1088#1100
        #1044#1077#1082#1072#1073#1088#1100)
    end
    object DateTimePicker_k: TDateTimePicker
      Left = 256
      Top = 33
      Width = 168
      Height = 21
      Date = 41052.567958796290000000
      Time = 41052.567958796290000000
      DateFormat = dfLong
      TabOrder = 1
    end
    object not_org: TCheckBox
      Left = 31
      Top = 61
      Width = 125
      Height = 17
      Hint = #1042#1099#1073#1077#1088#1091#1090#1089#1103' '#1074#1089#1077' '#1082#1086#1084#1087#1072#1085#1080#1080' '#1082#1088#1086#1084#1077' '#1074#1099#1076#1077#1083#1077#1085#1085#1099#1093
      Caption = #1050#1086#1084#1087#1072#1085#1080#1081
      Color = clMaroon
      ParentColor = False
      TabOrder = 3
    end
    object not_prod_vid: TCheckBox
      Left = 271
      Top = 61
      Width = 125
      Height = 17
      Hint = #1042#1099#1073#1077#1088#1091#1090#1089#1103' '#1074#1089#1077' '#1090#1080#1087#1099' '#1087#1088#1086#1076#1091#1082#1090#1086#1074' '#1082#1088#1086#1084#1077' '#1074#1099#1076#1077#1083#1077#1085#1085#1099#1093
      Caption = #1058#1080#1087#1086#1074' '#1087#1088#1086#1076#1091#1082#1090#1086#1074
      Color = clMaroon
      ParentColor = False
      TabOrder = 4
    end
    object not_prod: TCheckBox
      Left = 521
      Top = 61
      Width = 125
      Height = 17
      Hint = #1042#1099#1073#1077#1088#1091#1090#1089#1103' '#1074#1089#1077' '#1090#1080#1087#1099' '#1087#1088#1086#1076#1091#1082#1090#1086#1074' '#1082#1088#1086#1084#1077' '#1074#1099#1076#1077#1083#1077#1085#1085#1099#1093
      Caption = #1055#1088#1086#1076#1091#1082#1090#1086#1074
      Color = clMaroon
      ParentColor = False
      TabOrder = 5
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 520
    Width = 710
    Height = 16
    Hint = #1069#1090#1086' '#1089#1090#1072#1090#1091#1089' '#1041#1072#1088
    Panels = <
      item
        Width = 500
      end>
  end
  object GroupBox5: TGroupBox
    Left = 15
    Top = 5
    Width = 200
    Height = 388
    Hint = 
      #1042#1099#1073#1077#1088#1080#1090#1077' '#1085#1091#1078#1085#1091#1102' '#1092#1080#1088#1084#1091', '#1077#1089#1083#1080' '#1074#1099#1073#1086#1088#1072' '#1085#1077#1090', '#1090#1086' '#1087#1086#1080#1089#1082' '#1080#1076#1077#1090' '#1087#1086' '#1074#1089#1077#1084' '#1087#1086 +
      #1083#1103#1084
    Margins.Left = 15
    Margins.Top = 5
    Margins.Right = 20
    Margins.Bottom = 5
    Anchors = [akLeft, akTop, akBottom]
    Caption = #1050#1086#1084#1087#1072#1085#1080#1080
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 0
    DesignSize = (
      200
      388)
    object CheckListBox_org: TCheckListBox
      Left = 16
      Top = 21
      Width = 168
      Height = 354
      OnClickCheck = CheckListBox_orgClickCheck
      Anchors = [akLeft, akTop, akRight, akBottom]
      ItemHeight = 13
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = CheckListBox_orgClick
      OnMouseLeave = CheckListBox_orgMouseLeave
    end
  end
  object GroupBox6: TGroupBox
    Left = 255
    Top = 5
    Width = 200
    Height = 388
    Hint = 
      #1042#1099#1073#1077#1088#1080#1090#1077' '#1090#1080#1087' '#1087#1088#1086#1076#1091#1082#1090#1072', '#1077#1089#1083#1080' '#1074#1099#1073#1086#1088#1072' '#1085#1077#1090', '#1090#1086' '#1087#1086#1080#1089#1082' '#1080#1076#1077#1090' '#1087#1086' '#1074#1089#1077#1084' '#1087#1086 +
      #1083#1103#1084
    Margins.Left = 20
    Margins.Top = 5
    Margins.Right = 20
    Margins.Bottom = 5
    Anchors = [akLeft, akTop, akBottom]
    Caption = #1058#1080#1087' '#1087#1088#1086#1076#1091#1082#1090#1072
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 1
    DesignSize = (
      200
      388)
    object CheckListBox_prodvid: TCheckListBox
      Left = 16
      Top = 21
      Width = 168
      Height = 354
      OnClickCheck = CheckListBox_prodvidClickCheck
      Anchors = [akLeft, akTop, akRight, akBottom]
      ItemHeight = 13
      TabOrder = 0
      OnClick = CheckListBox_prodvidClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 495
    Top = 5
    Width = 200
    Height = 388
    Hint = #1042#1099#1073#1077#1088#1080#1090#1077' '#1087#1088#1086#1076#1091#1082#1090', '#1077#1089#1083#1080' '#1074#1099#1073#1086#1088#1072' '#1085#1077#1090', '#1090#1086' '#1087#1086#1080#1089#1082' '#1080#1076#1077#1090' '#1087#1086' '#1074#1089#1077#1084' '#1087#1086#1083#1103#1084
    Margins.Left = 20
    Margins.Top = 5
    Margins.Right = 15
    Margins.Bottom = 5
    Anchors = [akLeft, akTop, akBottom]
    Caption = #1055#1088#1086#1076#1091#1082#1090
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 2
    DesignSize = (
      200
      388)
    object CheckListBox_prod: TCheckListBox
      Left = 16
      Top = 21
      Width = 168
      Height = 354
      OnClickCheck = CheckListBox_prodClickCheck
      Anchors = [akLeft, akTop, akRight, akBottom]
      HeaderBackgroundColor = clMenuBar
      ItemHeight = 13
      TabOrder = 0
      OnClick = CheckListBox_prodClick
    end
  end
  object Button1: TButton
    Left = 12
    Top = 491
    Width = 204
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1053#1072#1081#1090#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Verdana'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 5
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 254
    Top = 491
    Width = 202
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Verdana'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 6
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 493
    Top = 491
    Width = 204
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1042#1099#1093#1086#1076
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Verdana'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 7
    OnClick = Button3Click
  end
  object ApplicationEvents1: TApplicationEvents
    OnHint = ApplicationEvents1Hint
    Left = 464
    Top = 24
  end
end
