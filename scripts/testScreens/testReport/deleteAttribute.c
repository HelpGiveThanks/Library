testScreens: testReport: deleteAttribute
Set Variable [ $row; Value:Get ( PortalRowNumber ) ]
Go to Field [ ]
Go to Portal Row [ $row ]
[ Select; No dialog ]
Set Variable [ $delete; Value:defaultCopyrightName::_Ltag ]
Set Variable [ $name; Value:defaultCopyrightName::tag ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete " & $name & "?"; Buttons: “Cancel”, “Delete” ]
If [ Get ( LastMessageChoice ) = 2 ]
Delete Portal Row
[ No dialog ]
End If
Set Variable [ $delete ]
Refresh Window
January 7, 平成26 14:34:56 Imagination Quality Management.fp7 - deleteAttribute -1-
