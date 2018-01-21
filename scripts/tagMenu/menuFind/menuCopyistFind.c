January 20, 2018 19:16:27 Library.fmp12 - menuPublisherFind -1-
tagMenu: menuFind: menuPublisherFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"publisher" ]
#
#Goto correct layout.
Go to Layout [ “ReferenceMenuFind” (tagMenus) ]
#
#Find publisher tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Sort according to current users wishes.
If [ TEMP::sortPublisher = "cat" or TEMP::sortPublisher = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPublisher = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
