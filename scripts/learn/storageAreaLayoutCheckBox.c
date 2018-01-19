January 17, 2018 11:35:37 Library.fmp12 - holderCheckBox -1-
learn: holderCheckBox
#
#Prevent user from tagging holder records
#with other holder tags. I.E., No holder
#inside of holder relationships allowed.
If [ TEMP::InventoryLibraryYN = "" ]
Exit Script [ ]
End If
#
If [ Filter (testlearn::kcreference ; "L") ≠ "" ]
Set Field [ testlearn::brainstormCasePoint; "" ]
Show Custom Dialog [ Message: "This item is in/on a holder (box, shelf, etc.). To make it a location tag, 1) click 'tag', 2) click 'it's
here', 3) click 'holder', and 4) remove it from its current holder."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
