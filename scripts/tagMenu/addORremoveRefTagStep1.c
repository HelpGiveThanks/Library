July 21, 2018 13:48:13 Library.fmp12 - addORremoveRefTagStep1 -1-
tagMenu: addORremoveRefTagStep1
#
#
#
#If this tag has a picture that is hidden, ask if
#the user wants to see the picture or find
#record's with this tag.
If [ //There is a picture to show if...
Get (LayoutName) = "learnMenu4noPicRefCite" and
(
testlearn::picture ≠ "" or
testlearn::kshowReferencedMedia ≠ ""
)
or
Get (LayoutName) = "learnMenu3CiteS" and
(
reference::picture ≠ "" or
reference::showMedia ≠ "" and reference::URL ≠ "" or
reference::showMedia[2] ≠ "" and reference::kfileLocation ≠ "" and reference::fileName ≠ ""
) ]
If [ testlearn::_Ltestlearn & "L" & ¶ = FilterValues ( $$ref & ¶ ; testlearn::_Ltestlearn & "L" & ¶ ) and $$citationMatch = "learn" or
reference::_Lreference & "¶" = FilterValues ( $$ref ; reference::_Lreference & "¶" ) and $$citationMatch = "ref" ]
Show Custom Dialog [ Message: "Show this tag's picture or remove tag from the selected learn record?"; Default Button:
“remove”, Commit: “Yes”; Button 2: “show”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Show this tag's picture or add this tag to the selected learn record?"; Default Button:
“add”, Commit: “Yes”; Button 2: “show”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
End If
If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $$stopOpenNewTextWindow ]
Perform Script [ “showCitationPicture1inNewWindow (udpate)” ]
Exit Script [ ]
End If
If [ Get (LastMessageChoice) = 3 ]
Exit Script [ ]
End If
End If
#
#
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
