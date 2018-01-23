January 19, 2018 14:38:26 Library.fmp12 - addORremoveRefTagStep1 -1-
tagMenu: addORremoveRefTagStep1
#
#
#If main record node is currenlty locked then
#stop script and inform the user, unless the
#user altering the path tag, which is unique to
#the user's computer.
If [ $$citationMatch ≠ "path" ]
If [ $$lockedMainRefRecord ≠ "" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Show Custom Dialog [ Message: "Tags cannot be added or removed from locked reference records. Select this record's
creator node — " & $$lockedMainRefRecord & " — in the setup window and enter the password to unlock it."; Default
Button: “OK”, Commit: “No” ]
Halt Script
Else If [ $$lockedMainLearnRecord ≠ "" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Show Custom Dialog [ Message: "Tags cannot be added or removed from locked learn records. Select this record's creator
node — " & $$lockedMainLearnRecord & " — in the setup window and enter the password to unlock it."; Default Button:
“OK”, Commit: “No” ]
Halt Script
End If
End If
#
#
#Leave the field so the user can see
#conditional formatting.
Go to Field [ ]
#
#If user is looking at learn records do this.
If [ Right ( Get (LayoutName) ; 7 ) = "RefCite" ]
#
#Check if tagging would cause record to reference itself.
If [ testlearn::_Ltestlearn = $$main ]
Show Custom Dialog [ Message: "Records cannot reference themselves."; Default Button: “OK”, Commit: “No” ]
Select Window [ Name: "Tag Menus"; Current file ]
Halt Script
End If
#
#Complete process.
Perform Script [ “addORremoveRefTagStep2_forLearnRecord” ]
Select Window [ Name: "Learn"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
#If user is looking at reference records do this.
Perform Script [ “addORremoveRefTagStep2_forRefRecord” ]
#
