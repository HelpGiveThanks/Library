tagMenu: deleteKeywordTag
#
#Decided to allow user to delete tags created by a locked
#user, but not create tags using a locked user.
#User needs full control over their tags.
#If node is currenlty locked then stop script, inform user.
If [ nodeLockTagMenus::orderOrLock ≠ "" ]
// Show Custom Dialog [ Message: "FYI — This record is part of a set of records that can be updated. You can delete it, but if you update your library this record will be put back if it is part of the update."; Buttons: “OK” ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTagMenus::tag & " -- in the setup tag window and enter the password to unlock it so that you can delete it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If user is looking at Node switch to that script.
If [ $$citationMatch = "node" ]
Perform Script [ “deleteNodeTag” ]
Exit Script [ ]
End If
#
#Exit field so user can see red delete
#formatting later on.
Go to Field [ ]
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Set variables to conditionally format section to
#be deleted, and its record number so if the
#user cancels the delete, the system can return
#to this record.
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Set Variable [ $deleteName; Value:tagMenus::tag ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Set Variable [ $$addTagToCitation; Value:1 ]
Set Variable [ $section; Value:TEMP::ksection ]
Set Variable [ $group; Value:tagMenus::kGroupOrTest ]
#
#Because there may be no records found, stop
#the system from informing the user of this.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Open a new window and look for tag in both
#primary and other node fields.
New Window [ ]
#
Loop
Loop
#
#The delete variable is used only to identify the
#node the user clicked the delete button for.
#The check variable is for every keyword in a group
#that the system needs to see if it is in use.
Set Variable [ $check; Value:tagMenus::_Ltag ]
#
#Clear the inUse variable before each run thru
#the loop. If not cleared, then last time thru
#if this variable had a value in it, that value will
#stay in it even if no finds are made, which then
#tells the system that a no find keyword, has finds.
#So the system must clear this variable before each
#run thru the loop.
Set Variable [ $inUse ]
#
#See if keyword is used by any learn records.
#Look in main kprimary...
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kKeywordPrimary; $check ]
Set Field [ testlearn::kcsection; $section ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
#
#Look in main kother...
Enter Find Mode [ ]
Set Field [ testlearn::kcKeywordOther; $check & ¶ ]
Set Field [ testlearn::kcsection; $section ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Extend Found Set [ ]
If [ Get (FoundCount) ≠ 0 ]
Set Variable [ $inUse; Value:Get (FoundCount) & " learn" ]
End If
#
#See if keyword is used by any discovery records.
#Check in discovery primary...
Enter Find Mode [ ]
Set Field [ testlearn::kKeywordPrimary; $check ]
Set Field [ testlearn::kcsection; $section ]
Set Field [ testlearn::ktest; "*" ]
Perform Find [ ]
#
#Check in other...
Enter Find Mode [ ]
Set Field [ testlearn::kcKeywordOther; $check ]
Set Field [ testlearn::kcsection; $section ]
Set Field [ testlearn::ktest; "*" ]
Extend Found Set [ ]
#
#See if keyword is used by any reference records.
#Check in primary...
Go to Layout [ “Reference” (reference) ]
Enter Find Mode [ ]
Set Field [ reference::kkeywordPrimary; $check ]
Set Field [ reference::kcsection; $section ]
Perform Find [ ]
#
#Check in other...
Enter Find Mode [ ]
Set Field [ reference::kkeywordOther; $check ]
Set Field [ reference::kcsection; $section ]
Extend Found Set [ ]
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & ", " & Get (FoundCount) & " reference" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:Get (FoundCount) & " reference" ]
January 7, 平成26 16:32:40 Imagination Quality Management.fp7 - deleteKeywordTag -1-tagMenu: deleteKeywordTag
End If
End If
#
#Return to keyword layout.
Go to Layout [ “ltagNK1” (tagMenus) ]
#
#If the current keyword is in use in the section of
#the database from which the delete was requested,
#inform the user of this, and skip the next
#steps of this loop and the next loop, which.
#is for checking if keyword is in use in other sections.
If [ tagMenus::_Ltag = $delete and $inUse ≠ "" ]
#
#If the keyword was in use in the current section
#then do not look for it in other sections.
Set Variable [ $section ]
Exit Loop If [ tagMenus::_Ltag = $delete and $inUse ≠ "" ]
End If
#
#If the current keyword is not in use in the section
#of the database from which this delete was started,
#capture this information.
If [ $delete = tagMenus::_Ltag and $inUse = "" ]
Set Variable [ $deleteNotInUse; Value:"not in use" ]
End If
#
#Exit the loop if there is only 1 member of this group
#or if the system just checked for the intial delete
#keyword in all sections of the database, which
#is why the section variable would be blank.
#In the latter case, the loop would be coming round
#after checking all sections in the database.
#At first the loop is confined to looking at all keywords
#in this section. Once it has done that, a script
#step below exits the loop only to enter a loop
#that clears the section variable and causes the
#system to re-enter this loop, only with a blank
#section variable so it will look in all sections of the
#database. When it reaches this step, that blank
#section variable will force it out of this loop and
#a similar script step in the outer loop will do the
#same thereby allowing the system to follow the
#remainder of this script to report on the findings
#made during these discovery loops.
Exit Loop If [ ValueCount ( ruleTagMenuGroups::ksection ) = 1 or $section = "" ]
#
#If the current keyword is not in use in this section
#then check if any of the other keywords in its group
#are in use in this section. These next steps apply
#to discovering inUse info about the other keywords
#in the original keywords group.
#
#Make a list of all keywords in the group that are
#linked to records in this section AND are in use
#(thus the inUse variable will not be blank).
If [ $delete ≠ tagMenus::_Ltag and $inUse ≠ "" ]
Set Variable [ $add; Value:If ( $nodeName = "" ; "" ; $nodeName & "; " ) ]
Set Variable [ $nodeName; Value:$add & tagMenus::tag ]
End If
#
#Capture any InUse variable content for later use
#use in the script.
Set Variable [ $addToSectionInUse; Value:$sectionInUse ]
Set Variable [ $sectionInUse; Value:$inUse & $addToSectionInUse ]
#
#Go the next record. As this delete may have
#been started on a record in the middle of the group
#these next steps insure that all records are checked
#even if that requires going to the first record
#in order to eventually loop thru all records in a
#group back to the initial record.
Go to Record/Request/Page
[ Next ]
If [ Get ( LastError ) = 101 ]
Go to Record/Request/Page
[ First ]
End If
#
#There may be more than one group of keywords
#in a section, so this next loop insures that the
#script bypasses other groups' nodes.
If [ tagMenus::kGroupOrTest ≠ $group ]
Loop
Go to Record/Request/Page
[ Next ]
If [ Get ( LastError ) = 101 ]
Go to Record/Request/Page
[ First ]
End If
Exit Loop If [ tagMenus::kGroupOrTest = $group ]
End Loop
End If
#
#Exit the loop when the intial record is reached
#for the second time.
Exit Loop If [ $delete = tagMenus::_Ltag ]
End Loop
#
#Exit the loop if the system is on the initial record
#and this record is in use and all sections of
#the database have been checked.
Exit Loop If [ tagMenus::_Ltag = $delete and $inUse ≠ "" and $section = "" ]
Exit Loop If [ ValueCount ( ruleTagMenuGroups::ksection ) = 1 or $section = "" ]
#
#If the current keyword is not in use in the section
#of the database where the delete was started,
#make sure it is not in use in any other section.
Set Variable [ $section ]
#
End Loop
#
Close Window [ Current Window ]
#
#
#
#
#Report on findings and if none delete keyword.
#
January 7, 平成26 16:32:40 Imagination Quality Management.fp7 - deleteKeywordTag -2-tagMenu: deleteKeywordTag
#
#
#
#If the keyword in question was not found in the
#section the user is deleting it from...
If [ $deleteNotInUse ≠ "" ]
#
#But this keyword is in use in other sections...
If [ $inUse ≠ "" ]
#
#If the other keywords in the keyword's group are in
#use in this section, then they must be unlinked
#from the records using them before the group
#all these keywords belong to can be removed from
#this section.
If [ $nodeName ≠ "" ]
Set Variable [ $delete ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Refresh Window
Show Custom Dialog [ Message: "This keyword cannot be deleted as it in use in other sections of the database. You can remove it from this section after you unlink these other keywords from this group: " & $nodeName & "."; Buttons: “OK” ]
Exit Script [ ]
#
#If the other keywords in the keyword's group are not
#in use BUT some of the other default items
#are part of this group, then this group cannot
# be removed from this section of the database.
Else If [ $nodeName = "" and $defaultNodeList ≠ "" ]
Set Variable [ $delete ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Refresh Window
Show Custom Dialog [ Message: "This keyword cannot be deleted as it in use in other sections of the database. You can remove it from this section after the following keywords from this group are unlinked as defaults: " & $defaultNodeList; Buttons: “OK” ]
Exit Script [ ]
#
#If the other keywords in the keyword's group are not
#in use and none of the other default items
#are part of this group, then this group can be
#removed from this section of the database.
#The user is given the option to do this removal.
Else If [ $nodeName = "" and $defaultNodeList = "" ]
Refresh Window
Show Custom Dialog [ Message: "This keyword cannot be deleted as it in use in other sections of the database. You can remove it from this section along with all the other keywords in its group. None of them are being used in this section."; Buttons: “cancel”, “remove” ]
If [ Get ( LastMessageChoice ) = 1 ]
#
#If the user chooses not to remove the group
#everything goes back to the way it was.
Go to Field [ ]
Set Variable [ $delete ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Refresh Window
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
#
#If the user choses to proceed with the removal,
#the section key is removed from the keyword group's
#key chain.
Set Field [ ruleTagMenuGroups::ksection; Substitute ( ruleTagMenuGroups::ksection & ¶ ; TEMP::ksection & ¶ ; "" ) ]
#
#For some reason, Filemaker will not remove paragraph
#character along with variable, so can end up with
#huge list of blank variables if this next part of the
#script is not performed to delete empty variables.
Set Variable [ $sectionVariableNumber; Value:ValueCount ( ruleTagMenuGroups::ksection ) ]
Loop
If [ GetValue ( ruleTagMenuGroups::ksection ; $sectionVariableNumber ) ≠ "" ]
Set Variable [ $sectionKeyMinusBlanks; Value:GetValue ( ruleTagMenuGroups::ksection ; $sectionVariableNumber ) & ¶ ]
End If
Set Variable [ $sectionVariableNumber; Value:$sectionVariableNumber - 1 ]
Exit Loop If [ $sectionVariableNumber = 0 ]
End Loop
Set Field [ ruleTagMenuGroups::ksection; $sectionKeyMinusBlanks ]
#
#A find is performed to show the remaining keyword
#groups for this section.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; "key" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
#Sort according to current users wishes. By default
#the sort will be by group which is set by editCitation script.
If [ TEMP::sortKey = "cat"
 or
TEMP::sortKey = "" ]
Sort Records [ Specified Sort Order: ruleTagSectionName::name; ascending
ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortKey = "abc" ]
Sort Records [ Specified Sort Order: ruleTagSectionName::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Go to citation record's current selection or to first record.
#Because user may click anywhere to go to a record
#all keys for all menu items must uploaded
#until one is found that matches and then the
#$$citationItem variable can be set.
#Like when the user clicks in a non field area
#a space between fields that then tells filemaker
#to go that record but not to field belonging to
#that record.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $$citationitem = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
January 7, 平成26 16:32:40 Imagination Quality Management.fp7 - deleteKeywordTag -3-tagMenu: deleteKeywordTag
If [ $$citationitem ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
End If
#
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Refresh Window
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "Setup"; Current file ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
#
End If
Exit Script [ ]
End If
End If
#
#If the keyword being deleted was not found in
#use in any sections of the database then before
#deleting it make sure the user really wants it deleted.
Set Variable [ $group ]
Refresh Window
Show Custom Dialog [ Message: "Delete current keyword?"; Buttons: “cancel”, “delete” ]
Set Variable [ $group; Value:tagMenus::kGroupOrTest ]
Set Variable [ $deleteGroup; Value:ruleTagMenuGroups::name ]
#
#If the user cancels, stop the delete.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#If the user says yes, first make sure the record
#is not the last record in a group. If it is and
#the system deleted the record without deleting
#the group too, this group would become
#an orphan as only categories that have records
#attached to them show up for the user to add
#more records uner them. So the group
#record must also be deleted if this is the last
#record under it.
Else If [ Get ( LastMessageChoice ) = 2 ]
New Window [ Name: "delete tag" ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kGroupOrTest; $group ]
Perform Find [ ]
#
#If there are more records under this cateogry
#then the system deletes the current record without
#any more user input.
If [ Get (FoundCount) ≠ 1 ]
Close Window [ Name: "Delete Tag"; Current file ]
Delete Record/Request
[ No dialog ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#BUT if only one record is found user is asked
#if they want to delete the group too.
Else If [ Get (FoundCount) = 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#The records are sorted by group to show
#the user which group is going to be deleted.
If [ TEMP::sortKey ≠ "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
Show Custom Dialog [ Title: "!"; Message: "Deleting " & $deleteName & " will also delete its group -- " & $deleteGroup & " -- as it is the last tag in this group."; Buttons: “Cancel”, “Delete” ]
#
#If the user says yes, then delete both the tag and
#the group record.
If [ Get ( LastMessageChoice ) = 2 ]
#
#Delete tag.
Delete Record/Request
[ No dialog ]
#
#Delete group.
Select Window [ Name: "delete tag"; Current file ]
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; $group ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
End If
End If
End If
Close Window [ Name: "Delete Tag"; Current file ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
End If
January 7, 平成26 16:32:40 Imagination Quality Management.fp7 - deleteKeywordTag -4-tagMenu: deleteKeywordTag
#
#
#
#
#
If [ $inUse ≠ "" ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Show Custom Dialog [ Message: "This keyword cannot be deleted as it in use x number of times in the following modules (main windows): " & $inUse & "."; Buttons: “OK” ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
End If
January 7, 平成26 16:32:40 Imagination Quality Management.fp7 - deleteKeywordTag -5-
