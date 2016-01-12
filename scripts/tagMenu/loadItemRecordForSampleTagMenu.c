tagMenu: loadItemRecordForSampleTagMenu
#
#WHEN TIME PERMITS
#Replace all instances of 'sample' and 'theory'
#with the word 'brainstorm'. REQUIRES going
#thru DDR to insure all instances are replaced.
#This is not critical, but would make scripts
#match layout screen button 'brainstorm'.
#
#
#Capture recordID to conditionally format current record.
If [ $$stopLoadTagRecord ≠ 1 ]
Go to Field [ ]
#
#The 'sample' variable may have more than one
#key in it. So we need a variable with just this
#record's keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
Set Field [ TEMP::kcsample; tagMenus::_Ltag ]
Set Variable [ $$SampleOrTestID; Value:Get (RecordID) ]
#
#The next conditional formatting variable needs
#to be cleared in case there are no records in
#the learn window tagged with this tag record.
#It might contain a tag ID from the selecting
#the previous record which did have at least 1
#learn record tagged with it. (See the end of
#this script where it is actually created.)
Set Variable [ $$atLeastOneRecord ]
#
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Height: 3; Width: 3; Top: -1000; Left: -1000 ]
Go to Layout [ “learn1” (testlearn) ]
#
#Prepare system to stop error message about no
#records being found as the user may not have
#yet tagged any learn records with this brainstorm tag.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::kcsample; "*" & $$tagsample & ¶ ]
Perform Find [ ]
Set Variable [ $atLeastOneRecord; Value:If ( Get ( FoundCount ) = 0 ; "" ; 1) ]
Close Window [ Current Window ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#This won't work without going through every
#record on the main window to check if it is tagged
#with this record, and that could take a really long
#time.
#So if there are no records tagged with this test item
#then make sure the Main window is sorted by
#date and not by brainstorm item sort order.
If [ $atLeastOneRecord ≠ 1 ]
#
#The 'sample' variable may have more than one
#key in it. So we need a variable with just this
#records keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
#
Select Window [ Name: "Learn"; Current file ]
Refresh Window
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Set Field [ TEMP::TLSampleSort; "" ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
Else If [ $atLeastOneRecord = 1 ]
#
#The formatting of sample tagged records in
#the Learn window is linked to the current
#record in the tag window. THE ONLY WAY to
#know this in the Tag window (that there are
#tagged records in the learn window) is to
#make a $$ variable. This way the system will
#remember it is conditionally formatting learn
#records when the active learn record is not
#tagged with the current record in the tag window.
Set Variable [ $$atLeastOneRecord; Value:$$tagsample ]
#
#The 'sample' variable may have more than one
#key in it. So we need a variable with just this
#record's keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
Set Field [ TEMP::kcsample; tagMenus::_Ltag ]
Set Variable [ $$SampleOrTestID; Value:Get (RecordID) ]
If [ $$add = 1 and $$citationMatch = $$addCitationMatch ]
Else If [ $$add = "" ]
End If
Refresh Window
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Set Field [ TEMP::TLSampleSort; "order" ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Select Window [ Name: "Learn"; Current file ]
#
#Insure user can be returned to their Learn
#record selection at the end of this script.
Set Variable [ $$returnFocusToThisRecord; Value:testlearn::_Ltestlearn ]
#
#Stop citation load script for the following find.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#In case the user is not show all records, find
#this sample tag's learn records.
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::kcsample; "*" & $$tagsample & ¶ ]
Extend Found Set [ ]
#
#Return user to seleteced learn record if they
#are not already on it.
If [ $$returnFocusToThisRecord ≠ testlearn::_Ltestlearn and $$returnFocusToThisRecord ≠ "" ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$returnFocusToThisRecord = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadCitation ]
Set Variable [ $$returnFocusToThisRecord ]
End If
Perform Script [ “loadCitation” ]
#
Perform Script [ “sortTLRecordsByOrderNumber” ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
End If
#
#Unlike 'exit script', 'halt script' will halt all scripts
#currently active. So if user was on another tag
#record and then clicked on the add tag button
#for another record, this script will launch.
#Problem is, because the user may really
#want to add this tag to the current item in the
#Learn window, after this script runs and finds
#zero records for example (which could happen)
#the add to tag script will run right after it, but
#it will fail to sort the records in the Learn window
#by order number, which this script
#(loadITemRecrodForTestTagMenu) is supposed to
#do everytime. The problem is a record for this
#tag record will exist after the addtotag script has
#run, but this script will not know that having run
#first. So the user will be left wondering, "how is
#that everytime I click on a new test or sample tag
#record that has record tagged with it in the Learn
#window, the Learn window is sorted by order number
#except for this time? How did this fail to happen?"
#Well, it failed for the reason given above and
#the sollution below is to use the 'Halt Script"
#command, which will force the user to click
#the add to tag button a second time to add the
#tag (the first time being when the user clicked
#it to move the system focus to this record, which
#triggered this loadItem... script.
Halt Script
End If
January 12, ଘ౮28 13:36:57 Library.fp7 - loadItemRecordForSampleTagMenu -1-
