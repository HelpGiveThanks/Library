January 15, 2018 17:15:32 Library.fmp12 - TgotoCitationMenu -1-
tagMenu: TgotoCitationMenu
#
// If [ Get ( ActiveFieldContents ) = "" ]
// Go to Field [ ]
// Exit Script [ ]
// End If
#
If [ $$findMode ≠ "" or $$stopTgotoCitationMenu = 1 ]
Go to Field [ ]
Set Variable [ $$stopTgotoCitationMenu ]
Exit Script [ ]
End If
#Admin tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#Conditionally format selected item and button on menu screen.
Set Variable [ $$citationItem; Value:Get (ActiveFieldContents) ]
Set Variable [ $$citationMatch; Value:Get (ActiveFieldName) ]
#
If [ Filter ( Get ( ActiveFieldTableName ) ; "refLearn" ) = "refLearn" ]
Set Variable [ $$citationMatch; Value:"ref" ]
Set Variable [ $learnRef; Value:refLearn::_Lreference ]
End If
#
If [ Left (Get (ActiveFieldName); 4) = "kkey" or Left (Get (ActiveFieldName); 5) = "kckey" or Get (ActiveFieldName) = "" ]
Set Variable [ $$citationMatch; Value:"key" ]
Set Variable [ $$citationItem; Value:tagTLKeywordPrimary::_Ltag ]
End If
#
If [ Left ( Get ( ActiveFieldName ) ; 5 ) = "knode" or
Filter ( Get (ActiveFieldTableName) ; "Node" ) = "Node" ]
Set Variable [ $$citationMatch; Value:"node" ]
Set Variable [ $$citationItem; Value:tagTLNodePrimary::_Ltag ]
End If
#
If [ Filter ( Get ( ActiveFieldName ) ; "node" ) = "node" ]
Set Variable [ $$citationMatch; Value:"node" ]
Set Variable [ $$citationItem; Value:reference::knodePrimary ]
End If
#
Refresh Window
#
#Exit field so blinking cursor doesn't show up in empty field.
Go to Field [ ]
Set Variable [ $window; Value:Get (WindowName) ]
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) /
2; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
End If
#
#
#
#
#
#LEARN WINDOW
If [ $window = "Learn" ]
#
If [ $$citationMatch = "kfolderpath" ]
Go to Layout [ “learnMenu1” (tagMenus) ]
Perform Script [ “menuPath” ]
#
Else If [ $$citationMatch = "kmedium" ]
Set Variable [ $$medium; Value:reference::kmedium ]
Go to Layout [ “learnMenu1” (tagMenus) ]
Perform Script [ “menuMedium” ]
#
Else If [ $$citationMatch = "khealth" ]
Go to Layout [ “learnMenuCopyright” (tagMenus) ]
Perform Script [ “menuCopyright” ]
#
Else If [ $$citationMatch = "key" ]
#KEY MENU
#
#See if user has selected requested menu.
If [ tagMenus::match ≠ "key" ]
#
#Menu NOT selected.
Perform Script [ “menuKey” ]
#
Else
#Menu IS selected.
#
#Record not selected and there is only a
#primary key, do this:
If [ $$primaryKey ≠ tagMenus::_Ltag or $$PrimaryKey ≠ "" ]
#
#Go to a layout with no pictures
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $reflayoutname; Value:Get (LayoutName) ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “ltagNK1” (tagMenus) ]
Else
Go to Layout [ “ltagNKs1” (tagMenus) ]
End If
#
#Make sure records are showing.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $$primaryKey ]
Extend Found Set [ ]
If [ $$otherKey ≠ "" ]
Set Variable [ $numberOfkeys; Value:1 ]
Loop
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; GetValue ( $$OtherKey ; $numberOfkeys ) ]
Extend Found Set [ ]
Set Variable [ $numberOfkeys; Value:$numberOfkeys + 1 ]
Exit Loop If [ $numberOfkeys = ValueCount ( $$OtherKey ) + 1 ]
End Loop
End If
#
#Loop thru records to find user's selection.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $$primaryKey = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Finish.
Go to Layout [ $reflayoutname ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
End If
End If
#
#
Else If [ $$citationMatch = "node" ]
#NODE MENU
#
#See if user has selected requested menu.
If [ tagMenus::match ≠ "node" ]
#
#Menu NOT selected.
Perform Script [ “menuNode” ]
#
Else
#Menu IS selected.
#
#Record not selected and there is only a
#primary node, do this:
If [ $$primaryNode ≠ tagMenus::_Ltag or $$Node ≠ "" ]
#
#Go to a layout with no pictures
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $reflayoutname; Value:Get (LayoutName) ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “ltagNK1” (tagMenus) ]
Else
Go to Layout [ “ltagNKs1” (tagMenus) ]
End If
#
#Make sure records are showing.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $$primaryNode ]
Extend Found Set [ ]
If [ $$Node ≠ "" ]
Set Variable [ $numberOfkeys; Value:1 ]
Loop
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; GetValue ( $$Node ; $numberOfkeys ) ]
Extend Found Set [ ]
Set Variable [ $numberOfkeys; Value:$numberOfkeys + 1 ]
Exit Loop If [ $numberOfkeys = ValueCount ( $$Node ) + 1 ]
End Loop
End If
#
#Loop thru records to find user's selection.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $$primaryNode = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Finish.
Go to Layout [ $reflayoutname ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
End If
End If
#
#
Else If [ $$citationMatch = "ref" ]
#REFERENCE MENU
#
#See if user has selected requested menu.
If [ Get (LayoutTableName) ≠ "reference" ]
#
#Menu NOT selected.
Perform Script [ “menuReference” ]
End If
#
#Menu IS selected.
#
#Record not selected, do this:
If [ $learnRef ≠ reference::_Lreference ]
#
#Go to a layout with no pictures
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $reflayoutname; Value:Get (LayoutName) ]
Go to Layout [ “learnMenu3CiteS” (reference) ]
#
#Make sure record is showing.
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $learnRef ]
Extend Found Set [ ]
#
#Loop thru records to find user's selection.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $learnRef = reference::_Lreference ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Finish.
Go to Layout [ $reflayoutname ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
End If
#
#
#
#
End If
#
#
#
#
#REFERENCE OR SETUP WINDOW
Else If [ $window = "References" or $window = "Setup" ]
#
#If in add mode, prevent menu scripts from changing
#the main window's set of records.
#Unlike learn records, reference records are created
#for specific uses such as providing a picture
#or link for a specific set of tags, say keyword tags.
#So, in add mode, when clicking on a menu item
#the system finds all the records in the main
#reference window for that menu item. This
#is not helpful when the user is trying to create
#a new record to add to a tag. So this next script
#step stops the records shown, including and most
#importantly the record the user is working on
#from disappearing when the system finds only
#records assigned to that menu item. This then
#allows the user to add tags to the item neccessary
#to make it addable to the the tag menu item the
#user is creating it for!
If [ $$add = 1 ]
Set Variable [ $$add; Value:2 ]
End If
#
#Set this variable to stop conditional formatting
#of unselected first Tag Menus record.
If [ $$citationitem = "" ]
Set Variable [ $$TgotoCitationMenuWithBlankField; Value:1 ]
Else
Set Variable [ $$TgotoCitationMenuWithBlankField ]
End If
#
If [ $$citationMatch = "kfolderpath" ]
Perform Script [ “menuPath” ]
Else If [ $$citationMatch = "kmedium" ]
Set Variable [ $$medium; Value:reference::kmedium ]
Perform Script [ “menuMedium” ]
Else If [ $$citationMatch = "kcopyright" ]
Perform Script [ “menuCopyright” ]
Else If [ $$citationMatch = "kpublication" ]
Perform Script [ “menuPublication” ]
Else If [ $$citationMatch = "kpublisher" ]
Perform Script [ “menuPublisher” ]
Else If [ $$citationMatch = "key" ]
Perform Script [ “menuKey” ]
Else If [ $$citationMatch = "node" ]
Perform Script [ “menuNode” ]
Else If [ $$citationMatch = "kcitation" ]
Perform Script [ “menuCitation” ]
End If
#
Select Window [ Name: "Tag Menus"; Current file ]
#
#If in add mode, allow menu scripts to once again
#change main window records.
If [ $$add = 2 ]
Set Variable [ $$add; Value:1 ]
End If
End If
#
