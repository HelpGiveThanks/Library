July 21, 2018 14:44:41 Library.fmp12 - menuNodeFind -1-
tagMenu: menuFind: menuNodeFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"node" ]
#
#Do not load tag records until the end of script
#to prevent flashing of window and to speed up
#script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnKeywordOrNodeFind” (tagMenus) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnKeywordOrNodeSFind” (tagMenus) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNodeFind” (tagMenus) ]
End If
#
#Find node tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
#
#In Learn section only show creator nodes,
#as these are the only nodes that can create
#or edit learn records.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; 123456789 ]
End If
#
Perform Find [ ]
#
#Sort according to current users wishes.
If [ TEMP::sortNode = "cat" or TEMP::sortNode = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortNode = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
