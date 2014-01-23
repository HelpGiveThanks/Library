tagMenu: menuCopyist
#
#If user is in tag ﬁeld and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"copyist" ]
#
#Set match temp tag ﬁeld to limit move pulldown
#to just the groups for this section and item type.
#( if you're wondering why this temp ﬁeld is a
# a dupllicate of the citation match variable it
# is because I didn't need it until a year into
# writing this database. At some point, it would
# probably be good to get rid of the variable. )
Set Field [ TEMP::mTag; $$citationMatch ]
#
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenu1” (tagMenus) ]
#
#If not in add mode ...
Else If [ $$add ≠ 1 ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
End If
#
#Find copyist tags. Copyist tags are available to all library sections.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
// #If no records exist then create one.
// If [ Get (FoundCount)=0 ]
// Perform Script [ “newCitationMenuGroup” ]
// End If
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortCopyist = "cat" or TEMP::sortCopyist = "" ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortCopyist = "abc" ]
Sort Records [ Speciﬁed Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Go to citation record's current selection or to ﬁrst record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$copyist = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$copyist ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
// Exit Script [ ]
End If
#
#Inform user of items use on both screens.
Set Variable [ $$citationItem; Value:tagMenus::_Ltag ]
Refresh Window
Select Window [ Name: "References"; Current ﬁle ]
#
#If in add mode, ﬁnd only records tagged with
#current $$citationmatch on reference layout.
#The learn record is never changed.
If [ Left (Get (LayoutName) ; 1) = "r" ]
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to copyist tags, or keep the current records shown?"; Buttons: “keep”, “show” ]
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Exit Script [ ]
End If
#
#ﬁnd on reference layout ...
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::ﬁlterFind; "copyist" ]
Perform Find [ ]
End If
End If
#
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
Go to Field [ ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
January 7, 平成26 16:02:47 Imagination Quality Management.fp7 - menuCopyist -1-
