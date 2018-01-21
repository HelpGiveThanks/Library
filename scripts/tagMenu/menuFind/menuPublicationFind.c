January 20, 2018 19:17:50 Library.fmp12 - menuPublicationFind -1-
tagMenu: menuFind: menuPublicationFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"publication" ]
#
#Goto correct layout.
Go to Layout [ “ReferenceMenuFind” (tagMenus) ]
#
#Find publication tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; "publication" ]
Perform Find [ ]
#
#Sort according to current users wishes.
If [ TEMP::sortPublication = "cat" or TEMP::sortPublication = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPublication = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
#
