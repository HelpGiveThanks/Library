July 21, 2018 12:56:02 Library.fmp12 - insertGenericNumberOrTimeReference -1-
tagMenu: insertGenericNumberOrTimeReference
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Figure out which template the user wants
#to insert.
If [ $$andTime ≠ "" ]
Set Variable [ $template; Value:"00:00:00" ]
Set Variable [ $$andTime ]
Else
Set Variable [ $template; Value:"pdf #, pp#" ]
End If
#
#Figure out if they are using it in their
#own words or in a quote.
Show Custom Dialog [ Message: "In your own words (" & $template & ") ?" & ¶ & "
OR" & ¶ & "
In a quote [" & $template & "] ?"; Default Button: “(own)”, Commit: “Yes”; Button 2: “[quote]”, Commit: “No”; Button 3: “cancel”,
Commit: “No” ]
If [ Get (LastMessageChoice) = 3 ]
Exit Script [ ]
End If
If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $template; Value:"[" & $template & "]" ]
End If
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $template; Value:"(" & $template & ")" ]
End If
#
#Select the Edit window.
Select Window [ Name: "Edit"; Current file ]
#
#Make sure the cursor is in active field and if
#not tell them to click in one.
If [ Get ( ActiveFieldName ) = "" ]
Show Custom Dialog [ Message: "Click into the text field, and then click exactly where you want — " & Trim ($template) & " —
inserted."; Default Button: “OK”, Commit: “Yes” ]
#
#
Else
#Insert template.
Insert Calculated Result [ $template ]
End If
#
#
