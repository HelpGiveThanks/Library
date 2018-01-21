January 20, 2018 19:10:31 Library.fmp12 - menuKeyFind -1-
tagMenu: menuFind: menuKeyFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"key" ]
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
#Find key tags for library section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Sort according to current users wishes.
If [ TEMP::sortKey = "cat" or TEMP::sortKey = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortKey = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
