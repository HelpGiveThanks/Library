tagMenu: menuPath
#
#If user is in tag ﬁeld and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Clear sample and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "sample" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Set Variable [ $$tagSample ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
End If
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"path" ]
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
#Turn off the loadtagrecord script to speed up the
#loop portion of the script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenu1” (tagMenus) ]
#
#If in learn mode ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnMenu1” (tagMenus) ]
#
#If in reference mode ...
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
End If
#
#Find Path tags. Path tags are available to all library sections.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; "Path" ]
Perform Find [ ]
#
#If no records exist then create one.
If [ Get (FoundCount)=0 ]
Perform Script [ “newCitationMenuGroup” ]
End If
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
Sort Records [ ]
[ No dialog ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortPath = "cat" or TEMP::sortPath = "" ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPath = "abc" ]
Sort Records [ Speciﬁed Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Go to citation record's current selection or to ﬁrst record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$Path = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn loadtagrecord script back on.
Set Variable [ $$stopLoadTagRecord ]
#
If [ $$Path ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
// Exit Script [ ]
End If
#
#Inform user of items use on both screens.
Set Variable [ $$citationItem; Value:tagMenus::_Ltag ]
Refresh Window
#
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
#
#If in add mode, ﬁnd only records tagged with
#current $$citationmatch.
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to ﬁle path tags, or keep the current records shown?"; Buttons: “keep”, “show” ]
If [ Get ( LastMessageChoice ) = 1 ]
January 7, 平成26 16:03:19 Imagination Quality Management.fp7 - menuPath -1-tagMenu: menuPath
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Exit Script [ ]
End If
#
#ﬁnd on reference layout ...
If [ Left (Get (LayoutName) ; 1) = "r" ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::ﬁlterFind; "path" ]
Perform Find [ ]
#
#ﬁnd on learn layout ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "path" ]
Perform Find [ ]
End If
End If
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
January 7, 平成26 16:03:19 Imagination Quality Management.fp7 - menuPath -2-
