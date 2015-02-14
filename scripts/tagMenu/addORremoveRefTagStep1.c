tagMenu: addORremoveRefTagStep1
#Remove focus from field so can see
#conditional formatting.
Go to Field [ ]
#
#Determine if user is looking at cite or ref.
#NOTE: The cite idea is no longer being used. So,
#when here is time to properly test, these cite script
#steps need to be removed. END NOTE
If [ $$citationMatch = "cite" ]
Perform Script [ “addTagToMainRecord” ]
Else If [ $$citationMatch = "ref" ]
If [ Right ( Get (LayoutName) ; 7 ) = "RefCite" ]
#
#Check if tagging would cause record to reference itself.
If [ testlearn::_Ltestlearn = $$citation ]
Show Custom Dialog [ Message: "Records cannot reference themselves."; Buttons: “OK” ]
Select Window [ Name: "Tag Menus"; Current file ]
Halt Script
End If
#
#Complete process.
Perform Script [ “addORremoveCiteOrRefTLTag” ]
Select Window [ Name: "Learn"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
Perform Script [ “addORremoveCitationOrReferenceRefTag” ]
End If
February 24, 平成26 10:26:34 Imagination Quality Management.fp7 - addORremoveRefTagStep1 -1-
