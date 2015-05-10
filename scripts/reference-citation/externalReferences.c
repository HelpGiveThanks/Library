reference(citation): externalReferences
#
#
#
#Use this bit of code to make the default reference
#point to the internal (Learn) records instead of
#the external references. Other scripts with code
#that needs to be turned on: menuReference,
// #If library is for inventory then go to container menu.
// If [ TEMP::InventoryLibaryYN ≠ "" ]
// Perform Script [ “menuReference” ]
// Exit Script [ ]
// End If
#
#If current mode is citation then use cite menu scirpt.
If [ $$citationMatch = "cite" ]
Perform Script [ “menuRefAddKeyWords” ]
Exit Script [ ]
End If
#
If [ $$findmode ≠ 1 ]
#Set testlearn internal reference field conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#Show all internal reference possibilities.
#
If [ TEMP::InventoryLibaryYN ≠ "" ]
Go to Layout [ “learnMenuRefStuff” (reference) ]
Else
Go to Layout [ “learnMenu3Cite” (reference) ]
End If
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ FilterValues ( $$ref ; reference::_Lreference ) = reference::_Lreference & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ FilterValues ( $$ref ; reference::_Lreference ) ≠ reference::_Lreference & ¶ ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
End If
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#Update conditional formatting in main window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Else If [ $$findmode = 1 ]
#Set testlearn internal reference field conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#Show all internal reference possibilities.
Go to Layout [ “learnFindCite” (reference) ]
End If
May 10, 平成27 12:08:24 Library.fp7 - externalReferences -1-
