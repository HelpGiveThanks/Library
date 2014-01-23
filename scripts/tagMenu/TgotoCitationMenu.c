tagMenu: TgotoCitationMenu
If [ Get ( ActiveFieldContents ) = "" ]
Go to Field [ ]
Exit Script [ ]
End If
If [ $$add = 1 and Get ( ActiveFieldName ) = "kcitation" or $$add = 1 and Get ( ActiveFieldName ) = "kcReference" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Learn records with references or a citation cannot be added to tags. Doing so would require adding all these reference and cite records' references and cite records, and then all of theirs, and so on. "; Buttons: “OK” ]
Exit Script [ ]
End If
// If [ TEMP::ksection & "¶" ≠ FilterValues ( reference::kcsection ; TEMP::ksection & "¶" ) ]
// Go to Field [ ]
// Show Custom Dialog [ Message: "This reference belongs to the " & ruleRefLibraryName::name & " section." & " You can add pictures and links from any reference record to any tag, but you can only add tags to the current default section's records (name shown top left)."; Buttons: “OK” ]
// Exit Script [ ]
// End If
If [ $$ﬁndMode ≠ "" ]
Go to Field [ ]
Exit Script [ ]
End If
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#Conditionally format selected item and button on menu screen.
Set Variable [ $$citationItem; Value:Get (ActiveFieldContents) ]
Set Variable [ $$citationMatch; Value:Get (ActiveFieldName) ]
If [ $$citationMatch = "referenceShort" ]
Set Variable [ $$citationMatch; Value:"kcitation" ]
Set Variable [ $$citationItem; Value:refReference::_Lreference ]
End If
If [ Left (Get (ActiveFieldName); 4) = "kkey" or Get (ActiveFieldName) = "" ]
Set Variable [ $$citationMatch; Value:"key" ]
Else If [ Left (Get (ActiveFieldName); 5) = "knode" ]
Set Variable [ $$citationMatch; Value:"node" ]
End If
Refresh Window
#
#Exit ﬁeld so blinking cursor doesn't show up in empty ﬁeld.
Go to Field [ ]
Set Variable [ $window; Value:Get (WindowName) ]
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) / 2 ]
End If
#
#set citationMatch to color menu button with inUse color.
If [ $window = "Learn" ]
If [ $$citationMatch = "kfolderpath" ]
Go to Layout [ “learnMenu1” (tagMenus) ]
Perform Script [ “menuPath” ]
Else If [ $$citationMatch = "kmedium" ]
Set Variable [ $$medium; Value:reference::kmedium ]
Go to Layout [ “learnMenu1” (tagMenus) ]
Perform Script [ “menuMedium” ]
Else If [ $$citationMatch = "khealth" ]
Go to Layout [ “learnMenuHealth” (tagMenus) ]
Perform Script [ “menuHealth” ]
Else If [ $$citationMatch = "key" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
Perform Script [ “menuKey” ]
Else If [ $$citationMatch = "node" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
Perform Script [ “menuNode” ]
Else If [ $$citationMatch = "kcitation" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “learnMenu3Cite” (reference) ]
Perform Script [ “menuCitation” ]
#
#Go to citation record's current selection or to ﬁrst record.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ FilterValues ( $$citationItem ; reference::_Lreference ) = reference::_Lreference & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ FilterValues ( $$citationItem ; reference::_Lreference ) ≠ reference::_Lreference & ¶ ]
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
End If
Set Variable [ $$citationMatch; Value:"ref" ]
Refresh Window
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Select Window [ Name: "Learn"; Current ﬁle ]
Refresh Window
End If
#
#
#
#
Else If [ $window = "References" or $window = "Setup" ]
#
#If in add mode, prevent menu scripts from changing
#the main window's set of records.
#Unlike learn records, reference records or created
#for speciﬁc uses such as providing a picture
#or link for a speciﬁc set of tags, say keyword tags.
#So, in add mode, when clicking on a menu item
#the system ﬁnds all the records in the main
#reference window for that menu item. This
#is not helpful when the user is trying to create
#a new record to add to a tag. So this next script
#step stops the records shown, including and most
#importantly the record the user is working on
#from disappearing when the system ﬁnds only
#records assigned to that menu item. This then
#allows the user to add tags to the item neccessary
#to make it addable to the the tag menu item the
#user is creating it for!
If [ $$add = 1 ]
Set Variable [ $$add; Value:2 ]
End If
#
If [ $$citationMatch = "kfolderpath" ]
January 7, 平成26 16:20:05 Imagination Quality Management.fp7 - TgotoCitationMenu -1-tagMenu: TgotoCitationMenu
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
Perform Script [ “menuPath” ]
Else If [ $$citationMatch = "kmedium" ]
Set Variable [ $$medium; Value:reference::kmedium ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
Perform Script [ “menuMedium” ]
Else If [ $$citationMatch = "khealth" ]
Go to Layout [ “ReferenceMenuHealth” (tagMenus) ]
Perform Script [ “menuHealth” ]
Else If [ $$citationMatch = "korgan" ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
Perform Script [ “menuOrgan” ]
Else If [ $$citationMatch = "kcopyist" ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
Perform Script [ “menuCopyist” ]
Else If [ $$citationMatch = "key" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
Perform Script [ “menuKey” ]
Else If [ $$citationMatch = "node" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
Perform Script [ “menuNode” ]
Else If [ $$citationMatch = "kcitation" ]
Go to Layout [ “ReferenceMenu3Cite” (reference) ]
Perform Script [ “menuRefAddKeyWords” ]
End If
End If
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#If in add mode, allow menu scripts to once again
#change main window records.
If [ $$add = 2 ]
Set Variable [ $$add; Value:1 ]
End If
January 7, 平成26 16:20:05 Imagination Quality Management.fp7 - TgotoCitationMenu -2-
