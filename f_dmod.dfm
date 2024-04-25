object dmod1: Tdmod1
  OldCreateOrder = False
  Height = 424
  Width = 511
  object ADOConnection1: TADOConnection
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 32
    Top = 8
  end
  object ADOQ_Work: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 36
    Top = 200
  end
  object s_prihvid: TDataSource
    DataSet = q_prihvid
    Left = 367
    Top = 137
  end
  object ADOQ_see: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 110
    Top = 202
    object ADOQ_seenom: TIntegerField
      FieldKind = fkCalculated
      FieldName = 'nom'
      Calculated = True
    end
    object ADOQ_seename_org: TStringField
      DisplayWidth = 100
      FieldName = 'name_org'
      Size = 100
    end
    object ADOQ_seename_prod_vid: TStringField
      DisplayWidth = 100
      FieldName = 'name_prod_vid'
      Size = 100
    end
    object ADOQ_seename_prod: TStringField
      DisplayWidth = 100
      FieldName = 'name_prod'
      Size = 100
    end
    object ADOQ_seekol_ed_tr: TStringField
      Alignment = taCenter
      DisplayWidth = 100
      FieldName = 'kol_ed_tr'
      Size = 100
    end
    object ADOQ_seedata_tr: TDateTimeField
      FieldName = 'data_tr'
    end
    object ADOQ_seeprim_tr: TStringField
      DisplayWidth = 100
      FieldName = 'prim_tr'
      Size = 100
    end
    object ADOQ_seecena_tr: TIntegerField
      FieldName = 'cena_tr'
    end
  end
  object DS_it: TDataSource
    DataSet = ADOQ_see
    Left = 110
    Top = 264
  end
  object q_prod: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    OnCalcFields = q_prodCalcFields
    Parameters = <
      item
        Name = 'prod_vid'
        Attributes = [paNullable]
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'prod'
        Attributes = [paNullable]
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end>
    SQL.Strings = (
      'SELECT'
      'kod_prod_vid,name_prod_vid,'
      'kod_prod,name_prod'
      'FROM prod  '
      'inner JOIN prod_vid '
      'ON prod.kod_prod_vid_v = prod_vid.kod_prod_vid'
      'WHERE (name_prod_vid LIKE :prod_vid ) '
      'AND (name_prod LIKE :prod)'
      'ORDER BY name_prod_vid,name_prod')
    Left = 100
    Top = 75
    object q_prodkod_prod_vid: TIntegerField
      FieldName = 'kod_prod_vid'
    end
    object q_prodname_prod_vid: TStringField
      FieldName = 'name_prod_vid'
    end
    object q_prodkod_prod: TIntegerField
      FieldName = 'kod_prod'
      Visible = False
    end
    object q_prodname_prod: TStringField
      DisplayWidth = 100
      FieldName = 'name_prod'
      Size = 100
    end
    object q_prodnom_prod: TIntegerField
      FieldKind = fkCalculated
      FieldName = 'nom'
      Calculated = True
    end
  end
  object s_prod: TDataSource
    DataSet = q_prod
    Left = 100
    Top = 137
  end
  object q_trati: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'org'
        Size = -1
        Value = Null
      end
      item
        Name = 'prod_vid'
        Size = -1
        Value = Null
      end
      item
        Name = 'prod'
        Size = -1
        Value = Null
      end
      item
        Name = 'par1'
        Size = -1
        Value = Null
      end
      item
        Name = 'par2'
        Size = -1
        Value = Null
      end>
    SQL.Strings = (
      'SELECT'
      'kod_prod_vid,name_prod_vid,'
      'kod_prod,name_prod,'
      'kod_org,name_org,'
      'kod_pokup,kol_ed_tr,cena_tr,data_tr,prim_tr'
      'FROM prod_vid'
      'inner JOIN (prod'
      'inner JOIN (org'
      'inner JOIN trati'
      'ON org.kod_org = trati.kod_org_tr)'
      'ON prod.kod_prod = trati.kod_prod_tr)'
      'ON prod_vid.kod_prod_vid = prod.kod_prod_vid_v'
      'WHERE (name_org LIKE :org)'
      'AND (name_prod_vid LIKE :prod_vid)'
      'AND (name_prod LIKE :prod)'
      'AND (trati.data_tr Between :par1 And :par2)'
      'ORDER BY data_tr'
      'DESC,name_org,name_prod_vid,name_prod')
    Left = 252
    Top = 75
  end
  object s_trati: TDataSource
    DataSet = q_trati
    Left = 252
    Top = 137
  end
  object q_prih: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'name'
        Size = -1
        Value = Null
      end>
    SQL.Strings = (
      'SELECT'
      'kod_prih_vid,name_prih_vid,'
      'kod_prih,sum_prih,data_prih,prim_prih'
      'FROM prih '
      'inner JOIN prih_vid '
      'ON  prih.kod_prih_vid_v = prih_vid.kod_prih_vid'
      'WHERE name_prih_vid LIKE :name'
      'ORDER BY data_prih DESC;')
    Left = 305
    Top = 75
  end
  object s_prih: TDataSource
    DataSet = q_prih
    Left = 305
    Top = 137
  end
  object ADOQ_del: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 35
    Top = 250
  end
  object q: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 34
    Top = 299
  end
  object q_org: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    OnCalcFields = q_orgCalcFields
    Parameters = <
      item
        Name = 'name_org'
        Attributes = [paNullable]
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end>
    SQL.Strings = (
      'SELECT'
      'kod_org,name_org,adress_org'
      'FROM org'
      'WHERE (name_org like :name_org)'
      'ORDER BY name_org')
    Left = 38
    Top = 75
    object q_orgkod_org: TIntegerField
      Alignment = taCenter
      FieldName = 'kod_org'
    end
    object q_orgname_org: TStringField
      Alignment = taCenter
      FieldName = 'name_org'
      Size = 100
    end
    object q_orgadress_org: TStringField
      Alignment = taCenter
      FieldName = 'adress_org'
      Size = 100
    end
    object q_orgnom: TIntegerField
      Alignment = taCenter
      FieldKind = fkCalculated
      FieldName = 'nom'
      Calculated = True
    end
  end
  object q_prodvid: TADOQuery
    Connection = ADOConnection1
    CursorType = ctStatic
    OnCalcFields = q_prodvidCalcFields
    Parameters = <
      item
        Name = 'name_prod_vid'
        Attributes = [paNullable]
        DataType = ftWideString
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end>
    SQL.Strings = (
      'SELECT'
      'kod_prod_vid,name_prod_vid'
      'FROM prod_vid'
      'WHERE (name_prod_vid like :name_prod_vid)'
      'ORDER BY name_prod_vid')
    Left = 173
    Top = 75
    object q_prodvidkod_prod_vid: TIntegerField
      Alignment = taCenter
      FieldName = 'kod_prod_vid'
    end
    object q_prodvidname_prod_vid: TStringField
      Alignment = taCenter
      FieldName = 'name_prod_vid'
      Size = 100
    end
    object q_prodvidnom: TIntegerField
      Alignment = taCenter
      FieldKind = fkCalculated
      FieldName = 'nom'
      Calculated = True
    end
  end
  object s_org: TDataSource
    DataSet = q_org
    Left = 37
    Top = 137
  end
  object s_prodvid: TDataSource
    DataSet = q_prodvid
    Left = 173
    Top = 137
  end
  object ADOQ_en: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 173
    Top = 258
  end
  object ADOQ_inf: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 174
    Top = 315
  end
  object ADOQ_sea: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 174
    Top = 201
    object IntegerField1: TIntegerField
      FieldKind = fkCalculated
      FieldName = 'nom'
      Calculated = True
    end
    object StringField1: TStringField
      DisplayWidth = 100
      FieldName = 'name_org'
      Size = 100
    end
    object StringField2: TStringField
      DisplayWidth = 100
      FieldName = 'name_prod_vid'
      Size = 100
    end
    object StringField3: TStringField
      DisplayWidth = 100
      FieldName = 'name_prod'
      Size = 100
    end
    object StringField4: TStringField
      Alignment = taCenter
      DisplayWidth = 100
      FieldName = 'kol_ed_tr'
      Size = 100
    end
    object DateTimeField1: TDateTimeField
      FieldName = 'data_tr'
    end
    object StringField5: TStringField
      DisplayWidth = 100
      FieldName = 'prim_tr'
      Size = 100
    end
    object ADOQ_seacena_tr: TIntegerField
      FieldName = 'cena_tr'
    end
  end
  object q_prihvid: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    SQL.Strings = (
      'SELECT '
      'kod_prih_vid,name_prih_vid '
      'FROM prih_vid '
      'ORDER BY name_prih_vid;')
    Left = 368
    Top = 75
  end
  object q_visa: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    SQL.Strings = (
      'SELECT '
      'id_visa,visa_n,visa_nom,visa_s'
      'FROM visa'
      'ORDER BY visa_n;')
    Left = 439
    Top = 76
  end
  object s_visa: TDataSource
    DataSet = q_visa
    Left = 438
    Top = 137
  end
end
