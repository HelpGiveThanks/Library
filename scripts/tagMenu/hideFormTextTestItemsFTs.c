January 15, 2018 17:05:34 Library.fmp12 - hideFormTextTestItemsFTs -1-
tagMenu: hideFormTextTestItemsFTs
#
#Prevent test item variables being loaded as this
#script moves thru them.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#
#
#If the hideFT preference was to hide them,
#then switch the preference to show them.
If [ TEMP::testHideFormTextItemsFTs = 1 ]
Set Field [ TEMP::testHideFormTextItemsFTs; "" ]
#
#If this list has FT items, then find them.
If [ $$noFT_ItemsFound = "" ]
#
#Find test items for section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenuTestItemGroup::match; TEMP::ktestItemSubsection & ¶ ]
Perform Find [ ]
#
#To insure the 'sort' button will next sort
#alphabetically, note that the current sort is
#by category/group.
Set Field [ TEMP::sortTestItem; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuTestItemGroup::name; ascending
tagMenuTestItemGroup::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Scroll Window
[ Home ]
#
#
#If this list has no FT items, then inform user.
Else
Show Custom Dialog [ Message: "Your preference to now show FT items (if there are any to show) has been saved. This
list has no FT items to show."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#
#If the hideFT preference was to show them,
#then switch the preference to hide them.
Else
Set Field [ TEMP::testHideFormTextItemsFTs; 1 ]
#
#Now go to each test item and omit
#the FT items.
Go to Record/Request/Page
[ First ]
Loop
Go to Field [ ]
If [ tagMenus::notesOrCopyright = "FT" ]
Omit Record
Else
Go to Record/Request/Page
[ Next; Exit after last ]
End If
End Loop
End If
#
#Now go the first record and scroll
#the window to the top.
Go to Record/Request/Page
[ First ]
Set Variable [ $$stopLoadTagRecord ]
Scroll Window
[ Home ]
#
#Load this records variables.
Perform Script [ “loadTagRecord (update)” ]
#
#
