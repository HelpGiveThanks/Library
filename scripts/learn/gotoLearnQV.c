January 16, 2018 21:48:55 Library.fmp12 - gotoLearnQV -1-
learn: gotoLearnQV
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode, then click this button."; Default Button: “OK”, Commit: “No” ]
Exit Script [ ]
End If
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
#Go to edit layout for this record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learn4EDITstuff” (testlearn) ]
Else
Go to Layout [ “learn4EDIT” (testlearn) ]
End If
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
Set Variable [ $$stoploadCitation ]
