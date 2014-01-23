learn: deleteLearnMainRecord
#
#If node is currenlty locked then stop script, inform user.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to delete records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in ﬁnd mode, exit script.
If [ $$ﬁndMode ≠ "" ]
Show Custom Dialog [ Message: "Exit ﬁnd mode, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Exit ﬁeld so user can see red delete
#formatting later on.
Go to Field [ ]
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
#
#If either the sample or test ﬁelds are ﬁlled show
#message below.
If [ testlearn::kcsample ≠ "" and testlearn::kctest ≠ "" ]
Show Custom Dialog [ Message: "In use by Theory and Test records. Must be removed before deleting. Click the 'theorize' button and scroll to highlighted items. Click the square buttons next them. Click the 'test' button and repeat delinking process."; Buttons: “OK” ]
Exit Script [ ]
Else If [ testlearn::kcsample ≠ "" ]
Show Custom Dialog [ Message: "In use by Theory records. Must be removed before deleting. Click the 'theorize' button and scroll to highlighted items. Click the square buttons next them."; Buttons: “OK” ]
Exit Script [ ]
Else If [ testlearn::kctest ≠ "" ]
Show Custom Dialog [ Message: "In use by Test records. Must be removed before deleting. Click the 'test' button and scroll to highlighted items. Click the square buttons next them."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Set variables to conditionally format section to
#be deleted, and its record number so if the
#user cancels the delete, the system can return
#to this record.
Set Variable [ $delete; Value:testlearn::_Ltestlearn ]
Set Variable [ $deleteName; Value:testlearn::_Number ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Set Variable [ $section; Value:TEMP::ksection ]
#
#Because there may be no records found, stop
#the system from informing the user of this.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Open a new window and look for record being
#cited or used as a reference by another record.
New Window [ ]
#
Loop
#
#Clear the inUse variable before each run thru
#the loop. If not cleared, then last time thru
#if this variable had a value in it, that value will
#stay in it even if no ﬁnds are made, which then
#tells the system that a no-ﬁnd reference, has ﬁnds.
#So the system must clear this variable before each
#run thru the loop.
Set Variable [ $inUse ]
#
#See if learn record is used by any learn records as a
#citation.
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kcitation; $delete ]
Set Field [ testlearn::kcsection; $section ]
Perform Find [ ]
#
If [ Get (LastError) ≠ 401 ]
Set Variable [ $inUse; Value:Get (FoundCount) & " learn citation" ]
End If
#
#See if learn record is used by any learn records as a
#reference.
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $delete ]
Set Field [ testlearn::kcsection; $section ]
Perform Find [ ]
#
If [ Get (LastError) ≠ 401 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & ", " & Get (FoundCount) & " learn reference" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:Get (FoundCount) & " learn reference" ]
End If
End If
#
#See if reference record is used by any tag records as a
#picture.
Go to Layout [ “tableTag” (tagTable) ]
#picture1
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture1; $delete ]
Set Field [ ruleLibrary 2::ksection; $section ]
Perform Find [ ]
Set Variable [ $tagFound1; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#picture2
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture2; $delete ]
Set Field [ ruleLibrary 2::ksection; $section ]
Perform Find [ ]
January 7, 平成26 17:23:26 Imagination Quality Management.fp7 - deleteLearnMainRecord -1-learn: deleteLearnMainRecord
Set Variable [ $tagFound2; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#picture3
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture3; $delete ]
Set Field [ ruleLibrary 2::ksection; $section ]
Perform Find [ ]
Set Variable [ $tagFound3; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
If [ $tagFound1 + $tagFound2 + $tagFound3 ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & ", " & ($tagFound1 + $tagFound2 + $tagFound3) & " tag menu picture(s) (" & $tagName & ")" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " tag menu picture(s) (" & $tagName & ")" ]
End If
End If
#
Set Variable [ $tagFound1 ]
Set Variable [ $tagFound2 ]
Set Variable [ $tagFound3 ]
Set Variable [ $tagNameADD ]
Set Variable [ $tagName ]
#
#See if reference record is used by any tag records
#as a web link.
Go to Layout [ “tableTag” (tagTable) ]
#link1
Enter Find Mode [ ]
Set Field [ tagTable::Ktitle1; $delete ]
Set Field [ ruleLibrary 2::ksection; $section ]
Perform Find [ ]
Set Variable [ $tagFound1; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#link2
Enter Find Mode [ ]
Set Field [ tagTable::Ktitle2; $delete ]
Set Field [ ruleLibrary 2::ksection; $section ]
Perform Find [ ]
Set Variable [ $tagFound2; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#link3
Enter Find Mode [ ]
Set Field [ tagTable::Ktitle3; $delete ]
Set Field [ ruleLibrary 2::ksection; $section ]
Perform Find [ ]
Set Variable [ $tagFound3; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
If [ $tagFound1 + $tagFound2 + $tagFound3 ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & ", " & ($tagFound1 + $tagFound2 + $tagFound3) & " tag menu link(s) (" & $tagName & ")" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " tag menu link(s) (" & $tagName & ")" ]
End If
End If
#
Set Variable [ $tagFound1 ]
Set Variable [ $tagFound2 ]
Set Variable [ $tagFound3 ]
Set Variable [ $tagNameADD ]
Set Variable [ $tagName ]
#
January 7, 平成26 17:23:26 Imagination Quality Management.fp7 - deleteLearnMainRecord -2-learn: deleteLearnMainRecord
#If the current record is in use in the section of
#the database from which the delete was requested,
#inform the user of this, and skip the next
#steps of this loop and the next loop, which.
#is for checking if record is in use in other sections.
If [ $section = TEMP::ksection and $inUse ≠ "" ]
#
#If the record was in use in the current section
#then do not look for it in other sections.
Set Variable [ $checkSection; Value:$section ]
Set Variable [ $section ]
Exit Loop If [ $checkSection = TEMP::ksection and $inUse ≠ "" ]
End If
#
#If the current record is not in use in the section
#of the database from which this delete was started,
#capture this information.
If [ $section = TEMP::ksection and $inUse = "" ]
Set Variable [ $deleteNotInUse; Value:"not in use" ]
End If
#
#Exit the loop if there is only 1 section key for this record
#or if the system just checked for the record
#in all sections of the database, which
#is why the section variable would be blank.
#In the latter case, the loop would be coming round
#after checking all sections in the database.
#At ﬁrst the loop is conﬁned to looking at all records
#in this section. Once it has done that, a script
#step below exits the loop only to enter a loop
#that clears the section variable and causes the
#system to re-enter this loop, only with a blank
#section variable so it will look in all sections of the
#database. When it reaches this step, that blank
#section variable will force it out of this loop and
#a similar script step in the outer loop will do the
#same thereby allowing the system to follow the
#remainder of this script to report on the ﬁndings
#made during these discovery loops.
Exit Loop If [ ValueCount ( testlearn::kcsection ) = 1 or $section = "" ]
#
#If the current record is not in use in the section
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
#Report on ﬁndings and if none delete record.
#
#
#
#
#If the record in question was not found in the
#section the user is deleting it from...
If [ $deleteNotInUse ≠ "" ]
#
#But this record is in use in other sections...
If [ $inUse ≠ "" ]
#
Refresh Window
Show Custom Dialog [ Message: "This record cannot be deleted as it in use in other sections of the database. You can remove it from this section though as it is not being used in this section."; Buttons: “cancel”, “remove” ]
If [ Get ( LastMessageChoice ) = 1 ]
#
#If the user chooses not to remove the record
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
Set Variable [ $delete ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#If the user choses to proceed with the removal,
#the section key is removed from the record's
#key chain. ( paragraph mark is added to section in
# case the key has no paragraph mark after it and so
# would not be found. )
Set Field [ testlearn::kcsection; Substitute ( testlearn::kcsection & ¶ ; TEMP::ksection & ¶ ; "" ) ]
#
#Omit the record as it no longer is part of this section.
Omit Record
#
End If
Exit Script [ ]
End If
End If
#
#
#
#If record was found in current section tell user.
If [ $inUse ≠ "" ]
Set Variable [ $delete ]
Refresh Window
// Show Custom Dialog [ Message: "This record cannot be deleted as it in use x number of times as a citation or reference in the following windows of this section: " & $inUse & "."; Buttons: “OK” ]
Show Custom Dialog [ Message: "Record cannot be deleted as it in use in these windows: " & $inUse & "."; Buttons: “OK” ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
#
#
#If record is not in use in any section, but has more
January 7, 平成26 17:23:26 Imagination Quality Management.fp7 - deleteLearnMainRecord -3-learn: deleteLearnMainRecord
#than one section key, give user option to remove it
#from just this section.
If [ ValueCount ( testlearn::kcsection ) > 1 ]
Refresh Window
Show Custom Dialog [ Message: "This record is in other sections of the library. Do you want to remove it from just this section or delete it from all sections?"; Buttons: “cancel”, “remove”, “delete” ]
#
#If the user cancels, stop the delete.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#If the clicks remove, then remove the record.
Else If [ Get ( LastMessageChoice ) = 2 ]
#
Set Variable [ $delete ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#If the user choses to proceed with the removal,
#the section key is removed from the record's
#key chain. ( paragraph mark is added to section in
# case the key has no paragraph mark after it and so
# would not be found. )
Set Field [ testlearn::kcsection; Substitute ( testlearn::kcsection & ¶ ; TEMP::ksection & ¶ ; "" ) ]
#
#Omit the record as it no longer is part of this section.
Omit Record
#
Exit Script [ ]
End If
#
End If
#
#
#
#
#If the record being deleted was not found in
#use in any sections of the database then before
#deleting it make sure the user really wants it deleted.
Set Variable [ $group ]
Refresh Window
Show Custom Dialog [ Message: "Delete current record?"; Buttons: “cancel”, “delete” ]
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
#If the user says yes, then delete the record.
Else If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
#
End If
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
Perform Script [ “loadCitation” ]
#
#
January 7, 平成26 17:23:26 Imagination Quality Management.fp7 - deleteLearnMainRecord -4-
