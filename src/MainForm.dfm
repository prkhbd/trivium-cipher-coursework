object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #171#1064#1080#1092#1088' Trivium'#187' - '#1089#1080#1084#1077#1090#1088#1080#1095#1085#1072' '#1082#1088#1080#1087#1090#1086#1075#1088#1072#1092#1110#1103
  ClientHeight = 720
  ClientWidth = 980
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  OnCreate = FormCreate
  TextHeight = 13
  object LabelLog: TLabel
    Left = 16
    Top = 472
    Width = 85
    Height = 13
    Caption = #1046#1091#1088#1085#1072#1083' '#1088#1086#1073#1086#1090#1080
  end
  object PanelHeader: TPanel
    Left = 16
    Top = 16
    Width = 948
    Height = 73
    BevelOuter = bvNone
    Color = 15987699
    ParentBackground = False
    TabOrder = 0
    object LabelTitle: TLabel
      Left = 16
      Top = 2
      Width = 507
      Height = 30
      Caption = #1055#1088#1080#1082#1083#1072#1076#1085#1080#1081' '#1079#1072#1089#1090#1086#1089#1091#1085#1086#1082' '#1089#1080#1084#1077#1090#1088#1080#1095#1085#1086#1111' '#1082#1088#1080#1087#1090#1086#1075#1088#1072#1092#1110#1111
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Segoe UI Semibold'
      Font.Style = []
      ParentFont = False
    end
    object LabelSubtitle: TLabel
      Left = 16
      Top = 46
      Width = 384
      Height = 13
      Caption = 
        #1050#1086#1076#1091#1074#1072#1085#1085#1103' '#1090#1072' '#1076#1077#1082#1086#1076#1091#1074#1072#1085#1085#1103' '#1092#1072#1081#1083#1110#1074' '#1085#1072' '#1086#1089#1085#1086#1074#1110' '#1087#1086#1090#1086#1082#1086#1074#1086#1075#1086' '#1096#1080#1092#1088#1091' Trivi' +
        'um.'
    end
  end
  object GroupBoxFiles: TGroupBox
    Left = 16
    Top = 104
    Width = 948
    Height = 126
    Caption = #1060#1072#1081#1083#1080
    TabOrder = 1
    object LabelInput: TLabel
      Left = 16
      Top = 28
      Width = 75
      Height = 13
      Caption = #1042#1093#1110#1076#1085#1080#1081' '#1092#1072#1081#1083':'
    end
    object LabelOutput: TLabel
      Left = 16
      Top = 60
      Width = 82
      Height = 13
      Caption = #1042#1080#1093#1110#1076#1085#1080#1081' '#1092#1072#1081#1083':'
    end
    object LabelKey: TLabel
      Left = 16
      Top = 92
      Width = 52
      Height = 13
      Caption = 'Key-'#1092#1072#1081#1083':'
    end
    object EditInputFile: TEdit
      Left = 128
      Top = 24
      Width = 708
      Height = 21
      TabOrder = 0
    end
    object ButtonBrowseInput: TButton
      Left = 848
      Top = 23
      Width = 81
      Height = 25
      Caption = #1054#1075#1083#1103#1076'...'
      TabOrder = 1
      OnClick = ButtonBrowseInputClick
    end
    object EditOutputFile: TEdit
      Left = 128
      Top = 56
      Width = 708
      Height = 21
      TabOrder = 2
    end
    object ButtonBrowseOutput: TButton
      Left = 848
      Top = 55
      Width = 81
      Height = 25
      Caption = #1054#1075#1083#1103#1076'...'
      TabOrder = 3
      OnClick = ButtonBrowseOutputClick
    end
    object EditKeyFile: TEdit
      Left = 128
      Top = 88
      Width = 708
      Height = 21
      TabOrder = 4
    end
    object ButtonBrowseKey: TButton
      Left = 848
      Top = 87
      Width = 81
      Height = 25
      Caption = #1054#1075#1083#1103#1076'...'
      TabOrder = 5
      OnClick = ButtonBrowseKeyClick
    end
  end
  object GroupBoxParams: TGroupBox
    Left = 16
    Top = 242
    Width = 948
    Height = 73
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1080' Trivium'
    TabOrder = 2
    object LabelIV: TLabel
      Left = 16
      Top = 32
      Width = 76
      Height = 13
      Caption = 'IV (80 '#1073#1110#1090', hex):'
    end
    object EditIV: TEdit
      Left = 128
      Top = 28
      Width = 516
      Height = 21
      TabOrder = 0
    end
    object ButtonGenerateIV: TButton
      Left = 656
      Top = 27
      Width = 105
      Height = 25
      Caption = #1047#1075#1077#1085#1077#1088#1091#1074#1072#1090#1080
      TabOrder = 1
      OnClick = ButtonGenerateIVClick
    end
    object CheckBoxAutoFillOutput: TCheckBox
      Left = 792
      Top = 31
      Width = 145
      Height = 17
      Caption = #1040#1074#1090#1086#1079#1072#1087#1086#1074#1085#1077#1085#1085#1103' '#1092#1072#1081#1083#1110#1074
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
  end
  object GroupBoxOps: TGroupBox
    Left = 16
    Top = 328
    Width = 948
    Height = 72
    Caption = #1054#1087#1077#1088#1072#1094#1110#1111
    TabOrder = 3
    object ButtonEncrypt: TButton
      Left = 16
      Top = 26
      Width = 160
      Height = 30
      Caption = #1047#1072#1096#1080#1092#1088#1091#1074#1072#1090#1080' '#1092#1072#1081#1083
      TabOrder = 0
      OnClick = ButtonEncryptClick
    end
    object ButtonDecrypt: TButton
      Left = 192
      Top = 26
      Width = 160
      Height = 30
      Caption = #1056#1086#1079#1096#1080#1092#1088#1091#1074#1072#1090#1080' '#1092#1072#1081#1083
      TabOrder = 1
      OnClick = ButtonDecryptClick
    end
    object ButtonGenerateKey: TButton
      Left = 368
      Top = 26
      Width = 170
      Height = 30
      Caption = #1057#1090#1074#1086#1088#1080#1090#1080' key-'#1092#1072#1081#1083
      TabOrder = 2
      OnClick = ButtonGenerateKeyClick
    end
    object ButtonClearLog: TButton
      Left = 554
      Top = 26
      Width = 140
      Height = 30
      Caption = #1054#1095#1080#1089#1090#1080#1090#1080' '#1083#1086#1075
      TabOrder = 3
      OnClick = ButtonClearLogClick
    end
  end
  object PanelNote: TPanel
    Left = 16
    Top = 412
    Width = 948
    Height = 49
    BevelOuter = bvNone
    Color = 15000804
    ParentBackground = False
    TabOrder = 4
    object LabelNote: TLabel
      Left = 12
      Top = 10
      Width = 917
      Height = 30
      AutoSize = False
      Caption = '_______________________________'
      WordWrap = True
    end
  end
  object MemoLog: TMemo
    Left = 16
    Top = 492
    Width = 948
    Height = 212
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 5
  end
  object OpenDialog1: TOpenDialog
    Left = 840
    Top = 16
  end
  object SaveDialog1: TSaveDialog
    Left = 880
    Top = 16
  end
end
