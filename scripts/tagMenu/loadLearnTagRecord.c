July 21, 2018 14:14:57 Library.fmp12 - loadLearnTagRecord -1-
tagMenu: loadLearnTagRecord
#
#NOTE: this script is used on the Tag Menus window
#for Learn records to exit field when a record is
#is first entered, which is a real problem on the
#iPhone as the text edit box opens when the user
#may have clicked only to select the record rather
#than edit it.
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Clear these variables and then load them.
Set Variable [ $$refIDForMainLearnRecord ]
Set Variable [ $$learnIDForMainLearnRecord; Value:reference::_Lreference ]
Set Variable [ $$learnIDForMainLearnRecord; Value:testlearn::_Ltestlearn ]
#
If [ TEMP::layoutLmain = "lesslearn4"
or
TEMP::layoutLmain = "morelearn4"
or
$$testLearnLayoutName ≠ "" ]
Select Window [ Name: "Learn"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#
Go to Field [ ]
Go to Field [ ]
#
#
