tagMenu: testAddTestItemTextOrKey
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
#If text is selected then the user wants to add
#the text of the test item to the caption ﬁeld.
If [ TEMP::textORcheck = "text" ]
Set Variable [ $tag; Value:tagMenus::tag ]
#
Select Window [ Name: "Test"; Current ﬁle ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Field [ testlearn::Caption; $caption & ¶ & $tag ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
Exit Script [ ]
End If
#
#If check is selected then the user wants to add
#the key of the test item to the discovery record's
#keychain.
#
#Get key for tag that is to be added to record.
Set Variable [ $tag; Value:tagMenus::_Ltag ]
#
#If test item is in use, then remove it.
Select Window [ Name: "Test"; Current ﬁle ]
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( GetValue ( testlearn::kctestItem ; $number ) ; $tag & "¶" ) = $tag & ¶ ]
Set Field [ testlearn::kctestItem; Substitute ( $$testItem ; GetValue ( testlearn::kctestItem ; $number ) & "¶" ; "" ) ]
Set Variable [ $$testItem; Value:testlearn::kctestItem ]
Set Variable [ $number; Value:"exit" ]
#
#Remove one item from inuse items for this group.
#This is essential for the unlink script on the test setup
#module. A group that has items in use cannot be
#unlinked until all inuse items are unlinked.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Set Variable [ $inUseNumberOfTimes; Value:ruleTagMenuGroups::CaptionORinuseCheck ]
Set Field [ ruleTagMenuGroups::CaptionORinuseCheck; If ( $inUseNumberOfTimes - 1 = 0 ; "" ; $inUseNumberOfTimes - 1 ) ]
End If
#
#If number was set to exit or if no keys exist, then
#exit loop.
Exit Loop If [ GetValue ( testlearn::kctestItem ; $number ) = "" ]
#
#Not sure how this could happen, but leaving it in and
#wishing I had made a comment when I added it.
Exit Loop If [ $number = "" ]
#
#If variable looked at did not match then raise the number
#to view the next variable.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
If [ $number ≠ "exit" ]
#
#Start by looking at the ﬁrst variable on the keychain.
Set Variable [ $number; Value:1 ]
Loop
#If test item is not in use add it.
If [ FilterValues ( GetValue ( testlearn::kctestItem ; $number ) ; $tag & "¶" ) ≠ $tag & ¶ ]
Set Field [ testlearn::kctestItem; $tag & ¶ & $$testItem ]
Set Variable [ $$testItem; Value:testlearn::kctestItem ]
Set Variable [ $number ]
#
#Record must be committed if user decides to
#perform a script on it right after this one or
#perform a ﬁnd requiring the newly added key.
Commit Records/Requests
#
#
#Add one item from inuse items for this group.
#This is essential for the unlink script on the test setup
#module. A group that has items in use cannot be
#unlinked until all inuse items are unlinked.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Set Variable [ $inUseNumberOfTimes; Value:ruleTagMenuGroups::CaptionORinuseCheck ]
Set Field [ ruleTagMenuGroups::CaptionORinuseCheck; $inUseNumberOfTimes + 1 ]
End If
#
#If number was set to exit or if no keys exist, then
#exit loop.
Exit Loop If [ FilterValues ( GetValue ( testlearn::kctestItem ; $number ) ; $tag & "¶" ) = "" ]
#
#Not sure how this could happen, but leaving it in and
#wishing I had made a comment when I added it.
Exit Loop If [ $number = "" ]
#
#If variable looked at did not match then raise the number
#to view the next variable.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
End If
// Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
#
Go to Field [ ]
January 7, 平成26 16:08:52 Imagination Quality Management.fp7 - testAddTestItemTextOrKey -1-
