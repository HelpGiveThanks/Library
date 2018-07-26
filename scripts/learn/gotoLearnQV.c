July 25, 2018 17:58:27 Library.fmp12 - gotoLearnQV -1-
learn: gotoLearnQV
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Currently in find mode. Click done in the tag menus window to exit find mode, and then click
this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Check if there are an references from the
#reference setion of the library (not learn
#references). And if there are then ask if the
#user would like to find them or go the QV
#interface for this record.
If [ TEMP::InventoryLibraryYN = "" ]
If [ ( testlearn::kcreference = ""
 or
ValueCount ( testlearn::kcreference ) - Length ( Filter ( testlearn::kcreference ; "L" ) ) = 0 )
= 0 ]
Show Custom Dialog [ Message: "Go to the QV interface for this record?"
& ¶ & " OR " & ¶ &
"Find all its references?"; Default Button: “go”, Commit: “Yes”; Button 2: “find”, Commit: “No”; Button 3: “cancel”, Commit:
“No” ]
If [ Get ( LastMessageChoice ) = 1 ]
#Continue with this script.
End If
If [ Get ( LastMessageChoice ) = 2 ]
#Find this record's references and display them
#in the Tag Menus window.
Perform Script [ “CHUNK_findLearnRecordsReferences” ]
Exit Script [ ]
End If
If [ Get ( LastMessageChoice ) = 3 ]
#Cancel.
Exit Script [ ]
End If
End If
End If
#
#Prevent the unnecessary loading of records.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#If in find mode, exit find mode.
If [ $$findMode= 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Go to Layout [ $$findLayout ]
Set Variable [ $$stoploadCitation ]
Select Window [ Name: "Learn"; Current file ]
End If
#
#Capture layout name.
Set Variable [ $$testLearnLayoutName; Value:Get (LayoutName) ]
#
#Capture note and timestamp. If these are
#changed while on the Qv layout it will effect
#the record's sort location and require a resort
#for the user to see the record they went to the
#QV window to look at.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$QvNote; Value:testlearn::note ]
Set Variable [ $$QvLocation; Value:testlearn::orderInventoryGroupNumber ]
Else
Set Variable [ $$QvTimestamp; Value:testlearn::timestamp ]
End If
#
#Go to edit layout for this record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
If [ tagTLNodePrimary::orderOrLock = "" ]
Go to Layout [ “learn4EDITstuff” (testlearn) ]
Else
Go to Layout [ “learn4EDITstuffLocked” (testlearn) ]
End If
Else
If [ tagTLNodePrimary::orderOrLock = "" ]
Go to Layout [ “learn4EDIT” (testlearn) ]
Else
Go to Layout [ “learn4EDITLocked” (testlearn) ]
End If
End If
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
Set Variable [ $$stoploadCitation ]
#
#
