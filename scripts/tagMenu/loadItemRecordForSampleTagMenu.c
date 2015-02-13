tagMenu: loadItemRecordForSampleTagMenu
#
#Capture recordID to conditionally format current record.
If [ $$stopLoadTagRecord ≠ 1 ]
Go to Field [ ]
#
#The 'sample' variable may have more than one
#key in it. So we need a variable with just this
#records keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
Set Field [ TEMP::kcsample; tagMenus::_Ltag ]
Set Variable [ $$SampleOrTestID; Value:Get (RecordID) ]
#
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ ]
Move/Resize Window [ Current Window; Height: 3; Width: 3; Top: -1000; Left: -1000 ]
Go to Layout [ “learn1” (testlearn) ]
#Prepare system to stop error message about no
#records being found as the user may not have
#yet tagged any learn records with this test tag.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "main" ]
Perform Find [ ]
Constrain Found Set [ Speciﬁed Find Requests: Omit Records; Criteria: testlearn::kcsample: “=” ]
[ Restore ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:1 ]
Loop
Exit Loop If [ (FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 1 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 2 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 3 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 4 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 5 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 6 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 7 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 8 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 9 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 10 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
) = 1 ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $atLeastOneRecord; Value:If ( (FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 1 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 2 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 3 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 4 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 5 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 6 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 7 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 8 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 9 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
or
FilterValues ( Middle ( GetValue ( testlearn::kcsample ; 10 ) ; 4 ; 42 ) ; $$tagsample & "¶" ) = $$tagsample & ¶
) = 1 ; 1 ; "" ) ]
Go to Layout [ original layout ]
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
#date and not by test item sort order.
If [ $atLeastOneRecord ≠ 1 ]
#
#The 'sample' variable may have more than one
#key in it. So we need a variable with just this
#records keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
#
Select Window [ Name: "Learn"; Current ﬁle ]
Refresh Window
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Set Field [ TEMP::TLSampleSort; "" ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
#
Else If [ $atLeastOneRecord = 1 ]
#
#The 'sample' variable may have more than one
#key in it. So we need a variable with just this
#records keys in it to conditionally format all
#learn window records tagged with it.
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
Set Field [ TEMP::kcsample; tagMenus::_Ltag ]
Set Variable [ $$SampleOrTestID; Value:Get (RecordID) ]
If [ $$add = 1 and $$citationMatch = $$addCitationMatch ]
Else If [ $$add = "" ]
End If
Refresh Window
#
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
// If [ TEMP::TLTestSort = "" ]
Set Field [ TEMP::TLSampleSort; "order" ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Select Window [ Name: "Learn"; Current ﬁle ]
Perform Script [ “SortTLRecordsByOrderNumber” ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
January 7, 平成26 16:18:59 Imagination Quality Management.fp7 - loadItemRecordForSampleTagMenu -1-tagMenu: loadItemRecordForSampleTagMenu Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
// End If
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
End If
#
#Unlike exit script, halt scripts will halt all scripts
#currently active. So if user was on another tag
#record and then clicked on the add tag button
#to for another record, this script will launch.
#Problem is, because the user may want to really
#want to add this tag to the current item in the
#Learn window, after this script runs and ﬁnds
#zero records for example (which could happen)
#the add to tag script will run right after it, but
#it will fail to sort the records in the Learn window
#by order number, which this script
#(loadITemRecrodForTestTagMenu) is supposed
#do everytime. The problem is a record for this
#tag record will exist after the addtotag script has
#run, but this script will not know that having run
#ﬁrst. So the user will be left wondering, "how is
#that everytime I click on a new test or sample tag
#record that has record tagged with it in the Learn
#window, the Learn window is sorted by order number
#except for this time? How did this fail to happen?"
#Well, it failed for the reason given above and
#the sollution below is to use the 'Halt Script"
#command, which will force the user to click
#the add to tag button a second time to add the
#tag (the ﬁrst time being when the user clicked
#it to move the system focus to this record, which
#triggered this loadItem... scirpt.
Halt Script
End If
January 7, 平成26 16:18:59 Imagination Quality Management.fp7 - loadItemRecordForSampleTagMenu -2-
